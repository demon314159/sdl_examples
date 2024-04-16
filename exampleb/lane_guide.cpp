//
// lane_guide.cpp
//

#include "lane_guide.h"
#include "pipe.h"
#include "pipe_elbow.h"
#include "pipe_shape.h"
#include "cube_shape.h"
#include "cylinder_shape.h"
#include "ring_shape.h"
#include "toroid_shape.h"
#include "triangular_prism_shape.h"
#include "cone_shape.h"
#include "pi.h"
#include <math.h>

LaneGuide::LaneGuide(float angle, Float3 position, float length, float height, float width,
                     const PaintCan& color, const PaintCan& face_color, float reflectivity, int steps,
                     int sensor_id, int sensor_side, bool no_hat)
    : m_angle(angle)
    , m_position(position)
    , m_length(length)
    , m_height(height)
    , m_width(width)
    , m_color(color)
    , m_face_color(face_color)
    , m_steps(steps)
    , m_sensor_id(sensor_id)
    , m_sensor_side(sensor_side)
    , m_no_hat(no_hat)
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

void LaneGuide::collide(Ball* ball, Sensor* sensor) const
{
    m_reflector1.collide(ball);
    m_reflector2.collide(ball);
    bool res = m_reflector3.collide(ball);
    if (res && (m_sensor_side == 1) && m_sensor_id) {
        sensor->set(m_sensor_id);
    }
    res = m_reflector4.collide(ball);
    if (res && (m_sensor_side == 2) && m_sensor_id) {
        sensor->set(m_sensor_id);
    }
}

CadModel LaneGuide::model(float animation_id) const
{
    CadModel mm;

    float rbumper = 0.00211;
    float r0_post = 0.56818 * m_width / 2.0;
    float r1_post = 0.47727 * m_width / 2.0;
    float r2_post = 0.25 * m_width / 2.0;
    float h1_post = 0.863636 * m_height;
    float h2_post = 1.1363636 * m_height;
    float h3_post = 1.54545 * m_height;
    float h4_post = h3_post + m_width / 10.0;
    float h5_post = h4_post + m_height / 5.0;

    CadModel base0(CubeShape(m_length, m_width / 10, r0_post * 2.0), m_color, animation_id);
    CadModel base1a(CubeShape(m_length, m_width / 10, r0_post * 2.0, true, false), m_face_color, 1.0);
    CadModel base1b(CubeShape(m_length, m_width / 10, r0_post * 2.0, false, true), m_face_color, animation_id);
    CadModel base2a(CylinderShape(r0_post, m_width / 10, m_steps, true, false), m_face_color, 1.0);
    CadModel base2b(CylinderShape(r0_post, m_width / 10, m_steps, false, true), m_face_color, animation_id);
    CadModel base3(ConeShape(r2_post, 0.001, h5_post - h4_post, m_steps), PaintCan(0.42, 0.42, 0.42), animation_id);
    CadModel big_post1(ConeShape(r0_post, r1_post, h1_post, m_steps), m_color, animation_id);
    CadModel big_post2(ConeShape(r1_post, r1_post, h2_post - h1_post, m_steps), m_color, animation_id);
    CadModel big_post3(ConeShape(r1_post, r2_post, h3_post - h2_post, m_steps), m_color, animation_id);
    CadModel b1(ToroidShape(m_width / 2.0 - rbumper, rbumper, m_steps, -180.0, 0.0), PaintCan(1.0, 1.0, 1.0), animation_id);
    CadModel b2(ToroidShape(m_width / 2.0 - rbumper, rbumper, m_steps, 0.0, 180.0), PaintCan(1.0, 1.0, 1.0), animation_id);
    CadModel b3(PipeShape(rbumper, m_length, m_steps), PaintCan(1.0, 1.0, 1.0), animation_id);

    mm.add(base0, m_length / 2.0, m_width / 20.0, 0.0);
    if (!m_no_hat) {
        mm.add(base1a, m_length / 2.0, h3_post + m_width / 20.0, 0.0);
        mm.add(base1b, m_length / 2.0, h3_post + m_width / 20.0, 0.0);
        mm.add(base2a, 0.0, h3_post + m_width / 20.0, 0.0);
        mm.add(base2b, 0.0, h3_post + m_width / 20.0, 0.0);
        mm.add(base2a, m_length, h3_post + m_width / 20.0, 0.0);
        mm.add(base2b, m_length, h3_post + m_width / 20.0, 0.0);
        mm.add(base3, 0.0, h4_post, 0.0);
        mm.add(base3, m_length, h4_post, 0.0);
    }
    mm.add(big_post1, 0.0,  0.0, 0.0);
    mm.add(big_post2, 0.0,  h1_post, 0.0);
    mm.add(big_post3, 0.0,  h2_post, 0.0);
    mm.add(big_post1, m_length,  0.0, 0.0);
    mm.add(big_post2, m_length,  h1_post, 0.0);
    mm.add(big_post3, m_length,  h2_post, 0.0);
    mm.add(b1, 0.0, m_height, 0.0);
    mm.add(b2, m_length, m_height, 0.0);
    mm.add(b3, 0.0, m_height, m_width / 2.0 - rbumper);
    mm.add(b3, 0.0, m_height, -(m_width / 2.0 - rbumper));
    mm.rotate_ay(m_angle);
    mm.translate(m_position.v1, m_position.v2, m_position.v3);
    return mm;
}


