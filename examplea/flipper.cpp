//
// flipper.cpp
//

#include "flipper.h"
#include "flipper_model.h"
#include "look.h"

#define MAJOR_RADIUS (FLIPPER_MAJOR_RADIUS + BUMPER_THICKNESS)
#define MINOR_RADIUS (FLIPPER_MINOR_RADIUS + BUMPER_THICKNESS)

Flipper::Flipper(float angle, Float3 position, float travel)
    : m_angle(angle)
    , m_position(position)
    , m_travel(travel)
    , m_active_angle(0.0)
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

float Flipper::angle() const
{
    return m_angle;
}

Float3 Flipper::position() const
{
    return m_position;
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

        copy4.translate({-m_position.v1, -m_position.v3});
        copy4.rotate(m_active_angle);
        copy4.translate({m_position.v1, m_position.v3});
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
    CadModel mm;
    mm.add(flipper);
    return mm;
}
