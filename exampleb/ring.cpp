//
// ring.cpp
//

#include "ring.h"
#include "ring_shape.h"
#include "toroid_shape.h"
#include <math.h>

Ring::Ring(float angle, Float3 position, float outer_radius, float inner_radius, float width,
           const PaintCan& color, float reflectivity, int steps)
    : m_angle(angle)
    , m_position(position)
    , m_outer_radius(outer_radius)
    , m_inner_radius(inner_radius)
    , m_width(width)
    , m_color(color)
    , m_steps(steps)
    , m_reflector1(true, width / 2.0, width / 2.0, outer_radius * 2.0, reflectivity)
    , m_reflector2(false, width / 2.0, width / 2.0, outer_radius * 2.0, reflectivity)
    , m_reflector3(true, width / 2.0, width / 2.0, outer_radius * 2.0, reflectivity)
    , m_reflector4(false, width / 2.0, width / 2.0, outer_radius * 2.0, reflectivity)
{
    m_reflector1.translate({-outer_radius, 0.0});
    m_reflector1.rotate(angle + 90.0);
    m_reflector1.translate({position.v1, position.v3});

    m_reflector2.translate({-outer_radius, 0.0});
    m_reflector2.rotate(angle + 90.0);
    m_reflector2.translate({position.v1, position.v3});

    m_reflector3.translate({-outer_radius, 0.0});
    m_reflector3.rotate(angle + 90.0);
    m_reflector3.translate({position.v1, position.v3});

    m_reflector4.translate({-outer_radius, 0.0});
    m_reflector4.rotate(angle + 90.0);
    m_reflector4.translate({position.v1, position.v3});
}

Ring::~Ring()
{
}

float Ring::angle() const
{
    return m_angle;
}

Float3 Ring::position() const
{
    return m_position;
}

void Ring::collide(Ball* ball) const
{
    m_reflector1.collide(ball);
    m_reflector2.collide(ball);
    m_reflector3.collide(ball);
    m_reflector4.collide(ball);
}

CadModel Ring::model(float animation_id) const
{
    CadModel half_toroid(ToroidShape(m_outer_radius, m_width / 2.0f, m_steps, 0.0, 360.0, -90.0, 90.0), m_color, 0.0);
    CadModel ring(RingShape(m_outer_radius, m_inner_radius, m_width, m_steps), m_color, 0.0);
    ring.rotate_ax(90.0);
    half_toroid.rotate_ax(90.0);
    ring.rotate_ay(m_angle + 90.0);
    half_toroid.rotate_ay(m_angle + 90.0);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(ring, pos.v1, pos.v2, pos.v3);
    mm.add(half_toroid, pos.v1, pos.v2, pos.v3);
    return mm;
}


