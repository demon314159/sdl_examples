//
// well.cpp
//

#include "well.h"
#include "pi.h"
#include <math.h>
#include "cylinder_shape.h"

Well::Well(Float2 p1, float radius, float depth)
    : m_p1(p1)
    , m_radius(radius)
    , m_depth(depth)
{
}

Well::~Well()
{
}

void Well::collide(Ball* ball) const
{
}

CadModel Well::model(float animation_id) const
{
    CadModel mm;

    CadModel cc(CylinderShape(m_radius, m_depth, 20), PaintCan(1.0, 0.0, 0.0), animation_id);
    mm.add(cc, m_p1.v1, m_depth / 2.0, m_p1.v2);

    return mm;
}

