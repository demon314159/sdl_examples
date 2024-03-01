//
// bumper.h
//

#ifndef _BUMPER_H_
#define _BUMPER_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "convex_kicker.h"

class Bumper
{
public:
    Bumper(Float3 position, float wall_radius, float stem_radius, float wall_height, float stem_height,
           const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color,
           float kicker_velocity, int steps);
    ~Bumper();

    CadModel model(float animation_id) const;
    void collide(Ball& ball) const;

private:
    Float3 m_position;
    float m_wall_radius;
    float m_stem_radius;
    float m_wall_height;
    float m_stem_height;
    PaintCan m_top_color;
    PaintCan m_middle_color;
    PaintCan m_bottom_color;
    int m_steps;
    ConvexKicker m_kicker;
};

#endif // _BUMPER_H_
