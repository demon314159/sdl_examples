//
// lane_guide.cpp
//

#include "lane_guide.h"
#include "pipe.h"
#include "pipe_elbow.h"
#include "cube_shape.h"
#include "cylinder_shape.h"
#include "ring_shape.h"
#include "toroid_shape.h"
#include "triangular_prism_shape.h"
#include "cone_shape.h"
#include "pi.h"
#include <math.h>

#include <stdio.h>

LaneGuide::LaneGuide(float angle, Float3 position, float length, float height, float width,
                     const PaintCan& color, float reflectivity, int steps)
    : m_angle(angle)
    , m_position(position)
    , m_length(length)
    , m_height(height)
    , m_width(width)
    , m_color(color)
    , m_steps(steps)
    , m_reflector1(true, width / 2.0, width / 2.0, length, reflectivity)
    , m_reflector2(false, width / 2.0, width / 2.0, length, reflectivity)
    , m_reflector3(true, width / 2.0, width / 2.0, length, reflectivity)
    , m_reflector4(false, width / 2.0, width / 2.0, length, reflectivity)
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

float LaneGuide::width() const
{
    return m_width;
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
    float fpost = 0.75;
    float f1 = fpost * 0.75;
    float f0 = 0.35;
    float rbumper = 0.002;
    CadModel mm;
    CadModel cone(ConeShape(f1 * m_width / 2.0, m_height, m_steps, 0.001), PaintCan(0.42, 0.42, 0.42), 0.0);
    CadModel bumper(ToroidShape(m_width / 2.0 - rbumper, rbumper, m_steps), PaintCan(1.0, 1.0, 1.0), 0.0);
    CadModel base(CubeShape(m_length, m_width / 8.0, fpost * m_width), m_color, 0.0);
    CadModel big_post(CylinderShape(f1 * m_width / 2.0, m_height, m_steps), m_color, 0.0);
    CadModel little_post(RingShape(fpost * m_width / 2.0, 0.0, (f0 * m_height), m_steps, m_width / 16.0), m_color, 0.0);
    CadModel prism(TriangularPrismShape(m_length - m_width, m_width, m_height * 1.5, m_width / 8.0), m_color, 0.0);
    mm.add(cone, 0.0, m_height / 2.0, 0.0);
    mm.add(cone, m_length, m_height / 2.0, 0.0);
    mm.add(bumper, 0.0, m_height, 0.0);
    mm.add(bumper, m_length, m_height, 0.0);
    mm.add(base, m_length / 2.0, m_width / 16.0, 0.0);
    mm.add(big_post, 0.0,  m_height / 2.0, 0.0);
    mm.add(little_post, 0.0,  f0 * m_height / 2.0, 0.0);
    mm.add(big_post, m_length,  m_height / 2.0, 0.0);
    mm.add(little_post, m_length,  f0 * m_height / 2.0, 0.0);
    mm.add(prism, m_length/ 2.0, 0.0, 0.0);
    mm.rotate_ay(m_angle);
    mm.translate(m_position.v1, m_position.v2, m_position.v3);
    return mm;
}


