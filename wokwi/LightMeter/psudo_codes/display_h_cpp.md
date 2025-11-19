#ifndef THERMO_DISPLAY_H
#define THERMO_DISPLAY_H

#include <Arduino.h> //println, length, print
#include <Wire.h> //begin (for OLED I2C)
#include <Adafruit_GFX.h> // setTextSize, setTextColor, setCersor
#include <Adafruit_SSD1306.h> //clearDisplay, display, 

class OledDisplay {
public:
    OledDisplay();

    // אתחול המסך
    bool InitDisplay();

    // הצגת טמפ’ ולחות
    void ShowSensorData(float temp, float hum);

private:
    Adafruit_SSD1306 m_display;
    bool m_inited;
};

#endif

///////////////////////////////////////////////////////////////////////////////
#include "thermo_display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

OledDisplay::OledDisplay()
    : m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1), m_inited(false)
{
}

bool OledDisplay::InitDisplay()
{
    Wire.begin();

    if (!m_display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        m_inited = false;
        return false;
    }

    m_display.clearDisplay();
    m_display.setTextSize(1);
    m_display.setTextColor(SSD1306_WHITE);
    m_display.setCursor(0, 0);
    m_display.println(F("ThermoDisplay Init..."));
    m_display.display();
    delay(1000);

    m_display.clearDisplay();
    m_display.display();
    m_inited = true;

    return true;
}

void OledDisplay::ShowSensorData(float temp, float hum)
{
    if (!m_inited) return;

    m_display.clearDisplay();
    m_display.setTextSize(1);
    m_display.setTextColor(SSD1306_WHITE);

    m_display.setCursor(0, 0);
    m_display.print("Temp: ");
    m_display.print(temp, 1);
    m_display.println(" C");

    m_display.setCursor(0, 16);
    m_display.print("Hum:  ");
    m_display.print(hum, 1);
    m_display.println(" %");

    m_display.display();
}




// מטרת הקובץ: ניהול מסך OLED SSD1306 בתקשורת I2C.
// אחראי רק על הצגה ויזואלית, ללא לוגיקה של מדידה.

// display.h
מחלקה: OledDisplay
    משתנים פרטיים:
        m_inited : bool
    פונקציות ציבוריות:
        InitDisplay()
            - מאתחלת את המסך
            - מציגה הודעת פתיחה “ThermoDisplay Init...”
        Clear()
            - מנקה את המסך
        ShowText(line1, line2)
            - מציגה שתי שורות טקסט (או רק אחת אם השנייה ריקה)
        ShowValue(label, value)
            - מציגה תווית ומספר מעוצב (לדוגמה “Temp: 25.3°C”)

// display.cpp
ב־InitDisplay():
    1. מפעיל את Wire (I²C)
    2. מפעיל את SSD1306.begin()
    3. מגדיר גודל גופן וצבע
    4. מציג הודעת פתיחה

ב־ShowText():
    1. ClearDisplay()
    2. SetCursor(0,0)
    3. print(line1)
    4. אם יש line2 → SetCursor(0,16), print(line2)
    5. display()

ב־ShowValue():
    1. ClearDisplay()
    2. SetCursor(0,0)
    3. print(label)
    4. SetCursor(0,16)
    5. print(value בפורמט קבוע)
    6. display()


///////////////////////////////////////////////////////////////////////////////
// מטרת המחלקה:
// ניהול מסך OLED SSD1306 בתקשורת I2C, כולל הדפסות טקסט וערכים מדודים.

מחלקה OledDisplay {

public:
    // אתחול המסך והכנתו לעבודה
    InitDisplay()

    // ניקוי התצוגה
    Clear()

    // הדפסת שתי שורות טקסט (אופציונלית שורה שנייה)
    ShowText(line1, line2="")

    // הצגת ערך מדידה (לדוגמה: Temp: 25.4°C)
    ShowValue(label, value, unit="")

private:
    // מציין אם המסך מאותחל בהצלחה
    m_inited : bool
}

///////////////////////////////////////////////////////////////////////////////
InitDisplay():
    הפעל תקשורת I2C ע"י Wire.begin()
    אתחל את המסך עם SSD1306.begin(SSD1306_SWITCHCAPVCC, 0x3C)
    אם אתחול נכשל → הגדר m_inited=false והחזר
    הגדר טקסט קטן (setTextSize(1)), צבע לבן (setTextColor(WHITE))
    נקה את המסך והצג הודעת פתיחה "ThermoDisplay Init..."
    m_inited = true

Clear():
    אם !m_inited → החזר
    clearDisplay()
    display()

ShowText(line1, line2=""):
    אם !m_inited → החזר
    clearDisplay()
    setCursor(0,0)
    print(line1)
    אם line2 לא ריק → setCursor(0,16) + print(line2)
    display()

ShowValue(label, value, unit=""):
    אם !m_inited → החזר
    clearDisplay()
    setCursor(0,0)
    print(label + ":")
    setCursor(0,16)
    print(value בפורמט של 1-2 ספרות אחרי נקודה)
    אם unit לא ריק → print(" " + unit)
    display()
//////////////////////////////////////////////////////////////////////

מחלקה: OledDisplay
מצב פנימי:
    m_inited : bool  ← האם האתחול הצליח

InitDisplay():
    - מפעיל I2C (Wire.begin)
    - מפעיל SSD1306.begin עם כתובת 0x3C
    - מגדיר גודל טקסט 1, צבע לבן, קורסור (0,0)
    - מציג "ThermoDisplay / Init..." כדי לאשר שהמסך עובד
    - מגדיר m_inited=true, אחרת false

Clear():
    - אם לא מאותחל → return
    - clearDisplay + display()

ShowText(line1, line2=""):
    - אם לא מאותחל → return
    - clearDisplay
    - setCursor(0,0); print(line1)
    - אם line2 לא ריק: setCursor(0,16); print(line2)
    - display()

ShowValue(label, value, unit=""):
    - אם לא מאותחל → return
    - clearDisplay
    - setCursor(0,0); print(label + ":")
    - setCursor(0,16); print(value בפורמט 1-2 ספרות אחרי נקודה)
    - אם unit לא ריק: print(" " + unit)
    - display()


