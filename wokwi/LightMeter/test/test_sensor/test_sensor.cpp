#include <Arduino.h>
#include "sensor.h"

#define DO_PIN 2

Sensor g_light_sensor(A0, DO_PIN);

void setup()
{
  Serial.begin(115200);
  Serial.println("LightMeter Sensor Test");
}

void loop()
{
  int analog_value = g_light_sensor.ReadAnalog();
  g_light_sensor.ReadDigital();
  float lux = g_light_sensor.ComputeLux(analog_value);
  float percent = g_light_sensor.GetLightLevelPercent();

  g_light_sensor.PrintDebug();

   // הדפסה לגרף (טאבים מפרידים בין הערכים)
   Serial.print(millis());
   Serial.print("\t");
   Serial.print(analog_value);
   Serial.print("\t");
   Serial.print(lux);
   Serial.print("\t");
   Serial.println(percent);

   //delay(100); // קצב רענון 10 פעמים בשנייה

  delay(500);
}