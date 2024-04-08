//
// concave_reflector.cpp
//

#include "concave_reflector.h"
#include "pi.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

ConcaveReflector::ConcaveReflector(float radius, float angle_i, float angle_f, float reflectivity)
    : m_perimeter({0.0, 0.0, 0.0, 0.0})
    , m_position({0.0, 0.0})
    , m_radius(radius)
    , m_reflectivity(reflectivity)
    , m_angle_i(angle_i)
    , m_angle_f(angle_f)
{
    update_perimeter();
}

ConcaveReflector::ConcaveReflector(float radius, float reflectivity)
    : m_perimeter({0.0, 0.0, 0.0, 0.0})
    , m_position({0.0, 0.0})
    , m_radius(radius)
    , m_reflectivity(reflectivity)
    , m_angle_i(0.0)
    , m_angle_f(360.0)
{
    update_perimeter();
}

ConcaveReflector::~ConcaveReflector()
{
}

void ConcaveReflector::update_perimeter()
{
    Float2 p1{-m_radius, -m_radius};
    Float2 p2{m_radius, m_radius};
    translate(p1, m_position);
    translate(p2, m_position);
    if (p1.v1 < p2.v1) {
        m_perimeter.xmin = p1.v1;
        m_perimeter.xmax = p2.v1;
    } else {
        m_perimeter.xmin = p2.v1;
        m_perimeter.xmax = p1.v1;
    }
    if (p1.v2 < p2.v2) {
        m_perimeter.zmin = p1.v2;
        m_perimeter.zmax = p2.v2;
    } else {
        m_perimeter.zmin = p2.v2;
        m_perimeter.zmax = p1.v2;
    }
}

void ConcaveReflector::translate(Float2& point, Float2 distance) const
{
    point.v1 += distance.v1;
    point.v2 += distance.v2;
}

void ConcaveReflector::translate(Float2 distance)
{
    m_position.v1 += distance.v1;
    m_position.v2 += distance.v2;
    update_perimeter();
}

void ConcaveReflector::rotate(float angle)
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * m_position.v1 + sint * m_position.v2;
    float tz = -sint * m_position.v1 + cost * m_position.v2;
    m_position = {tx, tz};

    m_angle_i += angle;
    m_angle_f += angle;
    update_perimeter();
}

bool ConcaveReflector::angle_within_range(float angle) const
{
    while (angle < m_angle_i) {
        angle += 360.0;
    }
    while (angle > m_angle_f) {
        angle -= 360.0;
    }
    return angle >= m_angle_i;
}

bool ConcaveReflector::within_distance(const Ball* ball) const
{
    double dx = ball->position().v1 - m_position.v1;
    double dz = ball->position().v2 - m_position.v2;

    float distance = sqrt(dx * dx + dz * dz);

    return (distance >= (m_radius - ball->radius()))
        && (distance <= (m_radius + ball->radius()));
}

void ConcaveReflector::collide(Ball* ball) const
{
    if (ball->quick_test(m_perimeter)) {
        if (within_distance(ball)) {
            float dx = ball->position().v1 - m_position.v1;
            float dz = ball->position().v2 - m_position.v2;
            float angle = (180.0 / PI) * atan2(-dz, dx);
            if (angle_within_range(angle)) {
                float rot_angle = angle + 90.0;
                Ball ball_copy = *ball;
                // translate reflector to (0, 0) and bring ball position and velocity
                ball_copy.translate_frame({-m_position.v1, -m_position.v2});
                // rotate reflector by -angle and bring ball position and velocity
                ball_copy.rotate_frame(-rot_angle);
                // translate reflector by (0, -radius) and bring ball position and velocity
                ball_copy.translate_frame({0.0, -m_radius});
                // negate ball z velocity
                Float2 temp = ball_copy.velocity();
                if (temp.v2 > 0.0) {
                    temp.v2 *= m_reflectivity;
                    ball_copy.set_velocity({temp.v1, -temp.v2});
                }
                // ball z pos -= (ball_z + radius)
                temp = ball_copy.position();
                ball_copy.set_position({temp.v1, (float) -2.0 * ball_copy.radius() - temp.v2});
                // translate reflector by (0, radius) and bring ball position and velocity
                ball_copy.translate_frame({0, m_radius});
                // rotate reflector by angle and bring ball position and velocity
                ball_copy.rotate_frame(rot_angle);
                // translate reflector to position and bring ball position and velocity
                ball_copy.translate_frame({m_position.v1, m_position.v2});
                // replace ball with new info
                *ball = ball_copy;
            }
        }
    }
}

