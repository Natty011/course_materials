תזכורת על החיבור הפיזי

חיישן ה־LDR שלך כולל גם פלט DO (Digital Output) שמחובר ל־D2.
זה אומר שיש לנו שני ערוצים:

AO → A0 – קריאה אנלוגית מדויקת (0–1023)

DO → D2 – קריאה בינארית (HIGH/LOW) לפי הסף שנקבע בפוטנציומטר שעל המודול

נשתמש בשניהם במחלקת Sensor.

🚀 הצעד הבא

ממליץ להתחיל כך:

ליצור את המחלקה Sensor:

בנאי שמקבל את פיני ה־AO וה־DO.

פונקציה ReadAnalog() – מחזירה ערך float/uint16_t.

פונקציה ReadDigital() – מחזירה bool.

פונקציה GetLightLevelPercent() – ממירה את הערך לטווח 0–100%.

לאחר מכן נעבור למחלקת Display:

בנאי שמאתחל את ה־TFT.

פונקציה ShowValue() – מציגה ערך ומציירת פס בהתאם.

ולבסוף main.cpp שישלב ביניהן.


////////////////////////////////////////////////////////////////////////////////////
#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor {
private:
    int m_analog_pin;       // פין האנלוגי (A0)
    int m_digital_pin;      // פין הדיגיטלי (D2)
    int m_last_analog;      // הערך האנלוגי האחרון שנמדד
    bool m_last_digital;    // הערך הבינארי האחרון שנמדד (true=HIGH)
    float m_last_lux;       // ערך הלוקס האחרון שחושב

public:
    // 🔹 בנאי
    Sensor(int analog_pin, int digital_pin);

    // 🔹 פונקציות קריאה מהחיישן
    int ReadAnalog();
    bool ReadDigital();

    // 🔹 פונקציות חישוב ועיבוד נתונים
    float ComputeLux(int analog_value);      // חישוב לוקסים לפי הנוסחה הפיזיקלית
    float GetLightLevelPercent() const;      // אחוז עוצמת אור (0–100%)

    // 🔹 פונקציה לעוזרת לדיבוג
    void PrintDebug() const;
};

#endif


///////////////////////////////////////////////////////////////////////////////////////
#include "sensor.h"

// ערכי כיול (לפי הדוקומנטציה של Wokwi)
static const float GAMMA = 0.7f;
static const float RL10  = 50.0f;  // קילו-אוהם

// 🔹 בנאי
Sensor::Sensor(int analog_pin, int digital_pin)
    : m_analog_pin(analog_pin),
      m_digital_pin(digital_pin),
      m_last_analog(0),
      m_last_digital(false),
      m_last_lux(0.0f)
{
    pinMode(m_digital_pin, INPUT);
}

// 🔹 קריאה אנלוגית
int Sensor::ReadAnalog() {
    m_last_analog = analogRead(m_analog_pin);
    return m_last_analog;
}

// 🔹 קריאה דיגיטלית
bool Sensor::ReadDigital() {
    m_last_digital = (digitalRead(m_digital_pin) == HIGH);
    return m_last_digital;
}

// 🔹 חישוב ערך לוקס
float Sensor::ComputeLux(int analog_value) {
    float voltage = analog_value / 1024.0f * 5.0f;
    float resistance = 2000 * voltage / (1.0f - voltage / 5.0f);
    float lux = pow(RL10 * 1e3f * pow(10.0f, GAMMA) / resistance, (1.0f / GAMMA));

    // הגנה מפני ערכים לא סופיים
    if (!isfinite(lux)) lux = 0.0f;

    m_last_lux = lux;
    return lux;
}

// 🔹 המרת ערך לאחוז (0–100)
float Sensor::GetLightLevelPercent() const {
    // חישוב ישיר מהערך האנלוגי האחרון (0–1023)
    float percent = (m_last_analog / 1023.0f) * 100.0f;

    // הבטחת תחום תקין
    if (percent < 0.0f) percent = 0.0f;
    if (percent > 100.0f) percent = 100.0f;

    return percent;
}

// 🔹 דיבוג – הדפסה לסריאל
void Sensor::PrintDebug() const {
    Serial.print("Analog: ");
    Serial.print(m_last_analog);
    Serial.print(" | Digital: ");
    Serial.print(m_last_digital ? "HIGH" : "LOW");
    Serial.print(" | Lux: ");
    Serial.print(m_last_lux);
    Serial.print(" | Light %: ");
    Serial.println(GetLightLevelPercent());
}
/////////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include "sensor.h"

Sensor lightSensor(A0, 2);

void setup() {
    Serial.begin(115200);
    Serial.println("LightMeter Sensor Test");
}

void loop() {
    int analogValue = lightSensor.ReadAnalog();
    lightSensor.ReadDigital();
    lightSensor.ComputeLux(analogValue);
    lightSensor.PrintDebug();

    delay(500);
}

/////////////////////////////////////////////////////////////////////////////////////



מחלקה: Sensor
----------------------------

שדות (members):
    m_analog_pin   ← מספר הפין האנלוגי (A0)
    m_digital_pin  ← מספר הפין הדיגיטלי (D2)
    m_last_analog  ← הערך האנלוגי האחרון שנמדד
    m_last_digital ← הערך הבינארי האחרון שנמדד (true / false)

פונקציות ציבוריות (public):

    בנאי (Constructor):
        קבל את מספרי הפינים (אנלוגי ודיגיטלי)
        שמור אותם כחלק מהאובייקט
        הגדר את הפין הדיגיטלי כקלט (pinMode)

    פונקציה: ReadAnalog()
        קרא ערך מהפין האנלוגי באמצעות analogRead
        שמור את הערך במשתנה m_last_analog
        החזר את הערך

    פונקציה: ReadDigital()
        קרא מצב מהפין הדיגיטלי באמצעות digitalRead
        שמור את הערך במשתנה m_last_digital
        החזר true אם HIGH, אחרת false

    פונקציה: GetLightLevelPercent()
        המר את הערך האנלוגי האחרון לטווח 0–100 אחוז
        השתמש בנוסחה:
            אחוז = (m_last_analog / 1023.0) * 100
        החזר את הערך המעוגל או float עם שתי ספרות אחרי הנקודה

    פונקציה: PrintDebug()
        הדפס ל־Serial את הערכים הנוכחיים (אנלוגי ודיגיטלי)
        לדוגמה:
            "Analog: 723 | Digital: HIGH | Light: 70%"

פונקציות פרטיות (private):
    כרגע אין צורך — אפשר להוסיף בעתיד פונקציות עזר כמו Normalize() או Filter().

