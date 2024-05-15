//
// sensor.h
//

#ifndef _SENSOR_H_
#define _SENSOR_H_

#define MAX_SENSORS            23

#define SENSOR_ID_NONE         0
#define SENSOR_ID_BUMPER       1
#define SENSOR_ID_ROLLOVER_A   2
#define SENSOR_ID_ROLLOVER_B   3
#define SENSOR_ID_ROLLOVER_C   4
#define SENSOR_ID_EXTRA_BALL   5
#define SENSOR_ID_DROP_10      6
#define SENSOR_ID_DROP_J1      7
#define SENSOR_ID_DROP_J2      8
#define SENSOR_ID_SPECIAL      9
#define SENSOR_ID_DROP_Q1      10
#define SENSOR_ID_DROP_Q2      11
#define SENSOR_ID_DROP_Q3      12
#define SENSOR_ID_TEN_POINT    13
#define SENSOR_ID_DROP_K1      14
#define SENSOR_ID_DROP_K2      15
#define SENSOR_ID_DROP_K3      14
#define SENSOR_ID_DROP_K4      17
#define SENSOR_ID_DROP_A1      18
#define SENSOR_ID_DROP_A2      19
#define SENSOR_ID_DROP_JOKER   20
#define SENSOR_ID_DROP_A3      21
#define SENSOR_ID_DROP_A4      22
#define SENSOR_ID_OUTHOLE      23

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
