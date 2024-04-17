//
// sensor.cpp
//

#include "sensor.h"

Sensor::Sensor(int sensors)
    : m_sensors(sensors)
    , m_state(new bool[sensors + 1])
    , m_last_state(new bool[sensors + 1])
{
    for (int i = 0; i <= sensors; i++) {
        m_state[i] = false;
        m_last_state[i] = false;
    }
}

Sensor::~Sensor()
{
    delete [] m_state;
    delete [] m_last_state;
}

void Sensor::set(int sensor_id)
{
    if (sensor_id > 0 && sensor_id <= m_sensors) {
        m_state[sensor_id] = true;
    }
}

bool Sensor::rising(int sensor_id)
{
    if (sensor_id > 0 && sensor_id <= m_sensors) {
        return m_state[sensor_id] && !m_last_state[sensor_id];
    }
    return false;
}

bool Sensor::falling(int sensor_id)
{
    if (sensor_id > 0 && sensor_id <= m_sensors) {
        return !m_state[sensor_id] && m_last_state[sensor_id];
    }
    return false;
}

bool Sensor::raw(int sensor_id)
{
    if (sensor_id > 0 && sensor_id <= m_sensors) {
        return m_state[sensor_id];
    }
    return false;
}

void Sensor::clear()
{
    for (int i = 1; i <= m_sensors; i++) {
        m_last_state[i] = m_state[i];
        m_state[i] = false;
    }
}

