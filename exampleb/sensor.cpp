//
// sensor.cpp
//

#include "sensor.h"

Sensor::Sensor(int sensors)
    : m_sensors(sensors)
    , m_state(new bool[sensors + 1])
{
    clear();
}

Sensor::~Sensor()
{
    delete [] m_state;
}

void Sensor::set(int sensor_id)
{
    if (sensor_id > 0 && sensor_id <= m_sensors) {
        m_state[sensor_id] = true;
    }
}

bool Sensor::state(int sensor_id)
{
    if (sensor_id > 0 && sensor_id <= m_sensors) {
        return m_state[sensor_id];
    }
    return false;
}

void Sensor::clear()
{
    for (int i = 1; i <= m_sensors; i++) {
        m_state[i] = false;
    }
}

