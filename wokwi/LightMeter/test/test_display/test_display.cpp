#include <Arduino.h>
#include "display.h"

#define TFT_CS 10
#define TFT_DC 9

Display g_display(TFT_CS, TFT_DC);

void setup()
{
    Serial.begin(115200);

    Serial.println("Display test start");
    //delay(3000);

    g_display.begin();
    //g_display.splash("Display Test");
    //Serial.print("DEBUG_SETUP");

    // First drawing of the frame
    g_display.show(0, 0, 0, false);
}

void loop()
{
    // Dinamic check of the screen: Changing values like a graph
    static float lux = 0;
    static bool state = false;

    lux += 5;
    if(lux > 1000)
    {
        lux = 0;
        state = !state;
    }

    float percent = ( lux / 1000.0f) * 100.0f;
    int analog_value = map(lux, 0, 1000, 0, 1023);
    g_display.show(lux, percent, analog_value, state);

    delay(150);
}