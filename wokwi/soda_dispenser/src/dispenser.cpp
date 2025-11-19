// <Arduino.h> — millis(), delay, String
#include <Arduino.h>   // millis(), delay, String
// <stdint.h> — טיפוסים ברוחב קבוע
#include <stdint.h>    // uint8_t, uint16_t, uint32_t
// "dispenser.h" — הצהרת המחלקה וה-API הציבורי
#include "dispenser.h"  // SodaDispenser::Dispenser
// "state.h" — כדי לקרוא ל-OnEnter/OnExit/Handle*
#include "state.h"      // SodaDispenser::State, ButtonEvent, SensorData
// "ui.h" — פעולות קלט/פלט (לחצנים אחרי debounce, תצוגה, חיישן מרחק)
#include "ui.h"         // nlrd::UserInterface

namespace SodaDispenser {

// --- הצהרות קדימה למצבי ברירת המחדל (סינגלטונים) כפי שממומשים ב-state.cpp ---
class State;
State& GetIdle();
State& GetSelecting();
State& GetDispensing();
State& GetMaintenance();
State& GetError();

using UI = nlrd::UserInterface;

void Dispenser::Begin()
{
  // אתחול UI וכניסה ל-Idle
  m_ui.Init();
  m_state = &GetIdle();
  m_state->OnEnter(*this, m_ui, millis());
}

void Dispenser::Tick(uint32_t nowMs)
{
  // 1) קלט לחצנים/חיישנים → אירועים
  ScanButtons_(nowMs);
  ScanSensors_(nowMs);

  // 2) tick למצבים + ציור
  m_state->HandleTick(*this, m_ui, nowMs);
  m_state->Display(m_ui);
}

void Dispenser::SetState(State& next, uint32_t nowMs)
{
  if (m_state == &next) return; // אין מעבר עצמי
  if (m_state) m_state->OnExit(*this, m_ui, nowMs);
  m_state = &next;
  m_state->OnEnter(*this, m_ui, nowMs);
}

// --- פעולות דומיין דרך ה-UI (כרגע דמה/עטיפות; ניתן להחליף לדרייברים אמיתיים) ---
void Dispenser::StartPump(uint16_t ms)
{
  (void)ms; // TODO: לחבר למשאבה אמיתית כשיהיה
  // כרגע נשתמש בלד/סרוו כהדמיה – לדוגמה נדליק LED לזמן נתון
  m_ui.SetLed(true);
}

void Dispenser::StopPump()
{
  m_ui.SetLed(false);
}

void Dispenser::OpenValve(uint8_t id)
{
  (void)id; // TODO: לחבר לשסתומים אמיתיים
  m_ui.SetServoAngle(40);
}

void Dispenser::CloseValve(uint8_t id)
{
  (void)id;
  m_ui.SetServoAngle(0);
}

void Dispenser::Show(const char* line1, const char* line2)
{
  const String l1 = line1 ? String(line1) : String("");
  const String l2 = line2 ? String(line2) : String("");
  m_ui.DisplayText(l1, l2);
}

bool Dispenser::IsCupPresent() const
{
  const long cm = m_ui.MeasureDistanceCM();
  return (cm > 0) && (cm <= kCupPresentThresholdCm);
}

void Dispenser::OnButton(const ButtonEvent& ev, uint32_t nowMs)
{
  (void)nowMs;
  m_state->HandleButton(*this, m_ui, ev);
}

void Dispenser::OnSensor(const SensorData& s, uint32_t nowMs)
{
  (void)nowMs;
  m_state->HandleSensorUpdate(*this, m_ui, s);
}

// --- קריאת קלט והפיכתו לאירועים (edge-detection + long-press) ---
void Dispenser::ScanButtons_(uint32_t nowMs)
{
  const bool selectDown  = m_ui.IsSelectPressed();
  const bool confirmDown = m_ui.IsConfirmPressed();

  // SELECT
  if (selectDown && !m_prevSelectDown) {
    m_selectPressedAtMs = nowMs;
    OnButton(ButtonEvent{ kBtnSelect, ButtonAction::Press, nowMs }, nowMs);
  } else if (!selectDown && m_prevSelectDown) {
    OnButton(ButtonEvent{ kBtnSelect, ButtonAction::Release, nowMs }, nowMs);
  } else if (selectDown && (nowMs - m_selectPressedAtMs) >= 800u) {
    // long-press פעם בכניסה הראשונה לסף
    if (m_prevSelectDown && m_selectPressedAtMs != 0) {
      OnButton(ButtonEvent{ kBtnSelect, ButtonAction::LongPress, nowMs }, nowMs);
      m_selectPressedAtMs = 0; // מניעת ירי חוזר
    }
  }
  m_prevSelectDown = selectDown;

  // CONFIRM
  if (confirmDown && !m_prevConfirmDown) {
    m_confirmPressedAtMs = nowMs;
    OnButton(ButtonEvent{ kBtnConfirm, ButtonAction::Press, nowMs }, nowMs);
  } else if (!confirmDown && m_prevConfirmDown) {
    OnButton(ButtonEvent{ kBtnConfirm, ButtonAction::Release, nowMs }, nowMs);
  } else if (confirmDown && (nowMs - m_confirmPressedAtMs) >= 1200u) {
    if (m_prevConfirmDown && m_confirmPressedAtMs != 0) {
      OnButton(ButtonEvent{ kBtnConfirm, ButtonAction::LongPress, nowMs }, nowMs);
      m_confirmPressedAtMs = 0;
    }
  }
  m_prevConfirmDown = confirmDown;
}

void Dispenser::ScanSensors_(uint32_t nowMs)
{
  (void)nowMs;
  SensorData s{};
  s.cupPresent = IsCupPresent();
  const long cm = m_ui.MeasureDistanceCM();
  s.distanceMm = (cm > 0) ? static_cast<uint16_t>(cm * 10) : 0u;
  OnSensor(s, nowMs);
}

} // namespace SodaDispenser
