//
// convex_reflector.h
//

#ifndef _CONVEX_REFLECTOR_H_
#define _CONVEX_REFLECTOR_H_

#include "float3.h"
#include "ball.h"

class ConvexReflector
{
public:
    ConvexReflector(bool left, float r1, float r2, float length);
    ~ConvexReflector();

    Float2 position() const;
    float radius() const;
    float angle_i() const;
    float angle_f() const;

    bool angle_within_range(float angle) const;
    bool within_distance(const Ball& ball) const;
    void collide(Ball& ball) const;
    void translate(Float2 distance);
    void rotate(float angle);

private:
    Float2 m_position;
    float m_radius;
    float m_angle_i;
    float m_angle_f;
};

#endif // _CONVEX_REFLECTOR_H_
