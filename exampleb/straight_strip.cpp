//
// straight_strip.cpp
//

#include "straight_strip.h"
#include "plane_shape.h"

StraightStrip::StraightStrip(float angle, Float3 position, float length, float height, const PaintCan& color, float reflectivity)
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

StraightStrip::StraightStrip(Float2 p1, Float2 p2, float height, const PaintCan& color, float reflectivity)
    : m_height(height)
    , m_color(color)
    , m_reflector(p1, p2, 0.0, reflectivity)
{

    m_angle = m_reflector.angle();
    m_position.v1 = m_reflector.position().v1;
    m_position.v2 = height / 2.0;
    m_position.v3 = m_reflector.position().v2;
    m_length = m_reflector.length();
}

StraightStrip::~StraightStrip()
{
}

float StraightStrip::angle() const
{
    return m_angle;
}

Float3 StraightStrip::position() const
{
    return m_position;
}

float StraightStrip::length() const
{
    return m_length;
}

void StraightStrip::collide(Ball* ball) const
{
    m_reflector.collide(ball);
}

CadModel StraightStrip::model(float animation_id) const
{
    CadModel strip(PlaneShape(m_length, m_height), m_color, animation_id);
    strip.rotate_ax(-90.0);
    strip.rotate_ay(m_angle);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(strip, pos.v1, pos.v2, pos.v3);
    return mm;
}
