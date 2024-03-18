//
// concave_strip.h
//

#ifndef _CONCAVE_STRIP_H_
#define _CONCAVE_STRIP_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "concave_reflector.h"

class ConcaveStrip
{
public:
    ConcaveStrip(float angle_i, float angle_f, Float3 position, float radius, float height, const PaintCan& color, float reflectivity, int steps);

    ~ConcaveStrip();

    CadModel model(float animation_id) const;
    float angle_i() const;
    float angle_f() const;
    Float3 position() const;
    float radius() const;
    void collide(Ball& ball) const;

private:
    float m_angle_i;
    float m_angle_f;
    Float3 m_position;
    float m_radius;
    float m_height;
    float m_steps;
    PaintCan m_color;
    ConcaveReflector m_reflector;
};

#endif // _CONCAVE_STRIP_H_
