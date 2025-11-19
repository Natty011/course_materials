#ifndef SODADISPENSER_STATE_H
#define SODADISPENSER_STATE_H

// <Arduino.h> — נשתמש ב-millis(), ב-String ובסוגים בסיסיים של ארדואינו
#include <Arduino.h>
// <stdint.h> — נשתמש בסוגים שלמים בעלי רוחב קבוע: uint8_t, uint16_t, uint32_t
#include <stdint.h>
// "ui.h" — ממשק המשתמש: תצוגה, קריאת לחצנים/חיישנים וכד' (פונקציות תצוגה וקלט)
#include "ui.h"

// הימנעות מתלות צולבת: מצהירים קדימה במקום לכלול "dispenser.h"
class Dispenser;   // יבצע מעבר בין מצבים ויחזיק מצב נוכחי
class UserInterface; // קיים ב-ui.h; ההכרזה כאן למניעת תלות הדדית

// מזהה לוגי של מצב — יעזור לדיבוג וללוגים
enum class StateId : uint8_t {
  Idle = 0,
  Selecting,
  Dispensing,
  Maintenance,
  Error
};

// אירוע לחצן כללי
struct ButtonEvent {
  uint8_t id;          // מזהה הלחצן (לפי המיפוי בפרויקט)
  bool pressed;        // true כשהלחצן נלחץ; ניתן להרחיב ללחיצה/שחרור/החזקה
  uint32_t timestamp;  // millis() בעת האירוע
};

// עדכון חיישנים מרוכז (לדוגמה: HC-SR04 דרך NewPing, חיישן כוס, וכו')
struct SensorData {
  uint16_t distance_mm; // מרחק במ"מ (אם רלוונטי)
  bool cup_present;     // האם זוהתה כוס
};

// מחלקת בסיס אבסטרקטית לכל המצבים במכונה
// כל מצב מגדיר את התגובות שלו לאירועים ולהתזמונים, ואת תצוגת ה-UI שלו
class State {
 public:
  virtual ~State() = default;

  // מזהה סמנטי של המצב (לדיבוג/טסטים/טלמטריה)
  virtual StateId id() const = 0;

  // שם טקסטואלי קצר (להדפסה סריאלית/לוגים)
  virtual const char* name() const = 0;

  // כניסה למצב — נקרא ברגע המעבר למצב זה
  virtual void on_enter(Dispenser& disp, UserInterface& ui, uint32_t now_ms) = 0;

  // יציאה מהמצב — ברירת מחדל: אין פעולה. ניתן לדרוס במצבים שצריכים ניקוי/כיבוי משאבים
  virtual void on_exit(Dispenser& disp, UserInterface& ui, uint32_t now_ms) {
    (void)disp; (void)ui; (void)now_ms;
  }

  // אירוע מחזורי (tick) — נקרא כל N מילישניות ע"י ה-Dispenser
  // ברירת מחדל: אין פעולה
  virtual void handle_tick(Dispenser& disp, UserInterface& ui, uint32_t now_ms) {
    (void)disp; (void)ui; (void)now_ms;
  }

  // אירוע לחצן מה-UI
  virtual void handle_button(Dispenser& disp, UserInterface& ui, const ButtonEvent& ev) = 0;

  // עדכון ערכי חיישנים מה-UI/Driver — ברירת מחדל: אין פעולה
  virtual void handle_sensor_update(Dispenser& disp, UserInterface& ui, const SensorData& s) {
    (void)disp; (void)ui; (void)s;
  }

  // תצוגה למסך/LED וכו' — כל מצב מצייר את המידע הרלוונטי
  virtual void display(UserInterface& ui) const = 0;

  // אופציונלי: timeout/דד-ליין פנימי (למשל יציאה ממסך בחירה אחרי חוסר פעילות)
  // ברירת מחדל: אין
  virtual uint32_t inactivity_deadline_ms() const { return 0; }
};

#endif // SODADISPENSER_STATE_H
