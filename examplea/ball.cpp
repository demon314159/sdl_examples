//
// ball.cpp
//

#include "ball.h"
#include "sphere_shape.h"
#include "pi.h"
#include "math.h"

Ball::Ball(float radius, const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color)
    : m_radius(radius)
    , m_top_color(top_color)
    , m_middle_color(middle_color)
    , m_bottom_color(bottom_color)
    , m_position({0.0, 0.0})
    , m_velocity({0.0, 0.0})
{

}

Ball::~Ball()
{
}

CadModel Ball::model(float animation_id) const
{
    float angle = 20.0;
    float top_lattitude = angle * PI / 180.0;
    float bottom_lattitude = -angle * PI / 180.0;
    CadModel mm;
    mm.add(SphereShape(m_radius, -PI / 2.0, bottom_lattitude), m_bottom_color, animation_id);
    mm.add(SphereShape(m_radius, bottom_lattitude, top_lattitude), m_middle_color, animation_id);
    mm.add(SphereShape(m_radius, top_lattitude, PI / 2.0), m_top_color, animation_id);
    return mm;
}

void Ball::advance(float seconds)
{
    m_position.v1 += (m_velocity.v1 * seconds);
    m_position.v2 += (m_velocity.v2 * seconds);
}

float Ball::radius() const
{
    return m_radius;
}

Float2 Ball::position() const
{
    return m_position;
}

Float2 Ball::velocity() const
{
    return m_velocity;
}

void Ball::set_position(Float2 position)
{
    m_position = position;
}

void Ball::set_velocity(Float2 velocity)
{
    m_velocity = velocity;
}

void Ball::rotate(float angle)
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * m_position.v1 + sint * m_position.v2;
    float tz = -sint * m_position.v1 + cost * m_position.v2;
    m_position = {tx, tz};

    tx = cost * m_velocity.v1 + sint * m_velocity.v2;
    tz = -sint * m_velocity.v1 + cost * m_velocity.v2;
    m_velocity = {tx, tz};
}

void Ball::translate(Float2 distance)
{
    m_position.v1 += distance.v1;
    m_position.v2 += distance.v2;
}
