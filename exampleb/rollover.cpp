//
// rollover.cpp
//

#include "rollover.h"
#include "pipe.h"
#include "pipe_elbow.h"
#include "pi.h"
#include <math.h>

#include <stdio.h>


Rollover::Rollover(float angle, Float3 position, float length, float width, float diameter,
           const PaintCan& color, int steps)
    : m_angle(angle)
    , m_position(position)
    , m_length(length)
    , m_width(width)
    , m_diameter(diameter)
    , m_color(color)
    , m_steps(steps)
{
}

Rollover::~Rollover()
{
}

float Rollover::angle() const
{
    return m_angle;
}

Float3 Rollover::position() const
{
    return m_position;
}

float Rollover::length() const
{
    return m_length;
}

float Rollover::width() const
{
    return m_width;
}

float Rollover::diameter() const
{
    return m_diameter;
}

void Rollover::collide(const Ball* ball) const
{
}

CadModel Rollover::model(float animation_id) const
{
    CadModel mm;
    float x0 = 0.0;
    float x1 = m_length * 0.8;
    float z0 = 0.0;
    float xt = 0.7 * (x1 - x0);
    float zt = 0.2 * (x1 - x0);
    float lead = 0.1 * (x1 - x0);

    float a0 = 90.0;
    float a1 = atan2(zt, xt) * 180.0 / PI;
    float a2 = (atan2(zt, -((x1 - x0 - xt))) * 180.0 / PI) - 180.0;
    float a3 = -90.0;
    float l1 = sqrt(zt * zt + xt * xt);
    float l2 = sqrt(zt * zt + (x1 - x0 - xt) * (x1 - x0 - xt));
//    printf("x0 = %.3f, z0 = %.3f, x1 = %.3f, xt = %.3f, zt = %.3f\n", x0, z0, x1, xt, zt);
//    printf("a1 = %.3f, a2 = %.3f, l1 = %.3f, l2 = %.3f\n", a1, a2, l1, l2);

    Pipe p0(a0, {x0, 0.0, z0}, m_diameter / 2.0, lead, m_color, m_steps);
    PipeElbow p01(p0.end_angle(), p0.end_position(), m_diameter / 2.0, a1 - a0, m_diameter, m_color, m_steps, m_steps);
    Pipe p1(p01.end_angle(), p01.end_position(), m_diameter / 2.0, l1, m_color, m_steps);
    PipeElbow p12(p1.end_angle(), p1.end_position(), m_diameter / 2.0, a2 - a1, m_diameter, m_color, m_steps, m_steps);
    Pipe p2(p12.end_angle(), p12.end_position(), m_diameter / 2.0, l2, m_color, m_steps);
    PipeElbow p23(p2.end_angle(), p2.end_position(), m_diameter / 2.0, a3 - a2, m_diameter, m_color, m_steps, m_steps);
    Pipe p3(p23.end_angle(), p23.end_position(), m_diameter / 2.0, lead, m_color, m_steps);
    float actual_length = p3.end_position().v1;
    printf("m_length = %.6f, ideal_length = %.6f, actual length = %.6f\n", m_length, x1, actual_length);

    mm.add(p0.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p01.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p1.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p12.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p2.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p23.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p3.model(0.0), 0.0, 0.0, 0.0);

    mm.rotate_ax(90.0);
    mm.rotate_ay(m_angle);
    mm.translate(m_position.v1, m_position.v2 - 1.5 * lead, m_position.v3 + actual_length / 2.0);
    return mm;
}


