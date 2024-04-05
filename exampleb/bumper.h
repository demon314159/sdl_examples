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
    Bumper(Float2 position, float kicker_radius, float kicker_velocity, float ball_radius,
           const PaintCan& color, int steps);
    ~Bumper();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;

private:
    Float2 m_position;
    float m_kicker_radius;
    float m_kicker_velocity;
    float m_ball_radius;
    PaintCan m_color;
    int m_steps;
    ConvexKicker m_kicker;
};

#endif // _BUMPER_H_
