#include <Arduino.h>
#include "sensor.h"   // כולל את המחלקה שלך

Sensor g_sensor(2, DHT22);

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("=== Starting Sensor Test ===");

  g_sensor.begin();
  g_sensor.update();

  float t = g_sensor.getTemperature();
  float h = g_sensor.getHumidity();

  Serial.print("Temperature: ");
  Serial.println(t);
  Serial.print("Humidity: ");
  Serial.println(h);

  if (isnan(t) || isnan(h)) {
    Serial.println("[FAIL] Sensor returned NaN values");
  } else if (t < -40 || t > 80 || h < 0 || h > 100) {
    Serial.println("[FAIL] Sensor values out of range");
  } else {
    Serial.println("[PASS] Sensor initialized and values OK");
  }
}

void loop() {
    g_sensor.update();          // זה ימשוך קריאה כל ~2 שניות לפי המימוש שלך
    Serial.print("Temp: ");
    Serial.print(g_sensor.getTemperature());
    Serial.print(" | Hum: ");
    Serial.println(g_sensor.getHumidity());
    delay(2000);                 // רק לקצב פלט נוח
  }
  
