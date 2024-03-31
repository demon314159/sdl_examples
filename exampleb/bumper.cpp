//
// bumper.cpp
//

#include "bumper.h"
#include "pi.h"
#include <math.h>

Bumper::Bumper(Float3 p1, Float3 p2, Float3 p3, float radius, float height,
                     const PaintCan& color, const PaintCan& face_color, float reflectivity, int steps)
    : m_p1(p1)
    , m_p2(p2)
    , m_p3(p3)
    , m_radius(radius)
    , m_height(height)
    , m_color(color)
    , m_face_color(face_color)
    , m_steps(steps)
    , m_reflector1(p3, p1, p2, reflectivity)
    , m_reflector2(p1, p2, p3, reflectivity)
    , m_reflector3(p2, p3, p1, reflectivity)
    , m_reflector4(p1, p2, reflectivity)
    , m_reflector5(p2, p3, reflectivity)
    , m_reflector6(p3, p1, reflectivity)
{
}

Bumper::~Bumper()
{
}

void Bumper::collide(Ball* ball) const
{
    m_reflector1.collide(ball);
    m_reflector2.collide(ball);
    m_reflector3.collide(ball);
    m_reflector4.collide(ball);
    m_reflector5.collide(ball);
    m_reflector6.collide(ball);
}

CadModel Bumper::model(float animation_id) const
{
    CadModel mm;

    return mm;
}


