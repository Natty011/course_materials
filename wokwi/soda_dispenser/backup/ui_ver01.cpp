#include "ui.h"

using namespace nlrd;

// ספרייה: Arduino.h  → pinMode, digitalWrite, delay
// ספרייה: Servo.h    → attach, write
// ספרייה: Adafruit_SSD1306.h → display.clearDisplay, display.setCursor, display.print, display.display

UserInterface::UserInterface()
{
  m_servo.attach(PIN_SERVO);
  m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  m_display.clearDisplay();
  m_display.display();
}

void UserInterface::Init()
{
    pinMode(PIN_BTN_SELECT, INPUT_PULLUP);
    pinMode(PIN_BTN_CONFIRM, INPUT_PULLUP);
    pinMode(PIN_LED, OUTPUT);

    m_servo.attach(PIN_SERVO);
    m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    m_display.clearDisplay();
    m_display.display();
}

void UserInterface::DisplayText(const String& line1, const String& line2)
{
    m_display.clearDisplay();
    m_display.setTextSize(1);
    m_display.setTextColor(SSD1306_WHITE);
    m_display.setCursor(0, 0);
    m_display.print(line1);
    m_display.setCursor(0, 10);
    m_display.print(line2);
    m_display.display();
}

void UserInterface::ClearDisplay()
{
    m_display.clearDisplay();
    m_display.display();
}

bool UserInterface::IsSelectPressed() const
{
    return ReadButton(PIN_BTN_SELECT);
}

bool UserInterface::IsConfirmPressed() const
{
    return ReadButton(PIN_BTN_CONFIRM);
}

void UserInterface::SetLed(bool on)
{
    digitalWrite(PIN_LED, on ? HIGH : LOW);
}

void UserInterface::SetServoAngle(int angle)
{
    m_servo.write(angle);
}

long UserInterface::MeasureDistanceCM() const
{
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    long duration = pulseIn(PIN_ECHO, HIGH);
    return duration * 0.034 / 2;
}

// 🧠 פונקציית debounce כמו שהסברנו
bool UserInterface::ReadButton(uint8_t pin)
{
    if (digitalRead(pin) == LOW)
    {
        delay(50); // debounce delay
        return digitalRead(pin) == LOW;
    }
    return false;
}

