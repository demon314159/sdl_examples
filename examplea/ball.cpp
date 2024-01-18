//
// ball.cpp
//

#include "ball.h"
#include "sphere_shape.h"
#include "pi.h"
#include "math.h"

#include <stdio.h>

Ball::Ball(float radius, const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color)
    : m_radius(radius)
    , m_top_color(top_color)
    , m_middle_color(middle_color)
    , m_bottom_color(bottom_color)
    , m_position({0.0, 0.0})
    , m_velocity({0.0, 0.0})
    , m_orientation()
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
    float f = 1.0 / sqrt(2.0);

    double deltax = m_velocity.v1 * seconds;
    double deltaz = m_velocity.v2 * seconds;
    m_position.v1 += (float) deltax;
    m_position.v2 += (float) deltaz;

    double distance = sqrt(deltax * deltax + deltaz * deltaz);
    double last_angle = (distance / m_radius) * (180.0 / PI);


// Rotete m_orienation quaternion by last_angle and axes and normalize it
    Quaternion qa((float) last_angle, {f, 0.0, f});
    m_orientation = m_orientation * qa;
    m_orientation.normalize();
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

void Ball::rotate_frame(float angle)
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

void Ball::translate_frame(Float2 distance)
{
    m_position.v1 += distance.v1;
    m_position.v2 += distance.v2;
}

Matrix4x4 Ball::animation_matrix() const
{
    Matrix4x4 mm;
    mm.unity();
    mm.translate(m_position.v1, 0.0, m_position.v2);

    // Multipy mm times the rotation matrix
    mm = mm * m_orientation.rotation_matrix();
    return mm;
}
