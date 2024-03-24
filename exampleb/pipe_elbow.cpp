//
// pipe_elbow.cpp
//

#include "pipe_elbow.h"
#include "pipe_elbow_shape.h"
#include "pi.h"
#include <math.h>

PipeElbow::PipeElbow(float angle, Float3 position, float radius, float bend_angle, float bend_radius,
                     const PaintCan& color, int steps, int bend_steps)
    : m_angle(angle)
    , m_position(position)
    , m_radius(radius)
    , m_bend_angle(bend_angle)
    , m_bend_radius(bend_radius)
    , m_color(color)
    , m_steps(steps)
    , m_bend_steps(bend_steps)
{
}

PipeElbow::~PipeElbow()
{
}

float PipeElbow::angle() const
{
    return m_angle;
}

Float3 PipeElbow::position() const
{
    return m_position;
}

float PipeElbow::end_angle() const
{
    return m_angle + m_bend_angle;
}

Float3 PipeElbow::end_position() const
{
    float xc, zc, xe, ze;
    if (m_bend_angle >= 0.0) {
        xc = 0.0;
        zc = -m_bend_radius;
        xe = xc + m_bend_radius * sin(m_bend_angle * PI / 180.0);
        ze = zc + m_bend_radius * cos(m_bend_angle * PI / 180.0);
    } else {
        xc = 0.0;
        zc = m_bend_radius;
        xe = xc - m_bend_radius * sin(m_bend_angle * PI / 180.0);
        ze = zc - m_bend_radius * cos(m_bend_angle * PI / 180.0);
    }
    float xr = xe * cos(m_angle * PI / 180.0) + ze * sin(m_angle * PI / 180.0);
    float zr = -xe * sin(m_angle * PI / 180.0) + ze * cos(m_angle * PI / 180.0);
    return {m_position.v1 + xr, m_position.v2, m_position.v3 + zr};
}

CadModel PipeElbow::model(float animation_id) const
{
    CadModel elbow(PipeElbowShape(m_radius, m_bend_radius, m_bend_angle, m_steps, m_bend_steps), m_color, 0.0);
    elbow.rotate_ay(m_angle);
    CadModel mm;
    mm.add(elbow, m_position.v1, m_position.v2, m_position.v3);
    return mm;
}


