//
// convex_reflector.cpp
//

#include "convex_reflector.h"
#include "pi.h"
#include <math.h>

ConvexReflector::ConvexReflector(bool left, float r1, float r2, float length)
{

}

ConvexReflector::~ConvexReflector()
{
}

Float2 ConvexReflector::position() const
{
    return m_position;
}

float ConvexReflector::length() const
{
    return m_length;
}

float ConvexReflector::angle() const
{
    return m_angle;
}

void ConvexReflector::translate(Float2 distance)
{
    m_position.v1 += distance.v1;
    m_position.v2 += distance.v2;
}

void ConvexReflector::rotate(float angle)
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * m_position.v1 + sint * m_position.v2;
    float tz = -sint * m_position.v1 + cost * m_position.v2;
    m_position = {tx, tz};

    m_angle += angle;
}
void ConvexReflector::collide(Ball& ball) const
{
}

