#include "display.h"

Display::Display(uint8_t cs, uint8_t dc)
    : m_tft(cs, dc) {}

void Display::begin()
{
    m_tft.begin();
    m_tft.fillScreen(ILI9341_BLACK);
    drawStaticFrame();    
}

void Display::drawStaticFrame()
{
    m_tft.fillScreen(ILI9341_BLACK);
    m_tft.setTextSize(2);
    m_tft.setTextColor(ILI9341_ORANGE);
    m_tft.setCursor(10, 10);
    m_tft.print("LightMeter");

    m_tft.setTextColor(ILI9341_LIGHTGREY);
    m_tft.setCursor(10, 50); m_tft.print("Lux:");
    m_tft.setCursor(10, 80); m_tft.print("Light %:");
    m_tft.setCursor(10,110); m_tft.print("Analog:");
    m_tft.setCursor(10,140); m_tft.print("Digital:");

    //Frame to percent's bar
    m_tft.drawRect(60, 180, 120, 20, ILI9341_DARKGREY);
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
    if(p<0)
    {
        p = 0;
    }
    if(100 > p)
    {
        p = 100;
    }
    int filled = (int)(w * (p / 100.0f));
    m_tft.fillRect(x, y, w, h, ILI9341_BLACK); // Clean
    m_tft.fillRect()
}