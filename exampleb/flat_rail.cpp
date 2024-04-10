//
// flat_rail.cpp
//

#include "flat_rail.h"
#include "pi.h"
#include <math.h>

#include "cube_shape.h"

FlatRail::FlatRail(Float2 p, float length, float width, float thickness, float bend_radius, float height,
                   const PaintCan& color, float reflectivity, int steps)
    : m_p(p)
    , m_length(length)
    , m_width(width)
    , m_thickness(thickness)
    , m_bend_radius(bend_radius)
    , m_height(height)
    , m_color(color)
    , m_steps(steps)
//    , m_reflector1(reflectivity)
//    , m_reflector2(reflectivity)
//    , m_reflector3(reflectivity)
//    , m_reflector4(reflectivity)
//    , m_reflector5(reflectivity)
//    , m_reflector6(reflectivity)
//    , m_reflector7(reflectivity)
//    , m_reflector8(reflectivity)
{
}

FlatRail::~FlatRail()
{
}

void FlatRail::collide(Ball* ball) const
{
//    m_reflector1.collide(ball);
//    m_reflector2.collide(ball);
//    m_reflector3.collide(ball);
//    m_reflector4.collide(ball);
//    m_reflector5.collide(ball);
//    m_reflector6.collide(ball);
//    m_reflector7.collide(ball);
//    m_reflector8.collide(ball);
}

CadModel FlatRail::model(float animation_id) const
{
    CadModel mm;

    CadModel cube(CubeShape(m_width, m_height, m_length), m_color, animation_id);
//    cube.rotate_ax(-90.0);
//    cube.rotate_ay(90.0);
    mm.add(cube, m_p.v1 - m_width / 2.0, m_height / 2.0, m_p.v2);

    return mm;
}


