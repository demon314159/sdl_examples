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

    void show(const char* msg) const;
    Float2 position() const;
    float length() const;
    float angle() const;

    void set_angular_velocity(float angular_velocity);
    Float2 velocity_at_impact(float x, Float2 velocity_origin) const;

    bool within_range(const Ball& ball) const;
    void collide(Ball& ball) const;
    void translate(Float2 distance);
    void rotate(float angle);
    void rotate(Float2& point, float angle) const;

private:
    Float2 m_position;
    float m_length;
    float m_angle;
    float m_angular_velocity;
    Float2 m_velocity_origin;

    void translate(Float2& point, Float2 distance) const;
};

#endif // _STRAIGHT_REFLECTOR_H_
