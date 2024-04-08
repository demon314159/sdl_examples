//
// straight_diode_reflector.cpp
//

#include "straight_diode_reflector.h"
#include "pi.h"
#include <math.h>

StraightDiodeReflector::StraightDiodeReflector(float length, float reflectivity)
    : m_perimeter({0.0, 0.0, 0.0, 0.0})
    , m_position({0.0, 0.0})
    , m_length(length)
    , m_reflectivity(reflectivity)
    , m_angle(0.0)
{
    update_perimeter();
}

StraightDiodeReflector::~StraightDiodeReflector()
{
}

void StraightDiodeReflector::update_perimeter()
{
    Float2 p1{-m_length / 2.0, 0.0};
    Float2 p2{m_length / 2.0, 0.0};
    rotate(p1, m_angle);
    rotate(p2, m_angle);
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

void StraightDiodeReflector::translate(Float2 distance)
{
    m_position.v1 += distance.v1;
    m_position.v2 += distance.v2;
    update_perimeter();
}

void StraightDiodeReflector::rotate(float angle)
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * m_position.v1 + sint * m_position.v2;
    float tz = -sint * m_position.v1 + cost * m_position.v2;
    m_position = {tx, tz};

    m_angle += angle;
    update_perimeter();
}

bool StraightDiodeReflector::within_range(const Ball* ball) const
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

void StraightDiodeReflector::collide(Ball* ball) const
{
    ball->light_test();
    if (ball->quick_test(m_perimeter)) {
        ball->light_test_pass();
        Ball ball_copy = *ball;
        // translate reflector to (0, 0) and bring ball position and velocity
        ball_copy.translate_frame({-m_position.v1, -m_position.v2});
        // rotate reflector by -angle and bring ball position and velocity
        ball_copy.rotate_frame(-m_angle);
        // test for ball z position to be more than -radius
        ball->heavy_test();
        if (within_range(&ball_copy)) { // collision
            ball->heavy_test_pass();
            if (ball_copy.velocity().v2 >= 0.0) {
                // negate ball z velocity
                Float2 temp = ball_copy.velocity();
                if (temp.v2 > 0.0) {
                    temp.v2 *= m_reflectivity;
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
    }
}

void StraightDiodeReflector::translate(Float2& point, Float2 distance) const
{
    point.v1 += distance.v1;
    point.v2 += distance.v2;
}

void StraightDiodeReflector::rotate(Float2& point, float angle) const
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * point.v1 + sint * point.v2;
    float tz = -sint * point.v1 + cost * point.v2;
    point = {tx, tz};
}

