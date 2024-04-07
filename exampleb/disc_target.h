//
// disc_target.h
//

#ifndef _DISC_TARGET_H_
#define _DISC_TARGET_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "straight_reflector.h"

class DiscTarget
{
public:
    DiscTarget(Float2 position, float angle, float radius, float width, const PaintCan& color1,
               const PaintCan& color2, const PaintCan& color3, float reflectivity, int steps);
    ~DiscTarget();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;

private:
    Float2 m_position;
    float m_angle;
    float m_radius;
    float m_width;
    PaintCan m_color1;
    PaintCan m_color2;
    PaintCan m_color3;
    int m_steps;
    StraightReflector m_reflector;
};

#endif // _DISC_TARGET_H_
