#include "sensor.h"

//Ctor
Sensor::Sensor(uint8_t pin, uint8_t type) 
    : m_dht(pin, type), m_temperature(0.0f),
      m_humidity(0.0f), m_last_read_time(0)
    {}
//Initilaize the sensor
void Sensor::begin()
{
    m_dht.begin();
}

// Internal function to read values from the sensor
void Sensor::readSensor()
{
    float temp = m_dht.readTemperature();
    float humid = m_dht.readHumidity();
    
    //Check if the values are valids
    if(!isnan(temp) & !isnan(humid))
    {
        m_temperature = temp;
        m_humidity = humid;
    }
}
// update values(every 2 sec)
void Sensor::update()
{
    unsigned long current_time = millis();
//Checking if passes 2 sec from the last reading
    if(current_time - m_last_read_time >= 2000)
    {
        readSensor();
        m_last_read_time = current_time;
    }
}
//Getters
float Sensor::getTemperature() const
{
    return m_temperature;
}

float Sensor::getHumidity() const
{
    return m_humidity;
}