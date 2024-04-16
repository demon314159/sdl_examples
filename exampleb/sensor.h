//
// sensor.h
//

#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"

class Sensor
{
public:
    Sensor(int sensors);
    ~Sensor();
    void set(int sensor_id);
    void clear();
    bool state(int sensor_id);

private:
    int m_sensors;
    bool* m_state;
};

#endif // _SENSOR_H_
