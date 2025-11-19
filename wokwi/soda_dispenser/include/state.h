#ifndef SODADISPENSER_STATE_H
#define SODADISPENSER_STATE_H

// <Arduino.h> — נשתמש ב-millis()‎ לזמני מערכת וב-String לסטרינגים קלים
#include <Arduino.h>   // millis(), String
// <stdint.h> — סוגים בעלי רוחב קבוע (uint8_t/16_t/32_t)
#include <stdint.h>    // uint8_t, uint16_t, uint32_t
// "ui.h" — שכבת קלט/פלט: תצוגה, לחצנים, חיישנים, דרייברים
#include "ui.h"        // UserInterface: DisplayText(...), PollButton(...), ReadSensors(...)

// הימנעות מתלות צולבת: הצהרות קדימה — אין כאן #include ל-"dispenser.h"

// מחזיק מצב נוכחי ומבצע מעבר בין מצבים
namespace nlrd { class UserInterface; }   // ← ה-UI שלך 
// מוגדרת ב-ui.h; ממשק לקלט/פלט/דרייברים
namespace SodaDispenser { class Dispenser; }

namespace SodaDispenser {

// ערכי ברירת מחדל משותפים — זמני בטיחות וטיים-אאוטים
namespace Defaults {
  constexpr uint32_t SelectingTimeoutMs = 20000; // חוסר פעילות במסך בחירה
  constexpr uint32_t DispenseSafetyMs   = 6000;  // גבול עליון למזיגה
}

// מזהה סמנטי של מצב (לדיבוג/טלמטריה/בדיקות)
enum class StateId : uint8_t {
  Idle = 0,
  Selecting,
  Dispensing,
  Maintenance,
  Error
};

// פעולת לחצן — מאפשר אפיון נקי של אירועי קלט
enum class ButtonAction : uint8_t {
  Press,       // לחיצה קצרה
  Release,     // שחרור
  LongPress    // לחיצה ארוכה (אחרי debounce + סף זמן)
};

// אירוע לחצן לאחר טיפול ב-debounce בשכבת ה-UI (ולא כאן)
struct ButtonEvent {
  uint8_t      buttonId;     // מזהה לוגי של הכפתור (ממופה ב-UI)
  ButtonAction action;       // Press/Release/LongPress
  uint32_t     timestampMs;  // millis() בעת האירוע
};

// נתוני חיישנים מרוכזים לקריאה אטומית אחת מה-UI
struct SensorData {
  uint16_t distanceMm;   // לדוגמה HC-SR04 (אם בשימוש)
  bool     cupPresent;   // האם יש כוס
};

// מחלקת בסיס אבסטרקטית לכל מצבי המכונה (State Pattern)
// אחריות: להגדיר Hooks שמצבים יממשו; אין לוגיקה של דרייברים כאן.
class State {
public:
  virtual ~State() = default;

  // מזהה/שם — לדיבוג וללוגים
  virtual StateId    Id()   const = 0;
  virtual const char*Name() const = 0;

  // כניסה/יציאה מהמצב — נקראות ע"י Dispenser בעת מעבר מצב
  virtual void OnEnter(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) = 0;
  virtual void OnExit (Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) {
    (void)dispenser; (void)ui; (void)nowMs; // ברירת מחדל: ללא פעולה
  }

  // לולאת זמן — נקראת מחזורית ע"י Dispenser
  virtual void HandleTick(Dispenser& dispenser, nlrd::UserInterface& ui, uint32_t nowMs) {
    (void)dispenser; (void)ui; (void)nowMs; // ברירת מחדל: ללא פעולה
  }

  // קלט — אירועי לחצן/חיישנים מגיעים מה-UI (אחרי debounce/פילטרים)
  virtual void HandleButton(Dispenser& dispenser, nlrd::UserInterface& ui, const ButtonEvent& ev) = 0;
  virtual void HandleSensorUpdate(Dispenser& dispenser, nlrd::UserInterface& ui, const SensorData& s) {
    (void)dispenser; (void)ui; (void)s; // ברירת מחדל: ללא פעולה
  }

  // פלט — כל מצב מצייר בעצמו את ממשק המשתמש הרלוונטי לו
  virtual void Display(nlrd::UserInterface& ui) const = 0;

  // דד-ליין לאי-פעילות (אופציונלי). 0 = אין מגבלה ע"פ ברירת מחדל
  virtual uint32_t InactivityDeadlineMs() const { return 0; }
};

} // namespace SodaDispenser

#endif // SODADISPENSER_STATE_H
