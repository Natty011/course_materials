///////////////sensor.h////////////////////////////////////////////////
#ifndef SENSOR_H
#define SENSOR_H

// --------------------------------------------
// ספרייה: DHT.h
// נועדה לתקשורת עם חיישני DHT11/DHT22
// מספקת את המחלקה DHT עם פונקציות כמו readTemperature(), readHumidity()
// --------------------------------------------
#include <DHT.h>
#include <Arduino.h>  // נדרש לסוגים כמו uint8_t ו־millis()

class Sensor {
private:
    DHT m_dht;                    // מופע החיישן DHT
    float m_temperature;          // ערך הטמפרטורה האחרון שנקרא
    float m_humidity;             // ערך הלחות האחרון שנקרא
    unsigned long m_last_read_time; // זמן הקריאה האחרון (ms)

public:
    // 🔹 בנאי: מקבל את הפין ואת סוג החיישן (למשל DHT22)
    Sensor(uint8_t pin, uint8_t type);

    // 🔹 אתחול הסנסור - חובה לקרוא פעם אחת ב־setup()
    void begin();

    // 🔹 קריאת נתונים חדשה אם עבר מספיק זמן (2 שניות)
    void update();

    // 🔹 גטרים לערכים האחרונים
    float getTemperature() const;
    float getHumidity() const;

private:
    // 🔹 קריאה ישירה מהחיישן (נקראת מתוך update)
    void readSensor();
};

#endif // SENSOR_H


///////////////sensor.cpp////////////////////////////////////////////////
#include "sensor.h"

// 🔹 קונסטרקטור
Sensor::Sensor(uint8_t pin, uint8_t type)
    : m_dht(pin, type), m_temperature(0.0f), m_humidity(0.0f), m_last_read_time(0)
{}

// 🔹 אתחול הסנסור
void Sensor::begin() {
    m_dht.begin();
}

// 🔹 עדכון ערכים (כל 2 שניות)
void Sensor::update() {
    unsigned long current_time = millis();

    // בדיקה אם עברו לפחות 2 שניות מאז הקריאה האחרונה
    if (current_time - m_last_read_time >= 2000) {
        readSensor();
        m_last_read_time = current_time;
    }
}

// 🔹 פונקציה פנימית לקריאת ערכים מהחיישן
void Sensor::readSensor() {
    float t = m_dht.readTemperature();
    float h = m_dht.readHumidity();

    // בדיקה אם הערכים חוקיים
    if (!isnan(t) && !isnan(h)) {
        m_temperature = t;
        m_humidity = h;
    }
    
}

// 🔹 Getter לטמפרטורה
float Sensor::getTemperature() const {
    return m_temperature;
}

// 🔹 Getter ללחות
float Sensor::getHumidity() const {
    return m_humidity;
}


///////////////test/test_sensor/test_sensor.cpp////////////////////////////////////////////////
#include <Arduino.h>
#include <unity.h>   // ספריית בדיקות של PlatformIO
#include "sensor.h"

// ----------------------------------------------------
// הגדרות לחיישן
// ----------------------------------------------------
#define DHT_PIN 2
#define DHT_TYPE DHT22

// יצירת אובייקט גלובלי לבדיקה
Sensor sensor(DHT_PIN, DHT_TYPE);

// ----------------------------------------------------
// פונקציות אתחול וניקוי לכל טסט
// ----------------------------------------------------
void setUp() {
    sensor.begin(); // מאתחל לפני כל טסט
}

void tearDown() {
    // אם נדרש ניקוי משאבים (לא חובה כאן)
}

// ----------------------------------------------------
// טסט 1: בדיקת אתחול החיישן
// ----------------------------------------------------
void test_sensor_initialization() {
    sensor.begin();
    delay(2000);  // זמן המתנה לייצוב הקריאה הראשונה
    sensor.update();

    float temp = sensor.getTemperature();
    float hum  = sensor.getHumidity();

    // ודא שהערכים לא NaN
    TEST_ASSERT_FALSE(isnan(temp));
    TEST_ASSERT_FALSE(isnan(hum));

    // ודא שהם בטווח הגיוני
    TEST_ASSERT(temp >= -40 && temp <= 80);
    TEST_ASSERT(hum >= 0 && hum <= 100);
}

// ----------------------------------------------------
// טסט 2: בדיקת שמירה ויציבות של נתונים
// ----------------------------------------------------
void test_sensor_update_interval() {
    sensor.update();
    float old_temp = sensor.getTemperature();
    float old_hum  = sensor.getHumidity();

    // קריאה מיידית שנייה לא אמורה לשנות ערכים
    sensor.update();
    float new_temp = sensor.getTemperature();
    float new_hum  = sensor.getHumidity();

    TEST_ASSERT_EQUAL_FLOAT(old_temp, new_temp);
    TEST_ASSERT_EQUAL_FLOAT(old_hum, new_hum);
}

// ----------------------------------------------------
// פונקציית setup של סביבת הטסטים
// ----------------------------------------------------
void setup() {
    delay(2000);       // זמן חימום המערכת
    UNITY_BEGIN();     // התחלת ריצת הבדיקות
    RUN_TEST(test_sensor_initialization);
    RUN_TEST(test_sensor_update_interval);
    UNITY_END();       // סיום הבדיקות
}

void loop() {
    // אין צורך בלולאה כאן
}
//////////////////////////////////////////////////////////////////////

| קובץ              | תפקיד        | הערות                                         |
| ----------------- | ------------ | --------------------------------------------- |
| `sensor.h`        | ממשק המחלקה  | כולל DHT, Arduino, הגדרות מחלקה               |
| `sensor.cpp`      | מימוש מלא    | כולל בקרת תזמון וקריאה אמיתית מה־DHT          |
| `test_sensor.cpp` | בדיקות יחידה | מאתחל, בודק ערכים תקינים ובדיקת יציבות קריאות |


🧭 השלב הבא

ודא שבתיקיית הפרויקט יש תיקייה בשם test/test_sensor/.

שים שם את הקובץ test_sensor.cpp.

הרץ:

pio test -e uno
עקוב אחר הפלט ב־Serial Monitor — אתה אמור לראות:
[PASSED] test_sensor_initialization
[PASSED] test_sensor_update_interval




































#ifndef SENSOR_H
#define SENSOR_H

// הערות לכל include:
#include <DHT.h>        // מספקת את המחלקה DHT ואת הפונקציות readTemperature(), readHumidity()

class Sensor {
private:
    DHT m_dht;           // מופע של חיישן DHT
    float m_temperature; // מאחסן את הערך האחרון של טמפרטורה
    float m_humidity;    // מאחסן את הערך האחרון של לחות
    unsigned long m_last_read_time; // שומר מתי הייתה הקריאה האחרונה (לניהול תזמון)

public:
    // בנאי - מקבל את הפין של הסנסור ואת סוגו (DHT22)
    Sensor(uint8_t pin, uint8_t type);

    // אתחול הסנסור (לקריאה ב־setup)
    void begin();

    // פונקציה לעדכון הקריאות (מתבצעת כל פרק זמן מסוים)
    void update();

    // פונקציות גישה לערכים שנקראו
    float getTemperature() const;
    float getHumidity() const;

private:
    // פונקציה פנימית לקריאה אמיתית מהחיישן (מבוצעת בתוך update)
    void readSensor();
};

#endif

///////////////sensor.cpp////////////////////////////////////////////////
#include "sensor.h"

// קונסטרקטור - מאתחל את החיישן
Sensor::Sensor(uint8_t pin, uint8_t type)
    : m_dht(pin, type), m_temperature(0.0f), m_humidity(0.0f), m_last_read_time(0)
{}

// אתחול הסנסור
void Sensor::begin() {
    m_dht.begin();
}

// קריאת נתונים מהחיישן כל 2 שניות
void Sensor::update() {
    unsigned long current_time = millis();
    if (current_time - m_last_read_time >= 2000) {
        readSensor();
        m_last_read_time = current_time;
    }
}

// קריאה אמיתית מהחיישן
void Sensor::readSensor() {
    float t = m_dht.readTemperature();
    float h = m_dht.readHumidity();

    // בדיקה אם הערכים תקינים (לא NaN)
    if (!isnan(t) && !isnan(h)) {
        m_temperature = t;
        m_humidity = h;
    }
}

// גטרים
float Sensor::getTemperature() const { return m_temperature; }
float Sensor::getHumidity() const { return m_humidity; }


///////////////sensor_test.cpp////////////////////////////////////////////////
#include <Arduino.h>
#include <unity.h>
#include "sensor.h"

// נגדיר פין לחיישן
#define DHT_PIN 2
#define DHT_TYPE DHT22

Sensor sensor(DHT_PIN, DHT_TYPE);

void setUp() {
    sensor.begin();
}

void test_sensor_initialization() {
    TEST_ASSERT_TRUE(true); // אם הגענו לכאן בלי קריסה – עבר
}

void test_sensor_update_and_values() {
    sensor.update();
    float temp = sensor.getTemperature();
    float hum = sensor.getHumidity();
    
        // בדוק שהערכים לא NaN (קריאה תקינה)
    TEST_ASSERT_FALSE(isnan(temp));
    TEST_ASSERT_FALSE(isnan(hum));
    

    // לוודא שהערכים בטווח הגיוני
    TEST_ASSERT(temp >= -40 && temp <= 80);
    TEST_ASSERT(hum >= 0 && hum <= 100);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_sensor_initialization);
    RUN_TEST(test_sensor_update_and_values);
    UNITY_END();
}

void loop() {
    // לא נדרש
}
////////////////////////////////////////////////////////////////////////////////


// מטרת המחלקה:
// קריאת נתוני טמפרטורה ולחות מחיישן DHT22.

מחלקה SensorDht {

public:
    // בנאי: מקבל את פין ה-DATA
    SensorDht(pin)

    // אתחול החיישן
    InitSensor()

    // קריאת נתונים פעם אחת
    ReadOnce(out temp_c, out humidity) : bool

private:
    m_pin : uint8_t
    m_inited : bool
    dht : אובייקט ספרייה פנימי (DHT)
}
//////////////////////////////////////////////////////////////////////////////
SensorDht(pin):
    שמור את הפין במשתנה m_pin
    צור אובייקט DHT עם type = DHT22

InitSensor():
    dht.begin()
    m_inited = true

ReadOnce(out temp_c, out humidity):
    אם !m_inited → החזר false
    temp_c = dht.readTemperature()
    humidity = dht.readHumidity()
    אם temp_c או humidity הם NaN → החזר false
    אחרת → החזר true
/////////////////////////////////////////////////////////////////////////////////
מחלקה: SensorDht
מצב פנימי:
    m_pin : uint8_t        ← פין DATA (למשל 2)
    m_inited : bool
    dht : אובייקט ספרייה פנימי (DHT)

InitSensor():
    - dht.begin()
    - m_inited = true

ReadOnce(out temp_c, out hum):
    - אם לא מאותחל → החזר false
    - temp_c = dht.readTemperature()   (צלזיוס)
    - hum    = dht.readHumidity()
    - אם אחד מהם NaN → החזר false
    - אחרת → החזר true
/////////////////////////////////////////////////////////////////////////////

DHT dht(pin, DHT22);     // הגדרת החיישן
dht.begin();             // אתחול
float t = dht.readTemperature();  // טמפ' בצלזיוס
float h = dht.readHumidity();     // לחות באחוזים

