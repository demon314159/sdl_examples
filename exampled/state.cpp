//
// state.cpp
//

#include "state.h"
#include "pi.h"
#include <math.h>

State::State(void)
    : m_position({0.0, 0.0})
    , m_velocity({0.0, 0.0})
{
}

State::State(const Float2& position, const Float2& velocity)
    : m_position(position)
    , m_velocity(velocity)
{
}

void State::set_position(const Float2& position)
{
    m_position = position;
}

void State::set_velocity(const Float2& velocity)
{
    m_velocity = velocity;
}

State State::operator * (double scale) const
{
    State t;

    t.m_position.v1 = m_position.v1 * scale;
    t.m_position.v2 = m_position.v2 * scale;
    t.m_velocity.v1 = m_velocity.v1 * scale;
    t.m_velocity.v2 = m_velocity.v2 * scale;
    return t;
}

State State::operator + (const State& s) const
{
    State t;

    t.m_position.v1 = m_position.v1 + s.m_position.v1;
    t.m_position.v2 = m_position.v2 + s.m_position.v2;
    t.m_velocity.v1 = m_velocity.v1 + s.m_velocity.v1;
    t.m_velocity.v2 = m_velocity.v2 + s.m_velocity.v2;
    return t;
}

State State::operator - (const State& s) const
{
    State t;

    t.m_position.v1 = m_position.v1 - s.m_position.v1;
    t.m_position.v2 = m_position.v2 - s.m_position.v2;
    t.m_velocity.v1 = m_velocity.v1 - s.m_velocity.v1;
    t.m_velocity.v2 = m_velocity.v2 - s.m_velocity.v2;
    return t;
}

Float2 State::position(void) const
{
    return m_position;
}

Float2 State::velocity(void) const
{
    return m_velocity;
}

void State::rotate_frame(float angle)
{
    double cost = cos(angle * PI / 180.0);
    double sint = sin(angle * PI / 180.0);

    float tx = cost * m_position.v1 + sint * m_position.v2;
    float tz = -sint * m_position.v1 + cost * m_position.v2;
    set_position({tx, tz});

    tx = cost * m_velocity.v1 + sint * m_velocity.v2;
    tz = -sint * m_velocity.v1 + cost * m_velocity.v2;
    set_velocity({tx, tz});
}

void State::translate_velocity_frame(Float2 velocity)
{
    m_velocity.v1 += velocity.v1;
    m_velocity.v2 += velocity.v2;
}

void State::translate_frame(Float2 distance)
{
    m_position.v1 += distance.v1;
    m_position.v2 += distance.v2;
}


