#include <Arduino.h>
#include "sensor.h"
#include "thermo_display.h"

#define DHT_PIN 2
#define DHT_TYPE DHT22

Sensor g_sensor(DHT_PIN, DHT_TYPE);
OledDisplay g_display;

void setup() {
    Serial.begin(9600);
    delay(2000);
    Serial.println(F("=== Starting ThermoDisplay ==="));

    g_sensor.begin();

    if (!g_display.InitDisplay()) {
        Serial.println(F("Display init failed!"));
        while (true);  // עצור אם המסך לא מאותחל
    }
}

void loop() {
    g_sensor.update();
    float temp = g_sensor.getTemperature();
    float humid = g_sensor.getHumidity();

    if (isnan(temp) || isnan(humid)) {
        Serial.println(F("Sensor read error!"));
        g_display.ShowSensorData(0, 0);
    } else {
        Serial.print(F("Temp: "));
        Serial.print(temp);
        Serial.print(F(" | Hum: "));
        Serial.println(humid);

        g_display.ShowSensorData(temp, humid);
    }

    delay(2000);
}

//////// Another Option for loop()  ////////////////////////////////////////////
void loop() {
    g_sensor.update();
    float temp = g_sensor.getTemperature();
    float humid = g_sensor.getHumidity();

    // 🔸 בדיקה האם הקריאות תקינות (לא NaN)
    if (isnan(temp) || isnan(humid)) {
        Serial.println(F("Sensor read error (NaN)!"));
        g_display.ShowSensorData(0, 0);
        return;
    }

    // 🔸 בדיקה האם הערכים בטווחים הפיזיקליים הסבירים
    bool valid_temp = (temp >= -40 && temp <= 80);
    bool valid_hum  = (humid >= 0 && humid <= 100);

    if (!valid_temp || !valid_hum) {
        Serial.print(F("⚠️ Out of range: "));
        Serial.print(F("Temp="));
        Serial.print(temp);
        Serial.print(F(", Hum="));
        Serial.println(humid);

        // הצג הודעה ויזואלית במסך
        g_display.ShowSensorData(0, 0);
        return;
    }

    // 🔹 אם הכול תקין — הצג את הנתונים
    Serial.print(F("Temp: "));
    Serial.print(temp);
    Serial.print(F(" | Hum: "));
    Serial.println(humid);

    g_display.ShowSensorData(temp, humid);

    delay(2000);
}


///////////////////////////////////////////////////////////////////////






// לוגיקת הבקר המרכזי של ThermoDisplay

אתחול:
    צור אובייקט display
    צור אובייקט sensor עם pin 2
    קרא display.InitDisplay()
    קרא sensor.InitSensor()
    הצג "ThermoDisplay" בשורה 1
    הצג "Init..." בשורה 2

לולאה אינסופית:
    כל 2000ms:
        אם sensor.ReadOnce(temp, hum):
            הצג על המסך:
                שורה 1: "Temp(C): <temp>"
                שורה 2: "Hum(%):  <hum>"
        אחרת:
            הצג "Sensor Error"


////////////////////////////////////////////////////////////////////////////////
משתנים גלובליים:
    display : OledDisplay
    sensor  : SensorDht(pin=2)
    last_ms : unsigned long = 0
    interval_ms : const = 2000

setup():
    display.InitDisplay()
    display.ShowText("ThermoDisplay", "Init...")
    sensor.InitSensor()

loop():
    now = millis()
    אם (now - last_ms >= interval_ms):
        if sensor.ReadOnce(temp, hum):
            display.ShowText("Temp(C): " + format(temp,1),
                             "Hum(%):  " + format(hum,1))
        אחרת:
            display.ShowText("Sensor Error", "Check wiring")
        last_ms = now

