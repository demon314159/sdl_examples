//
// flipper.cpp
//

#include "flipper.h"
#include "flipper_model.h"
#include <math.h>

Flipper::Flipper(float angle, Float3 position, float length, float major_radius, float minor_radius,
                 float height, float bumper_thickness, float bumper_height,
                 const PaintCan& body_color, const PaintCan& bumper_color,
                float travel, float velocity, float reflectivity, int steps)
    : m_action_button(false)
    , m_angle(angle)
    , m_position(position)
    , m_length(length)
    , m_major_radius(major_radius)
    , m_minor_radius(minor_radius)
    , m_height(height)
    , m_bumper_thickness(bumper_thickness)
    , m_bumper_height(bumper_height)
    , m_body_color(body_color)
    , m_bumper_color(bumper_color)
    , m_travel(travel)
    , m_velocity(velocity)
    , m_steps(steps)
    , m_active_angle(0.0)
    , m_angular_velocity(0.0)
    , m_reflector1(true, major_radius + bumper_thickness, minor_radius + bumper_thickness, length, reflectivity)
    , m_reflector2(false, major_radius + bumper_thickness, minor_radius + bumper_thickness, length, reflectivity)
    , m_reflector3(true, major_radius + bumper_thickness, minor_radius + bumper_thickness, length, reflectivity)
    , m_reflector4(false, major_radius + bumper_thickness, minor_radius + bumper_thickness, length, reflectivity)
{
    m_reflector1.rotate(angle);
    m_reflector1.translate({position.v1, position.v3});
    m_reflector2.rotate(angle);
    m_reflector2.translate({position.v1, position.v3});
    m_reflector3.rotate(angle);
    m_reflector3.translate({position.v1, position.v3});
    m_reflector4.rotate(angle);
    m_reflector4.translate({position.v1, position.v3});
}

Flipper::~Flipper()
{
}

void Flipper::advance(float seconds)
{
    if (m_action_button) {
        if (fabs(m_active_angle) < fabs(m_travel)) {
            if (m_travel > 0.0) {
                m_angular_velocity = m_velocity;
            } else {
                m_angular_velocity = -m_velocity;
            }
            m_active_angle += (m_angular_velocity * seconds);
        } else {
            m_angular_velocity = 0.0;
        }
    } else {
        if (m_travel > 0.0) {
            if (m_active_angle > 0.0) {
                m_angular_velocity = -m_velocity;
                m_active_angle += (m_angular_velocity * seconds);
            } else {
              m_angular_velocity = 0.0;
            }
        } else {
            if (m_active_angle < 0.0) {
                m_angular_velocity = m_velocity;
                m_active_angle += (m_angular_velocity * seconds);
            } else {
              m_angular_velocity = 0.0;
            }
        }
    }
}

float Flipper::angle() const
{
    return m_angle;
}

Float3 Flipper::position() const
{
    return m_position;
}

float Flipper::angular_velocity() const
{
    return m_angular_velocity;
}

float Flipper::travel() const
{
    return m_travel;
}

float Flipper::active_angle() const
{
    return m_active_angle;
}

void Flipper::set_active_angle(float angle)
{
    m_active_angle = angle;
}

void Flipper::collide(Ball& ball) const
{
    ConvexReflector copy1 = m_reflector1;
    ConvexReflector copy2 = m_reflector2;
    StraightReflector copy3 = m_reflector3;
    StraightReflector copy4 = m_reflector4;

    if (m_active_angle != 0.0) {
        copy1.translate({-m_position.v1, -m_position.v3});
        copy1.rotate(m_active_angle);
        copy1.translate({m_position.v1, m_position.v3});
        copy1.set_angular_velocity(m_angular_velocity);

        copy2.translate({-m_position.v1, -m_position.v3});
        copy2.rotate(m_active_angle);
        copy2.translate({m_position.v1, m_position.v3});
        copy2.set_angular_velocity(m_angular_velocity);

        copy3.translate({-m_position.v1, -m_position.v3});
        copy3.rotate(m_active_angle);
        copy3.translate({m_position.v1, m_position.v3});
        copy3.set_angular_velocity(m_angular_velocity);

        copy4.translate({-m_position.v1, -m_position.v3});
        copy4.rotate(m_active_angle);
        copy4.translate({m_position.v1, m_position.v3});
        copy4.set_angular_velocity(m_angular_velocity);
    }
    copy1.collide(ball);
    copy2.collide(ball);
    copy3.collide(ball);
    copy4.collide(ball);
}

CadModel Flipper::model(float animation_id) const
{
    FlipperModel flipper(animation_id, m_body_color, m_bumper_color, m_major_radius, m_minor_radius, m_length, m_height, m_bumper_thickness, m_bumper_height);
    flipper.rotate_ay(m_angle);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(flipper, pos.v1, pos.v2, pos.v3);
    return mm;
}

void Flipper::action_button(bool on)
{
    if (on) {
        m_action_button = true;
    } else {
        m_action_button = false;
    }
}

