//
// straight_diode_reflector.h
//

#ifndef _STRAIGHT_DIODE_REFLECTOR_H_
#define _STRAIGHT_DIODE_REFLECTOR_H_

#include "float3.h"
#include "ball.h"

class StraightDiodeReflector
{
public:
    StraightDiodeReflector(float length, float reflectivity);
    ~StraightDiodeReflector();

    bool within_range(const Ball* ball) const;
    void collide(Ball* ball) const;
    void translate(Float2 distance);
    void rotate(float angle);

private:
    Float2 m_position;
    float m_length;
    float m_reflectivity;
    float m_angle;
};

#endif // _STRAIGHT_DIODE_REFLECTOR_H_
