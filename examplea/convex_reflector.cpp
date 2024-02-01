//
// convex_reflector.cpp
//

#include "convex_reflector.h"
#include "pi.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

ConvexReflector::ConvexReflector(bool left, float r1, float r2, float length)
    : m_angular_velocity(0.0)
    , m_velocity_origin({0.0, 0.0})
{
    double theta = asin((r1 - r2) / length);
    if (left) {
        m_position = {0.0, 0.0};
        m_radius = r1;
        m_angle_i = (180.0 / PI) * (PI / 2.0 - theta);
        m_angle_f = (180.0 / PI) * (3.0 * PI / 2.0 + theta);
    } else {
        m_position = {length, 0.0};
        m_radius = r2;
        m_angle_i = (180.0 / PI) * (3.0 * PI / 2.0 + theta);
        m_angle_f = (180.0 / PI) * (2.0 * PI + PI / 2.0 - theta);
    }
}

ConvexReflector::~ConvexReflector()
{
}

void ConvexReflector::show(const char* msg) const
{
    printf("    ConvexReflector(%s): position {%.3f, %.3f} radius %.3f, angle_i %.3f, angle_f %.3f, v %.3f, vo {%.3f, %.3f}\n",
                msg, m_position.v1, m_position.v2, m_radius, m_angle_i, m_angle_f,
                m_angular_velocity, m_velocity_origin.v1, m_velocity_origin.v2);
}

void ConvexReflector::set_angular_velocity(float angular_velocity)
{
    m_angular_velocity = angular_velocity;
}

Float2 ConvexReflector::position() const
{
    return m_position;
}

float ConvexReflector::radius() const
{
    return m_radius;
}

float ConvexReflector::angle_i() const
{
    return m_angle_i;
}

float ConvexReflector::angle_f() const
{
    return m_angle_f;
}

void ConvexReflector::translate(Float2 distance)
{
    m_position.v1 += distance.v1;
    m_position.v2 += distance.v2;
}

void ConvexReflector::rotate(float angle)
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * m_position.v1 + sint * m_position.v2;
    float tz = -sint * m_position.v1 + cost * m_position.v2;
    m_position = {tx, tz};

    m_angle_i += angle;
    m_angle_f += angle;
}

void ConvexReflector::translate(Float2& point, Float2 distance) const
{
    point.v1 += distance.v1;
    point.v2 += distance.v2;
}

bool ConvexReflector::angle_within_range(float angle) const
{
    while (angle < m_angle_i) {
        angle += 360.0;
    }
    while (angle > m_angle_f) {
        angle -= 360.0;
    }
    return angle >= m_angle_i;
}

bool ConvexReflector::within_distance(const Ball& ball) const
{
    double dx = ball.position().v1 - m_position.v1;
    double dz = ball.position().v2 - m_position.v2;

    float distance = sqrt(dx * dx + dz * dz);
    return distance <= (ball.radius() + m_radius);
}

Float2 ConvexReflector::velocity_at_impact(float x, Float2 velocity_origin) const
{
    float theta = atan2(-velocity_origin.v2, -velocity_origin.v1);
    float distance = sqrt(velocity_origin.v2 * velocity_origin.v2 + velocity_origin.v1 * velocity_origin.v1);
    float v = m_angular_velocity * (PI / 180.0) * distance;
    v = v * 0.7;
    float vz = -v * cos(theta);
    float vx = v * sin(theta);
    return {vx, vz};
}

void ConvexReflector::collide(Ball& ball) const
{
    Float2 vo = m_velocity_origin;
    if (within_distance(ball)) {
        float dx = ball.position().v1 - m_position.v1;
        float dz = ball.position().v2 - m_position.v2;
        float angle = (180.0 / PI) * atan2(-dz, dx);
        if (angle_within_range(angle)) {
            float rot_angle = angle - 90.0;
            Ball ball_copy = ball;
            // translate reflector to (0, 0) and bring ball position and velocity
            ball_copy.translate_frame({-m_position.v1, -m_position.v2});
            // rotate reflector by -angle and bring ball position and velocity
            ball_copy.rotate_frame(-rot_angle);
            // translate reflector by (0, radius) and bring ball position and velocity
            ball_copy.translate_frame({0, m_radius});
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
            // translate reflector by (0, -radius) and bring ball position and velocity
            ball_copy.translate_frame({0, -m_radius});
            // rotate reflector by angle and bring ball position and velocity
            ball_copy.rotate_frame(rot_angle);
            // translate reflector to position and bring ball position and velocity
            ball_copy.translate_frame({m_position.v1, m_position.v2});
            // replace ball with new info
            float f = 0.9;
            ball = ball_copy;
            Float2 bv = ball.velocity();
            ball.set_velocity({bv.v1 * f, bv.v2 * f});
        }
    }
}

