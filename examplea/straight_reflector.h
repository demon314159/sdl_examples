//
// straight_reflector.h
//

#ifndef _STRAIGHT_REFLECTOR_H_
#define _STRAIGHT_REFLECTOR_H_

#include "float3.h"
#include "ball.h"

class StraightReflector
{
public:
    StraightReflector(bool top, float r1, float r2, float length);
    ~StraightReflector();

    Float2 position() const;
    float length() const;
    float angle() const;

    bool within_range(const Ball& ball) const;
    void collide(Ball& ball) const;
    void translate(Float2 distance);
    void rotate(float angle);

private:
    Float2 m_position;
    float m_length;
    float m_angle;
};

#endif // _STRAIGHT_REFLECTOR_H_
