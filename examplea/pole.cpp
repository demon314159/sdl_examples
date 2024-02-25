//
// pole.cpp
//

#include "pole.h"
#include "pole_model.h"

Pole::Pole(Float3 position, float radius, float height, float bumper_thickness, float bumper_height,
           const PaintCan& body_color, const PaintCan& bumper_color,
           float reflectivity, int steps)
    : m_position(position)
    , m_radius(radius)
    , m_height(height)
    , m_bumper_thickness(bumper_thickness)
    , m_bumper_height(bumper_height)
    , m_body_color(body_color)
    , m_bumper_color(bumper_color)
    , m_steps(steps)
    , m_reflector(radius + bumper_thickness, reflectivity)
{
    m_reflector.translate({position.v1, position.v3});
}

Pole::~Pole()
{
}

Float3 Pole::position() const
{
    return m_position;
}

float Pole::radius() const
{
    return m_radius;
}

float Pole::height() const
{
    return m_height;
}

void Pole::collide(Ball& ball) const
{
    m_reflector.collide(ball);
}

CadModel Pole::model(float animation_id) const
{
    PoleModel pole(animation_id, m_body_color, m_bumper_color, m_radius, m_height, m_bumper_thickness, m_bumper_height, m_steps);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(pole, pos.v1, pos.v2, pos.v3);
    return mm;
}
