//
// straight_diode_reflector.h
//

#ifndef _STRAIGHT_DIODE_REFLECTOR_H_
#define _STRAIGHT_DIODE_REFLECTOR_H_

#include "float3.h"
#include "ball.h"
#include "perimeter.h"

class StraightDiodeReflector
{
public:
    StraightDiodeReflector(float length, float reflectivity);
    ~StraightDiodeReflector();
    void update_perimeter();

    bool within_range(const Ball* ball) const;
    bool collide(Ball* ball) const;
    void translate(Float2 distance);
    void rotate(float angle);

private:
    Perimeter m_perimeter;
    Float2 m_position;
    float m_length;
    float m_reflectivity;
    float m_angle;

    void translate(Float2& point, Float2 distance) const;
    void rotate(Float2& point, float angle) const;
};

#endif // _STRAIGHT_DIODE_REFLECTOR_H_
