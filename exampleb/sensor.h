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
    bool rising(int sensor_id);
    bool falling(int sensor_id);
    bool raw(int sensor_id);

private:
    int m_sensors;
    bool* m_state;
    bool* m_last_state;
};

#endif // _SENSOR_H_
