//
// bumper.cpp
//

#include "switch.h"
#include "bumper.h"
#include "cylinder_shape.h"
#include "cone_shape.h"
#include "disc_shape.h"
#include "diamond_shape.h"
#include "trim_shape.h"
#include "toroid_shape.h"
#include "atomic_shape.h"

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
    , m_switch_id(0)
    , m_kicker(kicker_radius, kicker_velocity)
{
    m_kicker.translate(position);
}

Bumper::~Bumper()
{
}

void Bumper::embed_switch(int switch_id)
{
    m_switch_id = switch_id;
}

void Bumper::collide(Ball* ball) const
{
    bool res = m_kicker.collide(ball);
    if (m_switch_id) {
        Switch::sample(m_switch_id, res);
    }
}

CadModel Bumper::model(float animation_id) const
{
    float atom_height = 0.0005;
    float disc_thickness = 0.0025;
    float diamond_thickness = 0.0005;
    float diamond_length = 0.007;
    float diamond_width = 0.6 * diamond_length;
    float ring_height = 0.0015;
    float cap_height = 0.004;
    float h1 = m_ball_radius / 8.0;
    float h2 = m_ball_radius / 2.0;
    float core_radius = m_kicker_radius / 2.0;
    float h3 = m_ball_radius + m_ball_radius / 2.0;
    float h4 = 2.0 * m_ball_radius - m_ball_radius / 8.0;

    float h5 = h4 + h1;
    float h6 = h5 + disc_thickness;
    float h7 = h6 + diamond_thickness;
    float h8 = h7 + cap_height;
    float h9 = h8 + disc_thickness / 2.0;
    float h10 = h9 + atom_height;


    PaintCan core_color(1.0, 1.0, 1.0);
    PaintCan atom_color(0.7, 0.0, 0.07);

    CadModel base(CylinderShape(m_kicker_radius, h1, m_major_steps), m_color, animation_id);
    CadModel paddle1(ConeShape(m_kicker_radius, core_radius * 1.5, h2 - h1, m_major_steps), m_color, animation_id);
    CadModel core(CylinderShape(core_radius, h3 - h2, m_major_steps), core_color, animation_id);
    CadModel paddle2(ConeShape(core_radius * 1.5, m_kicker_radius, h4 - h3, m_major_steps), m_color, animation_id);
    CadModel disc(DiscShape(m_radius, disc_thickness, m_major_steps, m_minor_steps), core_color, animation_id);
    CadModel diamond(DiamondShape(diamond_length, diamond_width, diamond_thickness), m_color, animation_id);
    CadModel trim(TrimShape(m_radius * 0.9f, (core_radius + m_radius * 0.9f) / 2.0, diamond_thickness, m_major_steps), m_color, animation_id);
    CadModel ring(ToroidShape(core_radius * 1.6, ring_height / 2.0, m_major_steps, 0.0, 360.0, 0.0, 90.0), core_color, animation_id);
    CadModel cap1(CylinderShape(core_radius * 1.6, cap_height, m_major_steps), core_color, animation_id);
    CadModel cap2(DiscShape(core_radius * 1.6, disc_thickness, m_major_steps, m_minor_steps, true, false, true), core_color, animation_id);
    CadModel cap3(DiscShape(core_radius * 1.6, disc_thickness, m_major_steps, m_minor_steps, true, true, false), core_color, 1.0);
    CadModel atom(AtomicShape(core_radius * 1.0, core_radius * 0.4, atom_height), atom_color, animation_id);
    CadModel mm;
    mm.add(base, m_position.v1, h1 / 2.0f, m_position.v2);
    mm.add(paddle1, m_position.v1, h1, m_position.v2);
    mm.add(core, m_position.v1, h2 + (h3 - h2) / 2.0, m_position.v2);
    mm.add(paddle2, m_position.v1, h3, m_position.v2);
    mm.add(base, m_position.v1, h4 + h1 / 2.0f, m_position.v2);
    mm.add(disc, m_position.v1, h5 + disc_thickness / 2.0f, m_position.v2);
    mm.add(trim, m_position.v1, h6 + diamond_thickness / 2.0f, m_position.v2);
    mm.add(ring, m_position.v1, h7 + ring_height / 2.0f, m_position.v2);
    mm.add(cap1, m_position.v1, h7 + cap_height / 2.0f, m_position.v2);
    mm.add(cap2, m_position.v1, h8, m_position.v2);
    mm.add(cap3, m_position.v1, h8, m_position.v2);
    mm.add(atom, m_position.v1, h9, m_position.v2);
    for (int i = 0; i < 8; i++) {
        CadModel temp(diamond, m_radius - diamond_length / 2.0 - diamond_length / 4.0, 0.0, 0.0);
        temp.rotate_ay(45.0 * (float) i);
        mm.add(temp, m_position.v1, h6 + diamond_thickness / 2.0, m_position.v2);
    }

    mm.translate(0.0, 0.002, 0.0);
    return mm;
}
