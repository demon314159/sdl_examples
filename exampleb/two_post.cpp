//
// two_post.cpp
//

#include "two_post.h"
#include "pi.h"
#include "plane_shape.h"
#include "cone_shape.h"
#include "toroid_shape.h"
#include "pipe_shape.h"
#include "convex_plane_shape.h"
#include "cylinder_shape.h"
#include "crown_nut_shape.h"
#include <math.h>

#include <stdio.h>


TwoPost::TwoPost(Float2 p1, Float2 p2, float radius, float height,
                 const PaintCan& color, const PaintCan& face_color,
                 float reflectivity, int steps, int sensor_id, int sensor_side,
                 bool no_nut1, bool no_nut2)
    : m_p1(p1)
    , m_p2(p2)
    , m_radius(radius)
    , m_height(height)
    , m_color(color)
    , m_face_color(face_color)
    , m_steps(steps)
    , m_sensor_id(sensor_id)
    , m_sensor_side(sensor_side)
    , m_no_nut1(no_nut1)
    , m_no_nut2(no_nut2)
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

TwoPost::~TwoPost()
{
}

void TwoPost::collide(Ball* ball, Sensor* sensor) const
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

CadModel TwoPost::model(float animation_id) const
{
    CadModel mm;

    float rbumper = 0.00211;
    float r0_post = 0.56818 * m_radius;
    float r1_post = 0.47727 * m_radius;
    float r2_post = 0.25 * m_radius;
    float h1_post = 0.863636 * m_height;
    float h2_post = 1.1363636 * m_height;
    float h3_post = 1.54545 * m_height;
    float h4_post = h3_post + m_radius / 5.0;
    float h5_post = h4_post + m_height / 5.0;

    CadModel big_post(ConeShape(r0_post, r1_post, h1_post, m_steps), m_color, animation_id);
    CadModel big_post2(ConeShape(r1_post, r1_post, h2_post - h1_post, m_steps), m_color, animation_id);
    CadModel big_post3(ConeShape(r1_post, r2_post, h3_post - h2_post, m_steps), m_color, animation_id);
    big_post.add(big_post2, 0.0, h1_post, 0.0);
    big_post.add(big_post3, 0.0, h2_post, 0.0);

    CadModel b1(ToroidShape(m_radius - rbumper, rbumper, m_steps, m_reflector1.angle_i(), m_reflector1.angle_f()), PaintCan(1.0, 1.0, 1.0), animation_id);
    b1.rotate_ay(90.0);
    CadModel b2(ToroidShape(m_radius - rbumper, rbumper, m_steps, m_reflector2.angle_i(), m_reflector2.angle_f()), PaintCan(1.0, 1.0, 1.0), animation_id);
    b2.rotate_ay(90.0);

    CadModel b3(PipeShape(rbumper, m_reflector3.length(), m_steps), m_color, animation_id);
    b3.translate(-m_reflector3.length() / 2.0, 0.0, rbumper);
    b3.rotate_ay(m_reflector3.angle());
    CadModel b4(PipeShape(rbumper, m_reflector4.length(), m_steps), m_color, animation_id);
    b4.translate(-m_reflector4.length() / 2.0, 0.0, rbumper);
    b4.rotate_ay(m_reflector4.angle());

    mm.add(big_post, m_p1.v1, 0.0, m_p1.v2);
    mm.add(big_post, m_p2.v1, 0.0, m_p2.v2);
    mm.add(b1, m_p1.v1, m_height, m_p1.v2);
    mm.add(b2, m_p2.v1, m_height, m_p2.v2);
    mm.add(b3, m_reflector3.position().v1, m_height, m_reflector3.position().v2);
    mm.add(b4, m_reflector4.position().v1, m_height, m_reflector4.position().v2);

    CadModel crown_nut(CrownNutShape(0.003, 0.002, 25, 25), PaintCan(1.0, 1.0, 1.0), 0.0);
    if (!m_no_nut1) {
        mm.add(crown_nut, m_p1.v1, h3_post, m_p1.v2);
    }
    if (!m_no_nut2) {
        mm.add(crown_nut, m_p2.v1, h3_post, m_p2.v2);
    }
    return mm;
}


