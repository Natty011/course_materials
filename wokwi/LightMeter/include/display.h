#ifndef DISPLAY_H
#define DISPLAY_H
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

class Display
{
public:
    Display(uint8_t cs, uint8_t dc);
    void begin();
    void splash(const char* title = "LightMeter");
    void show(float lux, float percent, int analog_value, bool digital_state);
private:
    Adafruit_ILI9341 m_tft;
    //Drawing fixed layer text
    void drawStaticFrame();
    //Printing which cleans only the old region(without nystagmus)
    void printValue(int16_t x, int16_t y, const String& text,
                    uint16_t fg = ILI9341_WHITE, uint16_t bg = ILI9341_BLACK,
                    int16_t boxW = 110, int16_t boxH = 16);
    //Progress bar of light percent
    void drawBar(int16_t x, int16_t y, int16_t w, int16_t h, float percent);
private:

}; //class Display

#endif // DISPLAY_H
