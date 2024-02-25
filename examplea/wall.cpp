//
// wall.cpp
//

#include "wall.h"
#include "flipper_model.h"

Wall::Wall(float angle, Float3 position, float length, float radius, float height,
           float bumper_thickness, float bumper_height,
           const PaintCan& body_color, const PaintCan& bumper_color,
           float reflectivity, int steps)
    : m_angle(angle)
    , m_position(position)
    , m_length(length)
    , m_radius(radius)
    , m_height(height)
    , m_bumper_thickness(bumper_thickness)
    , m_bumper_height(bumper_height)
    , m_body_color(body_color)
    , m_bumper_color(bumper_color)
    , m_steps(steps)
    , m_reflector1(true, radius + bumper_thickness, radius + bumper_thickness, length, reflectivity)
    , m_reflector2(false, radius + bumper_thickness, radius + bumper_thickness, length, reflectivity)
    , m_reflector3(true, radius + bumper_thickness, radius + bumper_thickness, length, reflectivity)
    , m_reflector4(false, radius + bumper_thickness, radius + bumper_thickness, length, reflectivity)
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
    m_reflector1.collide(ball);
    m_reflector2.collide(ball);
    m_reflector3.collide(ball);
    m_reflector4.collide(ball);
}

CadModel Wall::model(float animation_id) const
{
    FlipperModel wall(animation_id, m_body_color, m_bumper_color, m_radius, m_radius, m_length, m_height, m_bumper_thickness, m_bumper_height);
    wall.translate(-m_length / 2.0, 0.0, 0.0);
    wall.rotate_ay(m_angle);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(wall, pos.v1, pos.v2, pos.v3);
    return mm;
}
