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
    , m_reflector1(true, WALL_RADIUS + BUMPER_THICKNESS, WALL_RADIUS + BUMPER_THICKNESS, length)
    , m_reflector2(false, WALL_RADIUS + BUMPER_THICKNESS, WALL_RADIUS + BUMPER_THICKNESS, length)
    , m_reflector3(true, WALL_RADIUS + BUMPER_THICKNESS, WALL_RADIUS + BUMPER_THICKNESS, length)
    , m_reflector4(false, WALL_RADIUS + BUMPER_THICKNESS, WALL_RADIUS + BUMPER_THICKNESS, length)
{
    m_reflector1.translate({-length / 2.0f, 0.0});
    m_reflector1.rotate(angle);
    m_reflector1.translate({position.v1, position.v3});
    m_reflector2.translate({-length / 2.0f, 0.0});
    m_reflector2.rotate(angle);
    m_reflector2.translate({position.v1, position.v3});
    m_reflector3.translate({-length / 2.0f, 0.0});
    m_reflector3.rotate(angle);
    m_reflector3.translate({position.v1, position.v3});
    m_reflector4.translate({-length / 2.0f, 0.0});
    m_reflector4.rotate(angle);
    m_reflector4.translate({position.v1, position.v3});
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
//    m_reflector1.collide(ball);
//    m_reflector2.collide(ball);
    m_reflector3.collide(ball);
    m_reflector4.collide(ball);
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
