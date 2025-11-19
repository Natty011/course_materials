#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

namespace nlrd {

class UserInterface {
public:
    static constexpr uint8_t PIN_BTN_SELECT  = 2;
    static constexpr uint8_t PIN_BTN_CONFIRM = 3;
    static constexpr uint8_t PIN_LED         = 5;
    static constexpr uint8_t PIN_SERVO       = 9;

    static constexpr uint8_t PIN_TRIG  = 6;
    static constexpr uint8_t PIN_ECHO  = 7;

    static constexpr uint8_t OLED_WIDTH  = 128;
    static constexpr uint8_t OLED_HEIGHT = 64;

    explicit UserInterface();

    void Init();

    void DisplayText(const String& line1, const String& line2 = "");
    void ClearDisplay();

    bool IsSelectPressed() const;
    bool IsConfirmPressed() const;

    void SetLed(bool on);

    void SetServoAngle(int angle);

    long MeasureDistanceCM() const;

private:
    Servo m_servo;
    Adafruit_SSD1306 m_display;

    static bool ReadButton(uint8_t pin);
};

} // namespace nlrd

#endif // UI_H

