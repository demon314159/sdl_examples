//
// concave_strip.cpp
//

#include "concave_strip.h"
#include "concave_plane_shape.h"

ConcaveStrip::ConcaveStrip(float angle_i, float angle_f, Float3 position, float radius, float height, const PaintCan& color, float reflectivity, int steps)
    : m_angle_i(angle_i)
    , m_angle_f(angle_f)
    , m_position(position)
    , m_radius(radius)
    , m_height(height)
    , m_steps(steps)
    , m_color(color)
    , m_reflector(radius, angle_i, angle_f, reflectivity)
{
    m_reflector.translate({position.v1, position.v3});
}

ConcaveStrip::~ConcaveStrip()
{
}

float ConcaveStrip::angle_i() const
{
    return m_angle_i;
}

float ConcaveStrip::angle_f() const
{
    return m_angle_f;
}

Float3 ConcaveStrip::position() const
{
    return m_position;
}

float ConcaveStrip::radius() const
{
    return m_radius;
}

void ConcaveStrip::collide(Ball& ball) const
{
    m_reflector.collide(ball);
}

CadModel ConcaveStrip::model(float animation_id) const
{
    CadModel strip(ConcavePlaneShape(m_radius, m_angle_i, m_angle_f, m_height, m_steps), m_color, 0.0);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(strip, pos.v1, pos.v2, pos.v3);
    return mm;
}
