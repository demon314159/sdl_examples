//
// concave_reflector.h
//

#ifndef _CONCAVE_REFLECTOR_H_
#define _CONCAVE_REFLECTOR_H_

#include "float3.h"
#include "ball.h"

class ConcaveReflector
{
public:
    ConcaveReflector(float radius, float angle_i, float angle_f, float reflectivity);
    ConcaveReflector(float radius, float reflectivity);
    ~ConcaveReflector();

    bool angle_within_range(float angle) const;
    bool within_distance(const Ball& ball) const;
    void collide(Ball& ball) const;
    void translate(Float2 distance);
    void rotate(float angle);

private:
    Float2 m_position;
    float m_radius;
    float m_reflectivity;
    float m_angle_i;
    float m_angle_f;
};

#endif // _CONCAVE_REFLECTOR_H_
