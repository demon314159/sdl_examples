//
// three_post.cpp
//

#include "three_post.h"
#include "pi.h"
#include "plane_shape.h"
#include "convex_plane_shape.h"
#include "cylinder_shape.h"
#include <math.h>

ThreePost::ThreePost(Float2 p1, Float2 p2, Float2 p3, float radius, float height,
                     const PaintCan& color, const PaintCan& face_color, float reflectivity, int steps)
    : m_p1(p1)
    , m_p2(p2)
    , m_p3(p3)
    , m_radius(radius)
    , m_height(height)
    , m_color(color)
    , m_face_color(face_color)
    , m_steps(steps)
    , m_reflector1(p3, p1, p2, radius, reflectivity)
    , m_reflector2(p1, p2, p3, radius, reflectivity)
    , m_reflector3(p2, p3, p1, radius, reflectivity)
    , m_reflector4(p1, p2, radius, reflectivity)
    , m_reflector5(p2, p3, radius, reflectivity)
    , m_reflector6(p3, p1, radius, reflectivity)
{
}

ThreePost::~ThreePost()
{
}

void ThreePost::collide(Ball* ball) const
{
    m_reflector1.collide(ball);
    m_reflector2.collide(ball);
    m_reflector3.collide(ball);
    m_reflector4.collide(ball);
    m_reflector5.collide(ball);
    m_reflector6.collide(ball);
}

CadModel ThreePost::model(float animation_id) const
{
    CadModel mm;
    CadModel f4(PlaneShape(m_reflector4.length(), m_height), m_color, 0.0);
    f4.rotate_ax(-90.0);
    f4.rotate_ay(m_reflector4.angle());
    f4.translate(m_reflector4.position().v1, m_height / 2.0, m_reflector4.position().v2);
    mm.add(f4, 0.0, 0.0, 0.0);
    CadModel f5(PlaneShape(m_reflector5.length(), m_height), m_color, 0.0);
    f5.rotate_ax(-90.0);
    f5.rotate_ay(m_reflector5.angle());
    f5.translate(m_reflector5.position().v1, m_height / 2.0, m_reflector5.position().v2);
    mm.add(f5, 0.0, 0.0, 0.0);
    CadModel f6(PlaneShape(m_reflector6.length(), m_height), m_color, 0.0);
    f6.rotate_ax(-90.0);
    f6.rotate_ay(m_reflector6.angle());
    f6.translate(m_reflector6.position().v1, m_height / 2.0, m_reflector6.position().v2);
    mm.add(f6, 0.0, 0.0, 0.0);
    CadModel p1(ConvexPlaneShape(m_reflector1.radius(), m_reflector1.angle_i(), m_reflector1.angle_f(), m_height, m_steps), m_color, 0.0);
    p1.translate(m_reflector1.position().v1, m_height / 2.0, m_reflector1.position().v2);
    mm.add(p1, 0.0, 0.0, 0.0);
    CadModel p2(ConvexPlaneShape(m_reflector2.radius(), m_reflector2.angle_i(), m_reflector2.angle_f(), m_height, m_steps), m_color, 0.0);
    p2.translate(m_reflector2.position().v1, m_height / 2.0, m_reflector2.position().v2);
    mm.add(p2, 0.0, 0.0, 0.0);
    CadModel p3(ConvexPlaneShape(m_reflector3.radius(), m_reflector3.angle_i(), m_reflector3.angle_f(), m_height, m_steps), m_color, 0.0);
    p3.translate(m_reflector3.position().v1, m_height / 2.0, m_reflector3.position().v2);
    mm.add(p3, 0.0, 0.0, 0.0);
    return mm;
}


