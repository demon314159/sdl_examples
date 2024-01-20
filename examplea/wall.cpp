//
// wall.cpp
//

#include "wall.h"
#include "flipper_model.h"
#include "look.h"

Wall::Wall(float angle, Float3 position, float length)
    : m_angle(angle)
    , m_position(position)
    , m_length(length)
{

}

Wall::~Wall()
{
}

float Wall::angle() const
{
    return m_angle;
}

Float3 Wall::position() const
{
    return m_position;
}

float Wall::length() const
{
    return m_length;
}

void Wall::collide(Ball& ball) const
{
}

CadModel Wall::model(float animation_id) const
{
    FlipperModel wall(animation_id, BODY_COLOR, BUMPER_COLOR, WALL_RADIUS, WALL_RADIUS, m_length, WALL_HEIGHT, BUMPER_THICKNESS, BUMPER_HEIGHT);
    wall.translate(-m_length / 2.0, 0.0, 0.0);
    wall.rotate_ay(m_angle);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(wall, pos.v1, pos.v2, pos.v3);
    return mm;
}
