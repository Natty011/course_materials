// =========================================
// state.cpp — מימוש כל המצבים בקובץ אחד (מסודר לפי תלות)
// =========================================

// <Arduino.h> — millis() לזמני מערכת
#include <Arduino.h>  // millis()
// <stdint.h> — טיפוסים ברוחב קבוע
#include <stdint.h>   // uint8_t, uint16_t, uint32_t
// "state.h" — ממשק המצבים והטיפוסים הנלווים
#include "state.h"    // SodaDispenser::State, ButtonEvent, SensorData
// "dispenser.h" — ה-Context: מעבר מצבים ופעולות דומיין + מזהי כפתורים
#include "dispenser.h"// SodaDispenser::Dispenser, kBtnSelect/kBtnConfirm
// "ui.h" — שכבת קלט/פלט לתצוגה
#include "ui.h"       // nlrd::UserInterface

namespace SodaDispenser {

// --- הצהרות קדימה לפונקציות עזר חוצות-מחלקות (שוברות תלות מעגלית) ---
class State; // מה-header
State& GetIdle();
State& GetSelecting();
State& GetDispensing();
State& GetMaintenance();
State& GetError();

void SetDispenseRecipeIndex(uint8_t idx);
void SetErrorSafetyTimeout();
void SetErrorCupRemoved();

// =========================================
// ErrorState — מוצהר ראשון כדי לאפשר שימוש ב-ErrorState::Code
// =========================================
class ErrorState final : public State {
public:
  enum class Code : uint8_t { None=0, CupRemoved, SafetyTimeout, DriverFault };

  static ErrorState& Instance() { static ErrorState s; return s; }

  StateId     Id()   const override { return StateId::Error; }
  const char* Name() const override { return "Error"; }

  void OnEnter(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) override {
    (void)dispenser; (void)nowMs; Draw_(ui);
  }

  void HandleButton(Dispenser& dispenser, nlrd::UserInterface& ui, const ButtonEvent& ev) override {
    (void)ui;
    if (ev.action == ButtonAction::Press) {
      m_code = Code::None;
      dispenser.SetState(GetIdle(), ev.timestampMs);
    }
  }

  void HandleTick(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) override {
    (void)dispenser; (void)nowMs; Draw_(ui);
  }

  void Display(nlrd::UserInterface& ui) const override { Draw_(ui); }

  void SetErrorCode(Code c) { m_code = c; }

private:
  ErrorState() = default;

  const char* Text_() const {
    switch (m_code) {
      case Code::CupRemoved:    return "Cup removed";
      case Code::SafetyTimeout: return "Safety timeout";
      case Code::DriverFault:   return "Driver fault";
      default:                  return "Unknown";
    }
  }

  void Draw_(nlrd::UserInterface& ui) const { ui.DisplayText("ERROR", Text_()); }

private:
  Code m_code{Code::None};
};

// =========================================
// DispensingState — משתמש ב-ErrorState::Code
// =========================================
class DispensingState final : public State {
public:
  static DispensingState& Instance() { static DispensingState s; return s; }

  StateId     Id()   const override { return StateId::Dispensing; }
  const char* Name() const override { return "Dispensing"; }

  void OnEnter(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) override {
    (void)ui;
    m_startedAtMs = nowMs;
    m_deadlineMs  = nowMs + Safe_(dispenser);
    Start_(dispenser);
  }

  void HandleTick(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) override {
    // סיום רגיל
    if ((nowMs - m_startedAtMs) >= m_recipeMs) {
      Stop_(dispenser);
      dispenser.SetState(GetIdle(), nowMs);
      return;
    }
    // בטיחות עליון
    if (nowMs >= m_deadlineMs) {
      Stop_(dispenser);
      SetErrorSafetyTimeout();
      dispenser.SetState(GetError(), nowMs);
      return;
    }
    ui.DisplayText("Dispensing...", "Please wait");
  }

  void HandleButton(Dispenser& dispenser, nlrd::UserInterface& ui, const ButtonEvent& ev) override {
    (void)ui;
    if (ev.action == ButtonAction::LongPress && ev.buttonId == kBtnConfirm) {
      Stop_(dispenser);
      dispenser.SetState(GetIdle(), ev.timestampMs);
    }
  }

  void HandleSensorUpdate(Dispenser& dispenser, nlrd::UserInterface& ui, const SensorData& s) override {
    (void)ui;
    if (!s.cupPresent) {
      Stop_(dispenser);
      SetErrorCupRemoved();
      dispenser.SetState(GetError(), millis());
    }
  }

  void Display(nlrd::UserInterface& ui) const override { ui.DisplayText("Dispensing", "..."); }

  void SetRecipeIndex(uint8_t idx) {
    m_recipeIdx = idx;
    static constexpr uint16_t kMs[4] = { 3000, 2800, 2600, 2000 };
    m_recipeMs = (idx < 4) ? kMs[idx] : 2500;
  }

private:
  DispensingState() = default;

  uint32_t Safe_(Dispenser& d) const {
    const uint32_t g = d.DispenseSafetyMs();
    return (m_recipeMs < g) ? g : m_recipeMs;
  }

  void Start_(Dispenser& d) { d.OpenValve(0); d.StartPump(m_recipeMs); }
  void Stop_(Dispenser& d)  { d.StopPump();    d.CloseValve(0); }

private:
  uint8_t  m_recipeIdx{0};
  uint16_t m_recipeMs{2500};
  uint32_t m_startedAtMs{0};
  uint32_t m_deadlineMs{0};
};

// =========================================
// SelectingState — משתמש ב-DispensingState
// =========================================
class SelectingState final : public State {
public:
  static SelectingState& Instance() { static SelectingState s; return s; }

  StateId     Id()   const override { return StateId::Selecting; }
  const char* Name() const override { return "Selecting"; }

  void OnEnter(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) override {
    (void)dispenser; (void)nowMs;
    m_enteredAtMs = millis();
    m_index = 0;
    m_cup = false;
    Draw_(ui);
  }

  void HandleTick(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) override {
    (void)ui;
    const uint32_t dead = dispenser.SelectingTimeoutMs();
    if (dead > 0 && (nowMs - m_enteredAtMs) >= dead) {
      dispenser.SetState(GetIdle(), nowMs);
    }
  }

  void HandleButton(Dispenser& dispenser, nlrd::UserInterface& ui, const ButtonEvent& ev) override {
    if (ev.action != ButtonAction::Press) return;

    if (ev.buttonId == kBtnSelect) {
      Next_(ui);
      return;
    }
    if (ev.buttonId == kBtnConfirm) {
      if (!m_cup) {
        ui.DisplayText("No cup", "Place cup first");
        return;
      }
      SetDispenseRecipeIndex(m_index);
      dispenser.SetState(GetDispensing(), ev.timestampMs);
    }
  }

  void HandleSensorUpdate(Dispenser& dispenser, nlrd::UserInterface& ui, const SensorData& s) override {
    (void)dispenser;
    m_cup = s.cupPresent;
    Draw_(ui);
  }

  void Display(nlrd::UserInterface& ui) const override { Draw_(ui); }

  uint32_t InactivityDeadlineMs() const override { return Defaults::SelectingTimeoutMs; }

private:
  SelectingState() = default;
  static constexpr uint8_t kSize = 4;

  const char* NameByIndex_() const {
    static const char* kMenu[kSize] = { "Cola", "Orange", "Lemon", "Soda" };
    return kMenu[m_index];
  }

  void Draw_(nlrd::UserInterface& ui) const {
    ui.DisplayText(NameByIndex_(), m_cup ? "Confirm" : "Place cup...");
  }

  void Next_(nlrd::UserInterface& ui) {
    if (m_index + 1 < kSize) ++m_index; else m_index = 0;
    Draw_(ui);
  }

private:
  uint32_t m_enteredAtMs{0};
  uint8_t  m_index{0};
  bool     m_cup{false};
};

// =========================================
// MaintenanceState — פשוט; לא תלוי במחלקות שיבואו אחריו
// =========================================
class MaintenanceState final : public State {
public:
  static MaintenanceState& Instance() { static MaintenanceState s; return s; }

  StateId     Id()   const override { return StateId::Maintenance; }
  const char* Name() const override { return "Maintenance"; }

  void OnEnter(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) override {
    (void)dispenser; (void)nowMs; m_idx = 0; Draw_(ui);
  }

  void HandleButton(Dispenser& dispenser, nlrd::UserInterface& ui, const ButtonEvent& ev) override {
    if (ev.action != ButtonAction::Press) return;

    if (ev.buttonId == kBtnSelect) {
      Next_(ui);
    } else if (ev.buttonId == kBtnConfirm) {
      Run_(dispenser, ui);
    }
  }

  void Display(nlrd::UserInterface& ui) const override { Draw_(ui); }

private:
  MaintenanceState() = default;
  static constexpr uint8_t kSize = 3;

  void Draw_(nlrd::UserInterface& ui) const {
    static const char* kItems[kSize] = { "Prime", "Purge", "ValveTest" };
    ui.DisplayText("Maintenance", kItems[m_idx]);
  }

  void Next_(nlrd::UserInterface& ui) {
    if (m_idx + 1 < kSize) ++m_idx; else m_idx = 0;
    Draw_(ui);
  }

  void Run_(Dispenser& d, nlrd::UserInterface& ui) {
    switch (m_idx) {
      case 0: d.OpenValve(0); d.StartPump(1500); ui.DisplayText("Prime", "1500ms"); break;
      case 1: d.OpenValve(0); d.StartPump(800);  ui.DisplayText("Purge", "800ms");  break;
      case 2: d.OpenValve(0);                    ui.DisplayText("Valve", "Open");    break; // סגירה בטיק/זמן
      default: break;
    }
  }

private:
  uint8_t m_idx{0};
};

// =========================================
// IdleState — מוגדר אחרון (תלוי ב-Selecting/Maintenance)
// =========================================
class IdleState final : public State {
public:
  static IdleState& Instance() { static IdleState s; return s; }

  StateId     Id()   const override { return StateId::Idle; }
  const char* Name() const override { return "Idle"; }

  void OnEnter(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) override {
    (void)dispenser; (void)nowMs; m_enteredAtMs = millis(); ui.DisplayText("Ready", "Press/select");
  }

  void HandleTick(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) override {
    (void)dispenser; (void)ui; (void)nowMs; /* אופציונלי: heartbeat */
  }

  void HandleButton(Dispenser& dispenser, nlrd::UserInterface& ui, const ButtonEvent& ev) override {
    (void)ui;
    if (ev.action == ButtonAction::LongPress && ev.buttonId == kBtnSelect) {
      dispenser.SetState(GetMaintenance(), ev.timestampMs);
      return;
    }
    if (ev.action == ButtonAction::Press) {
      dispenser.SetState(GetSelecting(), ev.timestampMs);
    }
  }

  void Display(nlrd::UserInterface& ui) const override { ui.DisplayText("Soda Dispenser", "Waiting..."); }

private:
  IdleState() = default;
  uint32_t m_enteredAtMs{0};
};

// --- פונקציות עזר גלובליות כדי לא לחשוף שמות המחלקות ב-dispenser.cpp ---
State& GetIdle()        { return static_cast<State&>(IdleState::Instance()); }
State& GetSelecting()   { return static_cast<State&>(SelectingState::Instance()); }
State& GetDispensing()  { return static_cast<State&>(DispensingState::Instance()); }
State& GetMaintenance() { return static_cast<State&>(MaintenanceState::Instance()); }
State& GetError()       { return static_cast<State&>(ErrorState::Instance()); }

// --- מימוש פונקציות העזר החוצות ---
void SetDispenseRecipeIndex(uint8_t idx) { DispensingState::Instance().SetRecipeIndex(idx); }
void SetErrorSafetyTimeout()            { ErrorState::Instance().SetErrorCode(ErrorState::Code::SafetyTimeout); }
void SetErrorCupRemoved()               { ErrorState::Instance().SetErrorCode(ErrorState::Code::CupRemoved); }

} // namespace SodaDispenser
