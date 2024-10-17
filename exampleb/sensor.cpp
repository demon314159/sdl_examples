//
// sensor.cpp
//

#include "sensor.h"

#define MASK 0x100000

Sensor::Sensor(int sensors)
    : m_sensors(sensors)
    , m_state(new int[sensors + 1])
{
    for (int i = 0; i <= sensors; i++) {
        m_state[i] = 0;
    }
}

Sensor::~Sensor()
{
    delete [] m_state;
}

void Sensor::set(int sensor_id)
{
    if (sensor_id > 0 && sensor_id <= m_sensors) {
        m_state[sensor_id] |= MASK;
    }
}

bool Sensor::rising(int sensor_id)
{
    if (sensor_id > 0 && sensor_id <= m_sensors) {
        return m_state[sensor_id] == MASK;
    }
    return false;
}

bool Sensor::raw(int sensor_id)
{
    if (sensor_id > 0 && sensor_id <= m_sensors) {
        return (m_state[sensor_id] & MASK) == MASK;
    }
    return false;
}

void Sensor::clear()
{
    for (int i = 1; i <= m_sensors; i++) {
        m_state[i] = m_state[i] >> 1;
    }
}

