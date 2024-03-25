//
// straight_diode_strip.cpp
//

#include "straight_diode_strip.h"
#include "plane_shape.h"

StraightDiodeStrip::StraightDiodeStrip(float angle, Float3 position, float length, float height, const PaintCan& color, float reflectivity)
    : m_angle(angle)
    , m_position(position)
    , m_length(length)
    , m_height(height)
    , m_color(color)
    , m_reflector(length, reflectivity)
{
    m_reflector.rotate(angle);
    m_reflector.translate({position.v1, position.v3});
}

StraightDiodeStrip::~StraightDiodeStrip()
{
}

float StraightDiodeStrip::angle() const
{
    return m_angle;
}

Float3 StraightDiodeStrip::position() const
{
    return m_position;
}

float StraightDiodeStrip::length() const
{
    return m_length;
}

void StraightDiodeStrip::collide(Ball* ball) const
{
    m_reflector.collide(ball);
}

CadModel StraightDiodeStrip::model(float animation_id) const
{
    CadModel strip(PlaneShape(m_length, m_height), m_color, animation_id);
    strip.rotate_ax(-90.0);
    strip.rotate_ay(m_angle);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(strip, pos.v1, pos.v2, pos.v3);
    return mm;
}
