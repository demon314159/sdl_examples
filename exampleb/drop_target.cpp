//
// drop_target.cpp
//

#include "drop_target.h"
#include "cube_shape.h"

DropTarget::DropTarget(Float2 position, float angle, float width, float height, float thickness,
                       const PaintCan& color, float reflectivity, int steps)
    : m_position(position)
    , m_angle(angle)
    , m_width(width)
    , m_height(height)
    , m_thickness(thickness)
    , m_color(color)
    , m_steps(steps)
    , m_reflector(width, reflectivity)
{
    m_reflector.rotate(angle);
    m_reflector.translate({position.v1, position.v2 - thickness / 2.0f});
}

DropTarget::~DropTarget()
{
}

void DropTarget::collide(Ball* ball) const
{
    m_reflector.collide(ball);
}

CadModel DropTarget::model(float animation_id) const
{
    CadModel cube(CubeShape(m_width, m_height, m_thickness), m_color, animation_id);
    cube.rotate_ay(m_angle);
    CadModel mm;
    mm.add(cube, m_position.v1, m_height / 2.0, m_position.v2);
    return mm;
}
