#include "sensor.h"

// Sensor's calibration values
static const float g_gamma = 0.7;
static const float g_rl10 = 50.0; //KOhm

//Ctor
Sensor::Sensor(int analog_pin, int digital_pin) 
    : m_analog_pin(analog_pin),
      m_digital_pin(digital_pin),
      m_last_analog(0),
      m_last_digital(false),
      m_last_lux(0.0)
{
    pinMode(m_digital_pin, INPUT);
}
// Analog read
int Sensor::ReadAnalog()
{
    m_last_analog = analogRead(m_analog_pin);
    return m_last_analog;
}
// Digital read
bool Sensor::ReadDigital()
{
    m_last_digital = (HIGH == digitalRead(m_digital_pin));
    return m_last_digital;
}

// Calculating lux value
float Sensor::ComputeLux(int analog_value)
{
    float voltage = analog_value/1024.0f * 5.0f;
    float resistance = 2000 * voltage / (1.0f - voltage/5.0f);
    float lux = pow(g_rl10 * 1e3f * pow(10.0f, g_gamma) / resistance, (1.0f / g_gamma));

    //Protection from infinites values
    if(!isfinite(lux))
    {
        lux = 0.0f;
    }

    m_last_lux = lux;
    return lux;
}

//Conversion to precentage(0 - 100%)
float Sensor::GetLightLevelPercent() const
{
    // Direct calculation from the last analog value (0-1023)
    float percent = ((1024 - m_last_analog )/ 1023.0f) * 100.0f;

    // Insure valide range
    if(percent < 0.0f) percent = 0.0f;
    if(percent > 100.0f) percent = 100.0f;

    return percent;
}

// Debug - Printing to Serial
void Sensor::PrintDebug() const
{
    Serial.print("Analog: ");
    Serial.print(m_last_analog);
    Serial.print(" | Digital: ");
    Serial.print(m_last_digital);
    Serial.print(" | Lux: ");
    Serial.print(m_last_lux);
    Serial.print(" | Light %:");
    Serial.println(GetLightLevelPercent());

}
