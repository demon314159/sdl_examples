//
// convex_reflector.cpp
//

#include "convex_reflector.h"
#include "pi.h"
#include <math.h>

ConvexReflector::ConvexReflector(bool left, float r1, float r2, float length)
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

void ConvexReflector::collide(Ball& ball) const
{
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
            // negate ball z velocity
            Float2 temp = ball_copy.velocity();
            if (temp.v2 > 0.0) {
                ball_copy.set_velocity({temp.v1, -temp.v2});
            }
            // ball z pos -= (ball_z + radius)
            temp = ball_copy.position();
            ball_copy.set_position({temp.v1, (float) -2.0 * ball.radius() - temp.v2});
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

