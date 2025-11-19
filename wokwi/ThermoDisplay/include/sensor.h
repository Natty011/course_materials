#ifndef SENSOR_H
#define SENSOR_H

// Need for communication with DHT22 sensor
#include <DHT.h> // begin, readTemperature, readHumidity
#include <Arduino.h> // uint8_t, float..., millis

class Sensor
{
public:
//Ctor: Get the #Pin and sensor type(DHT22)
    Sensor(uint8_t pin, uint8_t type);

// Initialization of the sensor - must call one time in setup()
    void begin();
    
//Reading new data if passes suffice time (2 msec)
    void update();

//Functions(getters) for access of the last values
    float getTemperature() const;
    float getHumidity() const;
    
private:
    DHT m_dht; // object's sensor
    float m_temperature; // Temperature's last read value 
    float m_humidity; //Humidity's last read value
    unsigned long m_last_read_time; // In msec


private:
// Reading directlly from the sensor(calls from update())
    void readSensor();


}; //class Sensor

#endif // SENSOR_H
