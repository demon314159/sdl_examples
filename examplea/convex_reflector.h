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
    float length() const;
    float angle() const;

    void collide(Ball& ball) const;
    void translate(Float2 distance);
    void rotate(float angle);

private:
    Float2 m_position;
    float m_length;
    float m_angle;
};

#endif // _CONVEX_REFLECTOR_H_
