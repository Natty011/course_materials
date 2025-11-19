// ui.cpp

#include <Arduino.h>              // pinMode, digitalWrite, delay
#include <Wire.h>                 // begin() - תקשורת I2C לתצוגה
#include <Adafruit_GFX.h>        // setTextSize, setTextColor, setCursor, print
#include <Adafruit_SSD1306.h>    // clearDisplay, display
#include <Servo.h>               // attach, write
#include <NewPing.h>             // מדידת מרחק ultrasonic (ping_cm)

#include "ui.h"                   // הגדרת המחלקה UserInterface

namespace nlrd {

// פונקציית עזר פרטית לקריאה ממצב כפתור בלחצן (debounce)
bool UserInterface::ReadButton(uint8_t pin) {
    constexpr unsigned int DEBOUNCE_DELAY_MS = 20; // זמן השהייה לסינון רעשים
    if (digitalRead(pin) == LOW) {
        delay(DEBOUNCE_DELAY_MS);
        return digitalRead(pin) == LOW;
    }
    return false;
}

// בנאי – כרגע לא מבצע פעולות, ניתן להעביר אליו בעתיד את Init() אם נרצה אוטומציה
UserInterface::UserInterface() {}

// אתחול של רכיבי חומרה – לחצנים, תצוגה, סרוו
void UserInterface::Init() {
    pinMode(PIN_BTN_SELECT, INPUT_PULLUP);
    pinMode(PIN_BTN_CONFIRM, INPUT_PULLUP);
    pinMode(PIN_LED, OUTPUT);

    m_servo.attach(PIN_SERVO);

    Wire.begin();
    m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    m_display.clearDisplay();
    m_display.setTextColor(SSD1306_WHITE);
    m_display.setTextSize(1);
    m_display.setCursor(0, 0);
    m_display.display();
}

// הדפסת טקסט לתצוגת OLED – שורת חובה (line1) ושורת רשות (line2)
void UserInterface::DisplayText(const String& line1, const String& line2) {
    m_display.clearDisplay();
    m_display.setCursor(0, 0);
    m_display.setTextSize(1);
    m_display.println(line1);
    if (!line2.isEmpty()) {
        m_display.println(line2);
    }
    m_display.display();
}

// ניקוי תצוגה בלבד (לשימוש חיצוני אם נרצה)
void UserInterface::ClearDisplay() {
    m_display.clearDisplay();
    m_display.display();
}

// בדיקת לחיצה על כפתור SELECT
bool UserInterface::IsSelectPressed() const {
    return ReadButton(PIN_BTN_SELECT);
}

// בדיקת לחיצה על כפתור CONFIRM
bool UserInterface::IsConfirmPressed() const {
    return ReadButton(PIN_BTN_CONFIRM);
}

// הדלקת/כיבוי LED
void UserInterface::SetLed(bool on) {
    digitalWrite(PIN_LED, on ? HIGH : LOW);
}

// הגדרת זווית לסרוו
void UserInterface::SetServoAngle(int angle) {
    m_servo.write(angle);
}

// מדידת מרחק באמצעות HC-SR04 – שימוש בספריית NewPing
long UserInterface::MeasureDistanceCM() const {
    NewPing sonar(PIN_TRIG, PIN_ECHO);
    return sonar.ping_cm();
}

} // namespace nlrd

