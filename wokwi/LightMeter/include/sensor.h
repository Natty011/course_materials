#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h> //readAnalog, pinMode, isfinite, pow, print/ln

class Sensor
{
public:
    //Ctor
    Sensor(int analog_pin, int digital_pin);

    //Reading functions from the sensor
    int ReadAnalog();
    bool ReadDigital();

    // Calculating and Proccesing functions from the sensor
    float ComputeLux(int);
    float GetLightLevelPercent() const; //Percentage of light intensity (0-100%)

    //Debug auxilary function
    void PrintDebug() const;

private:
    int m_analog_pin; //A0
    int m_digital_pin; //D2
    int m_last_analog; // Last analog's measurment
    bool m_last_digital; // Last binary's measurment(true == HIGH)
    float m_last_lux; //Last lux value that measured

};// class Sensor

#endif //SENSOR_H