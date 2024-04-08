//
// straight_kicker.cpp
//

#include "straight_kicker.h"
#include "pi.h"
#include <math.h>

StraightKicker::StraightKicker(Float2 p1, Float2 p2, float radius, float velocity)
    : m_position({0.0, 0.0})
    , m_velocity(velocity)
    , m_angle(0.0)
{
    float dx = p2.v1 - p1.v1;
    float dz = p2.v2 - p1.v2;
    m_length = sqrt(dx * dx + dz * dz);
    float angle = atan2(-dz, dx) * 180.0 / PI;
    translate({0.0, -radius});
    rotate(angle);
    translate({(p1.v1 + p2.v1) / 2.0f, (p1.v2 + p2.v2) / 2.0f});
}

StraightKicker::~StraightKicker()
{
}

void StraightKicker::translate(Float2 distance)
{
    m_position.v1 += distance.v1;
    m_position.v2 += distance.v2;
}

void StraightKicker::rotate(float angle)
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * m_position.v1 + sint * m_position.v2;
    float tz = -sint * m_position.v1 + cost * m_position.v2;
    m_position = {tx, tz};

    m_angle += angle;
}

bool StraightKicker::within_range(const Ball* ball) const
{
    Float2 bp = ball->position();

    if (bp.v2 < -ball->radius())
        return false;
    if (bp.v2 > ball->radius())
        return false;
    if (bp.v1 < (-m_length / 2.0))
        return false;
    if (bp.v1 > (m_length / 2.0))
        return false;
    return true;
}

void StraightKicker::translate(Float2& point, Float2 distance) const
{
    point.v1 += distance.v1;
    point.v2 += distance.v2;
}

void StraightKicker::rotate(Float2& point, float angle) const
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * point.v1 + sint * point.v2;
    float tz = -sint * point.v1 + cost * point.v2;
    point = {tx, tz};
}

void StraightKicker::collide(Ball* ball) const
{
    Ball ball_copy = *ball;
    // translate reflector to (0, 0) and bring ball position and velocity
    ball_copy.translate_frame({-m_position.v1, -m_position.v2});
    // rotate reflector by -angle and bring ball position and velocity
    ball_copy.rotate_frame(-m_angle);
    // test for ball z position to be more than -radius
    ball->heavy_test();
    if (within_range(&ball_copy)) { // collision
        ball->heavy_test_pass();
        // negate ball z velocity
        Float2 temp = ball_copy.velocity();
        if (temp.v2 > 0.0) {
            temp.v2 = m_velocity;
            ball_copy.set_velocity({temp.v1, -temp.v2});
        }
        // ball z pos -= (ball_z + radius)
        temp = ball_copy.position();
        ball_copy.set_position({temp.v1, (float) -2.0 * ball_copy.radius() - temp.v2});
        // rotate reflector by angle and bring ball position and velocity
        ball_copy.rotate_frame(m_angle);
        // translate reflector to position and bring ball position and velocity
        ball_copy.translate_frame({m_position.v1, m_position.v2});
        // replace ball with new info
        *ball = ball_copy;
    }
}

Float2 StraightKicker::position() const
{
    return m_position;
}

float StraightKicker::length() const
{
    return m_length;
}

float StraightKicker::angle() const
{
    return m_angle;
}


