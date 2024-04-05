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
    float h2 = m_ball_radius / 2.0;
    float core_radius = m_kicker_radius / 2.0;
    float h3 = m_ball_radius + m_ball_radius / 2.0;
    float h4 = 2.0 * m_ball_radius - m_ball_radius / 8.0;
    PaintCan core_color(1.0, 1.0, 1.0);

    CadModel base(CylinderShape(m_kicker_radius, h1, m_steps), m_color, animation_id);
    CadModel paddle1(ConeShape(m_kicker_radius, core_radius, h2 - h1, m_steps), m_color, animation_id);
    CadModel core(CylinderShape(core_radius, h3 - h2, m_steps), core_color, animation_id);
    CadModel paddle2(ConeShape(core_radius, m_kicker_radius, h4 - h3, m_steps), m_color, animation_id);
    CadModel mm;
    mm.add(base, m_position.v1, h1 / 2.0f, m_position.v2);
    mm.add(paddle1, m_position.v1, h1, m_position.v2);
    mm.add(core, m_position.v1, h2 + (h3 - h2) / 2.0, m_position.v2);
    mm.add(paddle2, m_position.v1, h3, m_position.v2);
    mm.add(base, m_position.v1, h4 + h1 / 2.0f, m_position.v2);
    mm.translate(0.0, 0.001, 0.0);
    return mm;
}
