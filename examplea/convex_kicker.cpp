//
// convex_kicker.cpp
//

#include "convex_kicker.h"
#include "pi.h"
#include <math.h>

ConvexKicker::ConvexKicker(float radius, float velocity)
    : m_position({0.0, 0.0})
    , m_radius(radius)
    , m_velocity(velocity)
    , m_angle_i(0.0)
    , m_angle_f(360.0)
{
}

ConvexKicker::~ConvexKicker()
{
}

void ConvexKicker::translate(Float2 distance)
{
    m_position.v1 += distance.v1;
    m_position.v2 += distance.v2;
}

void ConvexKicker::rotate(float angle)
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * m_position.v1 + sint * m_position.v2;
    float tz = -sint * m_position.v1 + cost * m_position.v2;
    m_position = {tx, tz};

    m_angle_i += angle;
    m_angle_f += angle;
}

void ConvexKicker::translate(Float2& point, Float2 distance) const
{
    point.v1 += distance.v1;
    point.v2 += distance.v2;
}

void ConvexKicker::rotate(Float2& point, float angle) const
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * point.v1 + sint * point.v2;
    float tz = -sint * point.v1 + cost * point.v2;
    point = {tx, tz};
}

bool ConvexKicker::angle_within_range(float angle) const
{
    while (angle < m_angle_i) {
        angle += 360.0;
    }
    while (angle > m_angle_f) {
        angle -= 360.0;
    }
    return angle >= m_angle_i;
}

bool ConvexKicker::within_distance(const Ball& ball) const
{
    double dx = ball.position().v1 - m_position.v1;
    double dz = ball.position().v2 - m_position.v2;

    float distance = sqrt(dx * dx + dz * dz);
    return distance <= (ball.radius() + m_radius);
}

void ConvexKicker::collide(Ball& ball) const
{
    if (within_distance(ball)) {
        float dx = ball.position().v1 - m_position.v1;
        float dz = ball.position().v2 - m_position.v2;
        float angle = (180.0 / PI) * atan2(-dz, dx);
        if (angle_within_range(angle)) {
            float rot_angle = angle - 90.0;
            Ball ball_copy = ball;
            // translate kicker to (0, 0) and bring ball position and velocity
            ball_copy.translate_frame({-m_position.v1, -m_position.v2});
            // rotate kicker by -angle and bring ball position and velocity
            ball_copy.rotate_frame(-rot_angle);
            // translate kicker by (0, radius) and bring ball position and velocity
            ball_copy.translate_frame({0.0, m_radius});
            // negate ball z velocity
            Float2 temp = ball_copy.velocity();
            if (temp.v2 > 0.0) {
                temp.v2 = m_velocity;
                ball_copy.set_velocity({temp.v1, -temp.v2});
            }
            // ball z pos -= (ball_z + radius)
            temp = ball_copy.position();
            ball_copy.set_position({temp.v1, (float) -2.0 * ball.radius() - temp.v2});
            // translate kicker by (0, -radius) and bring ball position and velocity
            ball_copy.translate_frame({0, -m_radius});
            // rotate kicker by angle and bring ball position and velocity
            ball_copy.rotate_frame(rot_angle);
            // translate kicker to position and bring ball position and velocity
            ball_copy.translate_frame({m_position.v1, m_position.v2});
            // replace ball with new info
            ball = ball_copy;
        }
    }
}

