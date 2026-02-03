#include "display.h"
//#include<Arduino.h>

Display::Display(uint8_t cs, uint8_t dc)
    : m_tft(cs, dc) {}

void Display::begin()
{
    m_tft.begin();
    m_tft.setRotation(1);
    m_tft.fillScreen(ILI9341_BLACK);
    drawStaticFrame();    

}

void Display::splash(const char* title)
{
    m_tft.fillScreen(ILI9341_BLACK);
    m_tft.setTextColor(ILI9341_CYAN);
    m_tft.setTextSize(2);
    m_tft.setCursor(20, 20);
    m_tft.println(title);
    m_tft.setTextSize(2);
    m_tft.setTextColor(20, 40);
    m_tft.setTextColor(ILI9341_YELLOW);
    m_tft.println("Initializing...");

}

void Display::drawStaticFrame()
{
    m_tft.fillScreen(ILI9341_BLACK);
    m_tft.setTextSize(2);
    m_tft.setTextColor(ILI9341_ORANGE);
    m_tft.setCursor(0, 0);
    m_tft.print("LightMeter");

    m_tft.setTextColor(ILI9341_LIGHTGREY);
    m_tft.setCursor(0, 50); m_tft.print("Lux:");
    m_tft.setCursor(0, 80); m_tft.print("Light:");
    m_tft.setCursor(0,110); m_tft.print("Analog:");
    m_tft.setCursor(0,140); m_tft.print("Digital:");

    //Frame to percent's bar
    //m_tft.drawRect(120, 78, 180, 18, ILI9341_DARKGREY);
    delay(3000);

}

void Display::printValue(int16_t x, int16_t y, const String& text,
                        uint16_t fg, uint16_t bg, int16_t w, int16_t h)
{
    m_tft.fillRect(x, y, w, h, bg); //Clean the region first
    m_tft.setTextColor(fg);
    m_tft.setTextSize(2);
    m_tft.setCursor(x, y);
    m_tft.print(text);
}

void Display::drawBar(int16_t x, int16_t y, int16_t w, int16_t h, float p)
{
    if(p<0.0f)
    {
        p = 0.0f;
    }
    if(100.0f < p)
    {
        p = 100.0f;
    }
    const int filled = static_cast<int>(w * p / 100.0f);
    m_tft.fillRect(x, y, w, h, ILI9341_BLACK); // Clean
    m_tft.fillRect(x, y, filled,h, ILI9341_GREEN); // Fill the relative bar
    m_tft.drawRect(x, y, w, h, ILI9341_DARKGREY); //Frame
}

void Display::show(float lux, float percent, int analog_value, bool digital_state)
{

    if(lux != m_last_lux)
    {
        printValue(100, 50, String(lux, 1));
        printValue(195, 50, "lx", ILI9341_BLUE);// Small units if wants
        m_last_lux = lux;
    }

    if(percent != m_last_percent)
    {
        drawBar(100, 78, 150, 18, percent);
        printValue(260, 78, String(percent, 1)+"%");
        m_last_percent = percent;
    }

    if(analog_value != m_last_analog)
    {
        printValue(100, 110, String(analog_value));
        m_last_analog = analog_value;
    }

    if(digital_state != m_last_digital)
    {
        printValue(100, 140,
            digital_state ? "HIGH" : "LOW",
            digital_state ? ILI9341_GREEN : ILI9341_RED);
        m_last_digital = digital_state;
    }

}

