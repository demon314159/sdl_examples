//
// straight_reflector.cpp
//

#include "straight_reflector.h"
#include "pi.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

StraightReflector::StraightReflector(bool top, float r1, float r2, float length)
    : m_position({0.0, 0.0})
    , m_length(1.0)
    , m_angle(0.0)
    , m_angular_velocity(0.0)
    , m_velocity_origin({0.0, 0.0})
{
    double theta = asin((r1 - r2) / length);
    float theta_i = PI / 2.0 - theta;
    float theta_f = 2.0 * PI + PI / 2.0 - theta;
    float x1 = r1 * cos(theta_i);
    float z1 = r1 * sin(theta_i);
    float x2 = r2 * cos(theta_f) + length;
    float z2 = r2 * sin(theta_f);
    m_length = sqrt((x1 - x2) * (x1 - x2) + (z1 - z2) * (z1 - z2));
    if (top) {
        m_position = {(x1 + x2) / 2.0f, -(z1 + z2) / 2.0f};
        m_angle = -theta * (180.0f / PI);
    } else {
        m_position = {(x1 + x2) / 2.0f, (z1 + z2) / 2.0f};
        m_angle = 180.0 + theta * (180.0f / PI);
    }
}

StraightReflector::~StraightReflector()
{
}

void StraightReflector::show(const char* msg) const
{
    printf("    StraightReflector(%s): position {%.3f, %.3f} angle %.3f, length %.3f, v %.3f, vo {%.3f, %.3f}\n",
                msg, m_position.v1, m_position.v2, m_angle, m_length,
                m_angular_velocity, m_velocity_origin.v1, m_velocity_origin.v2);
}

void StraightReflector::set_angular_velocity(float angular_velocity)
{
    m_angular_velocity = angular_velocity;
}

Float2 StraightReflector::position() const
{
    return m_position;
}

float StraightReflector::length() const
{
    return m_length;
}

float StraightReflector::angle() const
{
    return m_angle;
}

void StraightReflector::translate(Float2 distance)
{
    m_position.v1 += distance.v1;
    m_position.v2 += distance.v2;
    m_velocity_origin.v1 += distance.v1;
    m_velocity_origin.v2 += distance.v2;
}

void StraightReflector::rotate(float angle)
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * m_position.v1 + sint * m_position.v2;
    float tz = -sint * m_position.v1 + cost * m_position.v2;
    m_position = {tx, tz};

    m_angle += angle;
}

bool StraightReflector::within_range(const Ball& ball) const
{
    Float2 bp = ball.position();

    if (bp.v2 < -ball.radius())
        return false;
    if (bp.v2 > ball.radius())
        return false;
    if (bp.v1 < (-m_length / 2.0))
        return false;
    if (bp.v1 > (m_length / 2.0))
        return false;
    return true;
}

void StraightReflector::translate(Float2& point, Float2 distance) const
{
    point.v1 += distance.v1;
    point.v2 += distance.v2;
}

void StraightReflector::rotate(Float2& point, float angle) const
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * point.v1 + sint * point.v2;
    float tz = -sint * point.v1 + cost * point.v2;
    point = {tx, tz};
}

Float2 StraightReflector::velocity_at_impact(float x, Float2 velocity_origin) const
{
    float theta = atan2(-velocity_origin.v2, -velocity_origin.v1);
    float distance = sqrt(velocity_origin.v2 * velocity_origin.v2 + velocity_origin.v1 * velocity_origin.v1);
    float v = m_angular_velocity * (PI / 180.0) * distance;
    v = v * 0.7;
    float vz = -v * cos(theta);
    float vx = v * sin(theta);
    return {vx, vz};
}

void StraightReflector::collide(Ball& ball) const
{
    Float2 vo = m_velocity_origin;
    Ball ball_copy = ball;
    // translate reflector to (0, 0) and bring ball position and velocity
    ball_copy.translate_frame({-m_position.v1, -m_position.v2});
    translate(vo, {-m_position.v1, -m_position.v2});
    // rotate reflector by -angle and bring ball position and velocity
    ball_copy.rotate_frame(-m_angle);
    rotate(vo, -m_angle);
    // test for ball z position to be mode than -radius
    if (within_range(ball_copy)) { // collision
        Float2 impact_velocity = {0.0, 0.0};
        // Adjust frame for velocity at point of impact
        if (m_angular_velocity != 0.0) {
            impact_velocity = velocity_at_impact(ball_copy.position().v1, vo);
            ball_copy.translate_velocity_frame({-impact_velocity.v1, -impact_velocity.v2});
        }
        // negate ball z velocity
        Float2 temp = ball_copy.velocity();
        if (temp.v2 > 0.0) {
            ball_copy.set_velocity({temp.v1, -temp.v2});
        }
        // ball z pos -= (ball_z + radius)
        temp = ball_copy.position();
        ball_copy.set_position({temp.v1, (float) -2.0 * ball.radius() - temp.v2});
        // Unadjust frame for velocity at point of impact
        if (m_angular_velocity != 0.0) {
            ball_copy.translate_velocity_frame(impact_velocity);
        }
        // rotate reflector by angle and bring ball position and velocity
        ball_copy.rotate_frame(m_angle);
        // translate reflector to position and bring ball position and velocity
        ball_copy.translate_frame({m_position.v1, m_position.v2});
        // replace ball with new info
        float f = 0.9;
        ball = ball_copy;
        Float2 bv = ball.velocity();
        ball.set_velocity({bv.v1 * f, bv.v2 * f});
    }
}

