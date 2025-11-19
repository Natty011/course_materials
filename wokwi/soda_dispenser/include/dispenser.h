#ifndef SODADISPENSER_DISPENSER_H
#define SODADISPENSER_DISPENSER_H

// <Arduino.h> — נשתמש ב-millis() וב-String לתצוגה
#include <Arduino.h>      // millis(), String
// <stdint.h> — טיפוסים ברוחב קבוע
#include <stdint.h>       // uint8_t, uint16_t, uint32_t
// "state.h" — ממשק המצבים (State, ButtonEvent, SensorData)
#include "state.h"       // SodaDispenser::State, StateId, ButtonEvent, SensorData
// "ui.h" — שכבת קלט/פלט/דרייברים (לחצנים עם debounce, תצוגה, סנסור מרחק, סרוו)
#include "ui.h"          // nlrd::UserInterface: IsSelectPressed(), IsConfirmPressed(), DisplayText(), MeasureDistanceCM()

namespace SodaDispenser {

// מיפוי מזהי לחצנים לוגיים כדי לשמור על אחידות באירועים
enum : uint8_t { kBtnSelect = 1, kBtnConfirm = 2 };

// קדימה לשימוש קצר בשם מחלקת ה-UI
using UI = nlrd::UserInterface;

class Dispenser {
public:
  // הזרקת תלות ל-UI; מצב התחלתי ייקבע ב-Begin
  explicit Dispenser(UI& ui) : m_ui(ui) {}

  // אתחול מרכיבי המערכת (מאתחל UI, עובר ל-Idle)
  void Begin();

  // קריאה מחזורית מתוך loop() — קורא קלט מה-UI, מפיץ לאובייקט המצב הנוכחי ומצייר
  void Tick(uint32_t nowMs);

  // מעבר מצב — אחראי על קריאת OnExit/OnEnter של המצבים
  void SetState(State& next, uint32_t nowMs);

  // גישה למצב הנוכחי (לוגים/בדיקות)
  State& CurrentState() const { return *m_state; }

  // פעולות דומיין — מבוצעות דרך ה-UI, תוך שמירה על גבולות בטיחות (במימוש cpp)
  void StartPump(uint16_t ms);
  void StopPump();
  void OpenValve(uint8_t id);
  void CloseValve(uint8_t id);

  // תצוגה קצרה נוחה
  void Show(const char* line1, const char* line2 = nullptr);

  // קונפיגורציית טיימאאוטים/בטיחות — ניתן לכיול בעתיד
  uint32_t SelectingTimeoutMs() const { return m_selectingTimeoutMs; }
  uint32_t DispenseSafetyMs()  const { return m_dispenseSafetyMs; }

  // ספי חיישן — היגיון פשוט: כוס קיימת אם מרחק קטן מסף
  bool IsCupPresent() const;

  // הפצה של אירועי קלט (מופעלים מתוך Tick)
  void OnButton(const ButtonEvent& ev, uint32_t nowMs);
  void OnSensor(const SensorData& s, uint32_t nowMs);

private:
  // קריאת קלט לחצנים עם edge-detection (מייצר ButtonEvent נקיים מ-debounce)
  void ScanButtons_(uint32_t nowMs);
  void ScanSensors_(uint32_t nowMs);

  // עזרי לחיצה ארוכה
  void UpdateLongPress_(bool isDown, uint8_t btnId, uint32_t nowMs);

private:
  UI&     m_ui;          // ה-UI המוזרק
  State*  m_state{nullptr};

  // זיכרון לחצנים לצורך edge detection + לחיצה ארוכה
  bool     m_prevSelectDown{false};
  bool     m_prevConfirmDown{false};
  uint32_t m_selectPressedAtMs{0};
  uint32_t m_confirmPressedAtMs{0};

  // קונפיגורציה
  uint32_t m_selectingTimeoutMs{Defaults::SelectingTimeoutMs};
  uint32_t m_dispenseSafetyMs{Defaults::DispenseSafetyMs};

  // קירוב סף גילוי כוס בס״מ
  static constexpr long kCupPresentThresholdCm = 8; // עד 8 ס״מ נחשב כוס מוצבת
};

} // namespace SodaDispenser

#endif // SODADISPENSER_DISPENSER_H
