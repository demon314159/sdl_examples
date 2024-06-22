//
// straight_wire_guide.cpp
//

#include "straight_wire_guide.h"
#include "pipe.h"
#include "pipe_elbow.h"
#include "pi.h"
#include <math.h>

StraightWireGuide::StraightWireGuide(Float2 p1, Float2 p2, float radius, float height,
                                     const PaintCan& color, int reflectivity, int steps)
    : m_p1(p1)
    , m_p2(p2)
    , m_radius(radius)
    , m_height(height)
    , m_color(color)
    , m_steps(steps)
    , m_reflector1(true, radius, reflectivity)
    , m_reflector2(false, radius, reflectivity)
    , m_reflector3(p1, p2, radius, reflectivity)
    , m_reflector4(p2, p1, radius, reflectivity)
{
    m_reflector1.rotate(m_reflector3.angle());
    m_reflector2.rotate(m_reflector3.angle());
    m_reflector1.translate(p1);
    m_reflector2.translate(p2);
}

StraightWireGuide::~StraightWireGuide()
{
}

void StraightWireGuide::collide(Ball* ball) const
{
    m_reflector1.collide(ball);
    m_reflector2.collide(ball);
    m_reflector3.collide(ball);
    m_reflector4.collide(ball);
}

CadModel StraightWireGuide::model(float animation_id) const
{
    CadModel mm;

    float a0 = 90.0;
    float a1 = 0.0;
    float a2 = -90.0;

    Pipe p0(a0, {0.0, 0.0, 0.0}, m_radius, m_height, m_color, m_steps);
    PipeElbow p01(p0.end_angle(), p0.end_position(), m_radius, a1 - a0, m_radius * 2.0, m_color, m_steps, m_steps);
    float extra = p01.end_position().v1;
    Pipe p1(p01.end_angle(), p01.end_position(), m_radius, m_reflector3.length() - 2.0 * extra, m_color, m_steps);
    PipeElbow p12(p1.end_angle(), p1.end_position(), m_radius, a2 - a1, m_radius * 2.0, m_color, m_steps, m_steps);
    Pipe p2(p12.end_angle(), p12.end_position(), m_radius, m_height, m_color, m_steps);
    mm.add(p0.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p01.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p1.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p12.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p2.model(0.0), 0.0, 0.0, 0.0);
    mm.rotate_ax(90.0);
    mm.rotate_ay(m_reflector3.angle());
    mm.translate(m_p1.v1, 0.0, m_p1.v2);
    return mm;
}


