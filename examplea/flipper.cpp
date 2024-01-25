//
// flipper.cpp
//

#include "flipper.h"
#include "flipper_model.h"
#include "look.h"
#include <math.h>

#include <stdio.h>

#define MAJOR_RADIUS (FLIPPER_MAJOR_RADIUS + BUMPER_THICKNESS)
#define MINOR_RADIUS (FLIPPER_MINOR_RADIUS + BUMPER_THICKNESS)
#define ANGULAR_VELOCITY (280.0 * 4.0)

Flipper::Flipper(float angle, Float3 position, float travel)
    : m_action_button(false)
    , m_angle(angle)
    , m_position(position)
    , m_travel(travel)
    , m_active_angle(0.0)
    , m_angular_velocity(0.0)
    , m_angular_acceleration(0.0)
    , m_reflector1(true, MAJOR_RADIUS, MINOR_RADIUS, FLIPPER_LENGTH)
    , m_reflector2(false, MAJOR_RADIUS, MINOR_RADIUS, FLIPPER_LENGTH)
    , m_reflector3(true, MAJOR_RADIUS, MINOR_RADIUS, FLIPPER_LENGTH)
    , m_reflector4(false, MAJOR_RADIUS, MINOR_RADIUS, FLIPPER_LENGTH)
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
            m_angular_velocity = ANGULAR_VELOCITY;
            if (m_travel > 0.0) {
                m_active_angle += (m_angular_velocity * seconds);
            } else {
                m_active_angle -= (m_angular_velocity * seconds);
            }
        } else {
            m_angular_velocity = 0.0;
        }
    } else {
        if (m_travel > 0.0) {
            if (m_active_angle > 0.0) {
                m_angular_velocity = ANGULAR_VELOCITY;
                m_active_angle -= (m_angular_velocity * seconds);
            } else {
              m_angular_velocity = 0.0;
            }
        } else {
            if (m_active_angle < 0.0) {
                m_angular_velocity = ANGULAR_VELOCITY;
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

        copy2.translate({-m_position.v1, -m_position.v3});
        copy2.rotate(m_active_angle);
        copy2.translate({m_position.v1, m_position.v3});

        copy3.translate({-m_position.v1, -m_position.v3});
        copy3.rotate(m_active_angle);
        copy3.translate({m_position.v1, m_position.v3});
        copy3.set_angular_velocity(m_travel > 0.0 ? m_angular_velocity : -m_angular_velocity);

        copy4.translate({-m_position.v1, -m_position.v3});
        copy4.rotate(m_active_angle);
        copy4.translate({m_position.v1, m_position.v3});
        copy4.set_angular_velocity(m_travel > 0.0 ? m_angular_velocity : -m_angular_velocity);
    }
    copy1.collide(ball);
    copy2.collide(ball);
    copy3.collide(ball);
    copy4.collide(ball);
}

CadModel Flipper::model(float animation_id) const
{
    FlipperModel flipper(animation_id, BODY_COLOR, BUMPER_COLOR, FLIPPER_MAJOR_RADIUS, FLIPPER_MINOR_RADIUS, FLIPPER_LENGTH, FLIPPER_HEIGHT, BUMPER_THICKNESS, BUMPER_HEIGHT);
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

