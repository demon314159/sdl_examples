//
// pipe.cpp
//

#include "pipe.h"
#include "pipe_shape.h"
#include "pi.h"
#include <math.h>

Pipe::Pipe(float angle, Float3 position, float radius, float length, const PaintCan& color, int steps)
    : m_angle(angle)
    , m_position(position)
    , m_radius(radius)
    , m_length(length)
    , m_color(color)
    , m_steps(steps)
{
}

Pipe::~Pipe()
{
}

float Pipe::angle() const
{
    return m_angle;
}

Float3 Pipe::position() const
{
    return m_position;
}

float Pipe::end_angle() const
{
    return m_angle;
}

Float3 Pipe::end_position() const
{
    float xe, ze, xr, zr;
    xe = m_length;
    ze = 0.0;
    xr = xe * cos(m_angle * PI / 180.0);
    zr = -xe * sin(m_angle * PI / 180.0);
    return {m_position.v1 + xr, m_position.v2, m_position.v3 + zr};
}

CadModel Pipe::model(float animation_id) const
{
    CadModel pipe(PipeShape(m_radius, m_length, m_steps), m_color, 0.0);
    pipe.rotate_ay(m_angle);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(pipe, m_position.v1, m_position.v2, m_position.v3);
    return mm;
}


