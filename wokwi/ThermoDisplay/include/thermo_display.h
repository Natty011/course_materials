#ifndef THERMO_DISPLAY_H
#define THERMO_DISPLAY_H

#include <Arduino.h> //println, length, print, println
#include <Wire.h> //begin (for OLED I2C)
#include <Adafruit_GFX.h> // setTextSize, setTextColor, setCersor
#include <Adafruit_SSD1306.h> //clearDisplay, display

class OledDisplay
{
public:
    //Ctor. Initialization of the variables
    OledDisplay();
    // Initialization of the screen
    bool InitDisplay();
    //Showing the temperature and humidity
    void ShowSensorData(float temp, float humid);

private:
    Adafruit_SSD1306 m_display;
    bool m_initied;
}; // OledDisplay

#endif // THERMO_DISPLAY_H