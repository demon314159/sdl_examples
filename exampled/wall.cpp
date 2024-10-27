//
// wall.cpp
//

#include "wall.h"
#include "pi.h"
#include "cube_shape.h"
#include "cylinder_shape.h"
#include <math.h>

Wall::Wall(Float2 p1, Float2 p2, float radius, float height,
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

Wall::~Wall()
{
}

void Wall::collide(Ball* ball) const
{
    m_reflector1.collide(ball);
    m_reflector2.collide(ball);
    m_reflector3.collide(ball);
    m_reflector4.collide(ball);
}

CadModel Wall::model(float animation_id) const
{
    CadModel mm;

    CadModel block(CubeShape(m_reflector3.length(), m_height, m_radius * 2.0f), m_color, animation_id);
    CadModel cylinder(CylinderShape(m_radius, m_height, m_steps), m_color, animation_id);
    block.rotate_ay(m_reflector3.angle());
    mm.add(block, (m_p1.v1 + m_p2.v1) / 2.0f, m_height / 2.0f, (m_p1.v2 + m_p2.v2) / 2.0f);
    mm.add(cylinder, m_p1.v1, m_height / 2.0f, m_p1.v2);
    mm.add(cylinder, m_p2.v1, m_height / 2.0f, m_p2.v2);
    return mm;
}


