//
// ring.h
//

#ifndef _RING_H_
#define _RING_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "straight_reflector.h"

class Ring
{
public:
    Ring(float angle, Float3 position, float outer_radius, float inner_radius, float width,
         const PaintCan& color, float reflectivity, int steps);
    ~Ring();

    CadModel model(float animation_id) const;
    float angle() const;
    Float3 position() const;
    void collide(Ball* ball) const;

private:
    float m_angle;
    Float3 m_position;
    float m_outer_radius;
    float m_inner_radius;
    float m_width;
    PaintCan m_color;
    int m_steps;
    StraightReflector m_reflector1;
    StraightReflector m_reflector2;
    StraightReflector m_reflector3;
    StraightReflector m_reflector4;
};

#endif // _RING_H_
