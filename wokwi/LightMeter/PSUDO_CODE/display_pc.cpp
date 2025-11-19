#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

class Display {
public:
  Display(uint8_t cs, uint8_t dc, uint8_t rst);
  void begin();
  void splash(const char* title = "LightMeter");
  void show(float lux, float percent, int analogVal, bool digitalState);

private:
  Adafruit_ILI9341 _tft;
  // ציור שכבת טקסט קבועה
  void drawStaticFrame();
  // הדפסה שמנקה רק את האזור הישן (ללא ריצוד)
  void printValue(int16_t x, int16_t y, const String& text,
                  uint16_t fg = ILI9341_WHITE, uint16_t bg = ILI9341_BLACK,
                  int16_t boxW = 110, int16_t boxH = 16);
  // בר התקדמות לאחוז אור
  void drawBar(int16_t x, int16_t y, int16_t w, int16_t h, float percent);
};


/////////////////////////////////////////////////////////////////////////////

#include "display.h"

Display::Display(uint8_t cs, uint8_t dc, uint8_t rst)
: _tft(cs, dc, rst) {}

void Display::begin() {
  _tft.begin();
  _tft.setRotation(1);            // לרוחב
  _tft.fillScreen(ILI9341_BLACK);
  drawStaticFrame();
}

void Display::splash(const char* title) {
  _tft.fillScreen(ILI9341_BLACK);
  _tft.setTextColor(ILI9341_CYAN);
  _tft.setTextSize(3);
  _tft.setCursor(20, 40);
  _tft.print(title);
  _tft.setTextSize(2);
  _tft.setCursor(20, 80);
  _tft.setTextColor(ILI9341_YELLOW);
  _tft.print("Initializing...");
}

void Display::drawStaticFrame() {
  _tft.fillScreen(ILI9341_BLACK);
  _tft.setTextSize(2);
  _tft.setTextColor(ILI9341_ORANGE);
  _tft.setCursor(10, 10);  _tft.print("LightMeter");

  _tft.setTextColor(ILI9341_LIGHTGREY);
  _tft.setCursor(10, 50);  _tft.print("Lux:");
  _tft.setCursor(10, 80);  _tft.print("Light %:");
  _tft.setCursor(10,110);  _tft.print("Analog:");
  _tft.setCursor(10,140);  _tft.print("Digital:");

  // מסגרת לבר האחוזים
  _tft.drawRect(120, 78, 180, 18, ILI9341_DARKGREY);
}

void Display::printValue(int16_t x, int16_t y, const String& text,
                         uint16_t fg, uint16_t bg, int16_t w, int16_t h) {
  _tft.fillRect(x, y, w, h, bg);       // נקה אזור קודם
  _tft.setTextColor(fg);
  _tft.setTextSize(2);
  _tft.setCursor(x, y);
  _tft.print(text);
}

void Display::drawBar(int16_t x, int16_t y, int16_t w, int16_t h, float p) {
  if (p < 0) p = 0; if (p > 100) p = 100;
  int filled = (int)(w * (p / 100.0f));
  _tft.fillRect(x, y, w, h, ILI9341_BLACK);       // נקה
  _tft.fillRect(x, y, filled, h, ILI9341_GREEN);  // מלא
  _tft.drawRect(x, y, w, h, ILI9341_DARKGREY);    // מסגרת
}

void Display::show(float lux, float percent, int analogVal, bool digitalState) {
  // ערכים
  printValue(120, 50, String(lux, 1));            // Lux
  printValue(310, 50, "lx", ILI9341_DARKGREY);    // יחידות קטנות בצד אם רוצים

  drawBar(120, 78, 180, 18, percent);
  printValue(310, 78, String(percent, 1) + "%");

  printValue(120,110, String(analogVal));
  printValue(120,140, digitalState ? "HIGH" : "LOW",
             digitalState ? ILI9341_GREEN : ILI9341_RED);
}

//////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include "display.h"

// פינים למסך (לפי מה שהשתמשת בו אתמול)
#define TFT_CS  10
#define TFT_DC   9
#define TFT_RST  8

Display g_display(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("Display test start");

  g_display.begin();
  g_display.splash("Display Test");
  delay(1500);

  // ציור ראשוני של המסגרת
  g_display.show(0, 0, 0, false);
}

void loop() {
  // בדיקה דינמית של המסך: ערכים משתנים כמו בגרף
  static float lux = 0;
  static bool  state = false;

  lux += 5;
  if (lux > 1000) {
    lux = 0;
    state = !state;
  }

  float percent = (lux / 1000.0f) * 100.0f;
  int analogVal = map(lux, 0, 1000, 0, 1023);

  g_display.show(lux, percent, analogVal, state);

  delay(150);
}


//////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include "sensor.h"      // המחלקה שלך
#include "display.h"     // הקבצים שלמעלה

// --- Pins ---
#define A_PIN   A0
#define D_PIN   2
#define TFT_CS  10
#define TFT_DC  9
#define TFT_RST 8

// --- Objects ---
Sensor  g_light_sensor(A_PIN, D_PIN);
Display g_ui(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  g_ui.begin();
  g_ui.splash();
  delay(800);
  // מסך ראשי
  // (drawStaticFrame() נקרא ב-begin)
}

void loop() {
  int   a   = g_light_sensor.ReadAnalog();
  bool  d   = g_light_sensor.ReadDigital();
  float lux = g_light_sensor.ComputeLux(a);
  float p   = g_light_sensor.GetLightLevelPercent();

  g_ui.show(lux, p, a, d);

  // אופציונלי: דיבוג לסריאל
  // g_light_sensor.PrintDebug();

  delay(150);
}

