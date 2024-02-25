//
// pole.cpp
//

#include "pole.h"
#include "pole_model.h"
#include "look.h"

Pole::Pole(Float3 position, float radius, float height, float reflectivity)
    : m_position(position)
    , m_radius(radius)
    , m_height(height)
    , m_reflector(radius + BUMPER_THICKNESS, reflectivity)
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
    PoleModel pole(animation_id, BODY_COLOR, BUMPER_COLOR, m_radius, m_height, BUMPER_THICKNESS, BUMPER_HEIGHT);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(pole, pos.v1, pos.v2, pos.v3);
    return mm;
}
