//
// bumper.cpp
//

#include "bumper.h"
#include "cylinder_shape.h"
#include "cone_shape.h"

Bumper::Bumper(Float2 position, float kicker_radius, float kicker_velocity, float ball_radius,
               const PaintCan& color, int steps)
    : m_position(position)
    , m_kicker_radius(kicker_radius)
    , m_kicker_velocity(kicker_velocity)
    , m_ball_radius(ball_radius)
    , m_color(color)
    , m_steps(steps)
    , m_kicker(kicker_radius, kicker_velocity)
{
    m_kicker.translate(position);
}

Bumper::~Bumper()
{
}

void Bumper::collide(Ball* ball) const
{
    m_kicker.collide(ball);
}

CadModel Bumper::model(float animation_id) const
{
    float h1 = m_ball_radius / 8.0;
    float h2 = m_ball_radius / 4.0;

    CadModel base(CylinderShape(m_kicker_radius, h1, m_steps), m_color, animation_id);
    CadModel paddle(ConeShape(m_kicker_radius, m_kicker_radius / 2.0, h2 - h1, m_steps), m_color, animation_id);
    CadModel mm;
    mm.add(base, m_position.v1, h1 / 2.0f, m_position.v2);
    mm.add(paddle, m_position.v1, h1, m_position.v2);
    return mm;
}
