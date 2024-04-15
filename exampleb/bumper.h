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
    Bumper(Float2 position, float radius, float kicker_radius, float kicker_velocity, float ball_radius,
           const PaintCan& color, int major_steps, int minor_steps);
    ~Bumper();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;
    void embed_switch(int switch_id);

private:
    Float2 m_position;
    float m_radius;
    float m_kicker_radius;
    float m_kicker_velocity;
    float m_ball_radius;
    PaintCan m_color;
    int m_major_steps;
    int m_minor_steps;
    int m_switch_id;
    ConvexKicker m_kicker;
};

#endif // _BUMPER_H_
