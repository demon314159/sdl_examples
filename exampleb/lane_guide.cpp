//
// lane_guide.cpp
//

#include "lane_guide.h"
#include "pipe.h"
#include "pipe_elbow.h"
#include "cube_shape.h"
#include "pi.h"
#include <math.h>

#include <stdio.h>

LaneGuide::LaneGuide(float angle, Float3 position, float length, float height, float diameter,
                     const PaintCan& color, int reflectivity, int steps)
    : m_angle(angle)
    , m_position(position)
    , m_length(length)
    , m_height(height)
    , m_diameter(diameter)
    , m_color(color)
    , m_steps(steps)
    , m_reflector1(true, diameter / 2.0, diameter / 2.0, length, reflectivity)
    , m_reflector2(false, diameter / 2.0, diameter / 2.0, length, reflectivity)
    , m_reflector3(true, diameter / 2.0, diameter / 2.0, length, reflectivity)
    , m_reflector4(false, diameter / 2.0, diameter / 2.0, length, reflectivity)
{
    m_reflector1.rotate(angle);
    m_reflector1.translate({position.v1, position.v3});
    m_reflector2.rotate(angle);
    m_reflector2.translate({position.v1, position.v3});
    m_reflector3.rotate(angle);
    m_reflector3.translate({position.v1, position.v3});
    m_reflector4.rotate(angle);
    m_reflector4.translate({position.v1, position.v3});
}

LaneGuide::~LaneGuide()
{
}

float LaneGuide::angle() const
{
    return m_angle;
}

Float3 LaneGuide::position() const
{
    return m_position;
}

float LaneGuide::length() const
{
    return m_length;
}

float LaneGuide::height() const
{
    return m_height;
}

float LaneGuide::diameter() const
{
    return m_diameter;
}

void LaneGuide::collide(Ball* ball) const
{
    m_reflector1.collide(ball);
    m_reflector2.collide(ball);
    m_reflector3.collide(ball);
    m_reflector4.collide(ball);
}

CadModel LaneGuide::model(float animation_id) const
{
    CadModel mm;

    float a0 = 90.0;
    float a1 = 0.0;
    float a2 = -90.0;

    CadModel base(CubeShape(m_length, m_diameter / 4.0f, m_diameter), m_color, 0.0);
    Pipe p0(a0, {0.0, 0.0, 0.0}, m_diameter / 2.0, m_height, m_color, m_steps);
    PipeElbow p01(p0.end_angle(), p0.end_position(), m_diameter / 2.0, a1 - a0, m_diameter, m_color, m_steps, m_steps);
    float extra = p01.end_position().v1;
    Pipe p1(p01.end_angle(), p01.end_position(), m_diameter / 2.0, m_length - 2.0 * extra, m_color, m_steps);
    PipeElbow p12(p1.end_angle(), p1.end_position(), m_diameter / 2.0, a2 - a1, m_diameter, m_color, m_steps, m_steps);
    Pipe p2(p12.end_angle(), p12.end_position(), m_diameter / 2.0, m_height, m_color, m_steps);
    mm.add(p0.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p01.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p1.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p12.model(0.0), 0.0, 0.0, 0.0);
    mm.add(p2.model(0.0), 0.0, 0.0, 0.0);
    mm.rotate_ax(90.0);
    mm.add(base, m_length / 2.0, m_diameter / 8.0, 0.0);
    mm.rotate_ay(m_angle);
    mm.translate(m_position.v1, m_position.v2, m_position.v3);
    return mm;
}


