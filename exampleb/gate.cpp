//
// gate.cpp
//

#include "gate.h"
#include "pi.h"
#include "rounded_plane_shape.h"
#include <math.h>

Gate::Gate(Float2 position, float width, float length, float height, float angle,
                 const PaintCan& color, float reflectivity, int steps)
    : m_position(position)
    , m_width(width)
    , m_length(length)
    , m_height(height)
    , m_angle(angle)
    , m_color(color)
    , m_steps(steps)
{
}

Gate::~Gate()
{
}

void Gate::collide(Ball* ball) const
{
}

CadModel Gate::model(float animation_id) const
{
    CadModel mm;

    float t1 = 0.004;
    float br = 0.010;

    CadModel base(RoundedPlaneShape(m_width, t1, m_length, 0.0, br, 25), m_color, animation_id);

    mm.add(base, m_position.v1, t1 / 2.0, m_position.v2);
    return mm;
}


