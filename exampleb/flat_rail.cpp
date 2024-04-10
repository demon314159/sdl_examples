//
// flat_rail.cpp
//

#include "flat_rail.h"
#include "flat_rail_shape.h"
#include "pi.h"
#include <math.h>

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
    , m_reflector1(bend_radius - thickness, 0.0, acos((bend_radius - width)/ bend_radius) * 180.0 / PI, reflectivity)
    , m_reflector2(bend_radius - thickness, -acos((bend_radius - width)/ bend_radius) * 180.0 / PI, 0.0,  reflectivity)
    , m_reflector3(length - 2.0 * bend_radius * sin(acos((bend_radius - width) / bend_radius)), reflectivity)
{
    float angle = acos((bend_radius - width) / bend_radius) * 180.0 / PI;
    float k = bend_radius * sin(angle * PI / 180.0);
    m_reflector1.translate({-bend_radius, -length / 2.0f + k});
    m_reflector2.translate({-bend_radius, length / 2.0f - k});
    m_reflector3.rotate(90.0);
    m_reflector3.translate({-thickness, 0.0});
    m_reflector1.translate(p);
    m_reflector2.translate(p);
    m_reflector3.translate(p);
}

FlatRail::~FlatRail()
{
}

void FlatRail::collide(Ball* ball) const
{
    m_reflector1.collide(ball);
    m_reflector2.collide(ball);
    m_reflector3.collide(ball);
}

CadModel FlatRail::model(float animation_id) const
{
    CadModel mm;

    CadModel rail(FlatRailShape(m_length, m_width, m_thickness, m_bend_radius, m_height, m_steps), m_color, animation_id);
    mm.add(rail, m_p.v1, m_height / 2.0, m_p.v2);

    return mm;
}


