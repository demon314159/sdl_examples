//
// conivex_strip.cpp
//

#include "convex_strip.h"
#include "convex_plane_shape.h"

ConvexStrip::ConvexStrip(float angle_i, float angle_f, Float3 position, float radius, float height, const PaintCan& color, float reflectivity, int steps)
    : m_angle_i(angle_i)
    , m_angle_f(angle_f)
    , m_position(position)
    , m_radius(radius)
    , m_height(height)
    , m_steps(steps)
    , m_color(color)
    , m_reflector({position.v1, position.v3}, radius, angle_i, angle_f, reflectivity)
{
    m_reflector.translate({position.v1, position.v3});
}

ConvexStrip::~ConvexStrip()
{
}

float ConvexStrip::angle_i() const
{
    return m_angle_i;
}

float ConvexStrip::angle_f() const
{
    return m_angle_f;
}

Float3 ConvexStrip::position() const
{
    return m_position;
}

float ConvexStrip::radius() const
{
    return m_radius;
}

void ConvexStrip::collide(Ball* ball) const
{
    m_reflector.collide(ball);
}

CadModel ConvexStrip::model(float animation_id) const
{
    CadModel strip(ConvexPlaneShape(m_radius, m_angle_i, m_angle_f, m_height, m_steps), m_color, 0.0);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(strip, pos.v1, pos.v2, pos.v3);
    return mm;
}
