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
Display g_ui(TFT_CS, TFT_DC);

void setup() {
  Serial.begin(115200);
  g_ui.begin();
  //g_ui.splash();
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
   g_light_sensor.PrintDebug();

  delay(150);
}
