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
    float h = m_height;
    CadModel cube1(CubeShape(m_width, m_thickness, m_height, true, false), m_color, 1.0);
    CadModel cube2(CubeShape(m_width, m_thickness, m_height, false, true), m_color, animation_id);
    CadModel cube3(CubeShape(0.575 * m_width, m_thickness, h, true, false), m_color, 1.0);
    CadModel cube4(CubeShape(0.575 * m_width, m_thickness, h, false, true), m_color, animation_id);
    cube1.rotate_ax(-90.0);
    cube2.rotate_ax(-90.0);
    cube3.rotate_ax(-90.0);
    cube4.rotate_ax(-90.0);
    cube1.rotate_ay(m_angle);
    cube2.rotate_ay(m_angle);
    cube3.rotate_ay(m_angle);
    cube4.rotate_ay(m_angle);
    CadModel mm;
    mm.add(cube1, m_position.v1, m_height / 2.0, m_position.v2);
    mm.add(cube2, m_position.v1, m_height / 2.0, m_position.v2);
    mm.add(cube3, m_position.v1, -h / 2.0, m_position.v2);
    mm.add(cube4, m_position.v1, -h / 2.0, m_position.v2);
    mm.translate(0.0, -m_height / 5.0, 0.0);
    return mm;
}
