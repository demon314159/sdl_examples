//
// bumper.cpp
//

#include "bumper.h"
#include "cylinder_shape.h"
#include "cone_shape.h"
#include "disc_shape.h"
#include "diamond_shape.h"

Bumper::Bumper(Float2 position, float radius, float kicker_radius, float kicker_velocity, float ball_radius,
               const PaintCan& color, int major_steps, int minor_steps)
    : m_position(position)
    , m_radius(radius)
    , m_kicker_radius(kicker_radius)
    , m_kicker_velocity(kicker_velocity)
    , m_ball_radius(ball_radius)
    , m_color(color)
    , m_major_steps(major_steps)
    , m_minor_steps(minor_steps)
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
    float disc_thickness = 0.0025;
    float diamond_thickness = 0.001;
    float diamond_length = 0.007;
    float diamond_width = 0.6 * diamond_length;
    float h1 = m_ball_radius / 8.0;
    float h2 = m_ball_radius / 2.0;
    float core_radius = m_kicker_radius / 2.0;
    float h3 = m_ball_radius + m_ball_radius / 2.0;
    float h4 = 2.0 * m_ball_radius - m_ball_radius / 8.0;

    float h5 = h4 + h1;
    float h6 = h5 + disc_thickness;
    float h7 = h6 + diamond_thickness;


    PaintCan core_color(1.0, 1.0, 1.0);

    CadModel base(CylinderShape(m_kicker_radius, h1, m_major_steps), m_color, animation_id);
    CadModel paddle1(ConeShape(m_kicker_radius, core_radius * 1.5, h2 - h1, m_major_steps), m_color, animation_id);
    CadModel core(CylinderShape(core_radius, h3 - h2, m_major_steps), core_color, animation_id);
    CadModel paddle2(ConeShape(core_radius * 1.5, m_kicker_radius, h4 - h3, m_major_steps), m_color, animation_id);
    CadModel disc(DiscShape(m_radius, disc_thickness, m_major_steps, m_minor_steps), core_color, animation_id);
    CadModel diamond(DiamondShape(diamond_length, diamond_width, diamond_thickness), m_color, animation_id);
    CadModel mm;
    mm.add(base, m_position.v1, h1 / 2.0f, m_position.v2);
    mm.add(paddle1, m_position.v1, h1, m_position.v2);
    mm.add(core, m_position.v1, h2 + (h3 - h2) / 2.0, m_position.v2);
    mm.add(paddle2, m_position.v1, h3, m_position.v2);
    mm.add(base, m_position.v1, h4 + h1 / 2.0f, m_position.v2);
    mm.add(disc, m_position.v1, h5 + disc_thickness / 2.0f, m_position.v2);
    for (int i = 0; i < 8; i++) {
        CadModel temp(diamond, m_radius - diamond_length / 2.0 - diamond_length / 4.0, 0.0, 0.0);
        temp.rotate_ay(45.0 * (float) i);
        mm.add(temp, m_position.v1, h6 + diamond_thickness / 2.0, m_position.v2);
    }

    mm.translate(0.0, 0.002, 0.0);
    return mm;
}
