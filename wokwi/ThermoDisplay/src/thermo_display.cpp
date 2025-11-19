#include "thermo_display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

OledDisplay::OledDisplay() :
    m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1),
    m_initied(false)
{}

bool OledDisplay::InitDisplay()
{
    Wire.begin();

    if(!m_display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
    {
        m_initied = false;
        return false;
    }

    m_display.clearDisplay();
    m_display.setTextColor(SSD1306_WHITE);
    m_display.setTextSize(1);
    m_display.setCursor(0, 0);
    m_display.println(F("ThermoDisplay Init..."));
    m_display.display();
    delay(5000);

    m_display.clearDisplay();
    m_display.display();
    m_initied = true;

    return true;
}

void OledDisplay::ShowSensorData(float temp, float humid)
{
    if(!m_initied) return;

    m_display.clearDisplay();
    m_display.setTextSize(1);
    m_display.setTextColor(SSD1306_WHITE);

    m_display.setCursor(0, 0);
    m_display.print("Temp: ");
    m_display.print(temp, 2);
    m_display.println(" C");

    m_display.setCursor(0, 16);
    m_display.print("Humid: ");
    m_display.print(humid, 2);
    m_display.println(" %");

    m_display.display();

}
