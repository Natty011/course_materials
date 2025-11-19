#include <Arduino.h> //Serial.begin / 
#include "sensor.h"  // 
#include "thermo_display.h" //

#define DHT_PIN (2)
#define DHT_TYPE (DHT22)

Sensor g_sensor(DHT_PIN, DHT_TYPE);
OledDisplay g_display;

void setup()
{
    Serial.begin(9600);
    delay(2000);
    Serial.println(F("=== Starting ThermoDisplay ==="));

    g_sensor.begin();

    if(!g_display.InitDisplay())
    {
        Serial.println(F("Display init failed"));
        while(true); // don't procced, don't move to the loop() function
    }

}

void loop()
{
    g_sensor.update();
    float temp = g_sensor.getTemperature();
    float humid = g_sensor.getHumidity();

    if(isnan(temp) || isnan(humid))
    {
        Serial.println(F("Sensor read error!"));
        g_display.ShowSensorData(0, 0);
    }
    else
    {
        Serial.print(F("Temp: "));
        Serial.print(temp);
        Serial.print(F(" | Hum: "));
        Serial.println(humid);

        g_display.ShowSensorData(temp, humid);
    }

    delay(2000); //For conveniate display's rate
}
