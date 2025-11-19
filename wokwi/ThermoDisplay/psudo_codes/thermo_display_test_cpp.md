#include <Arduino.h>
#include "thermo_display.h"

OledDisplay display;

void setup() {
    Serial.begin(9600);
    if (!display.InitDisplay()) {
        Serial.println("Display init failed!");
        while (true);
    }
}

void loop() {
    float temp = 24.6;
    float hum  = 58.2;

    display.ShowSensorData(temp, hum);
    delay(2000);
}

