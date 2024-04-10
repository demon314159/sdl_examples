//
// drop_target.cpp
//

#include "drop_target.h"
#include "cube_shape.h"
#include "rounded_cube_shape.h"

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
    float w = m_width;
    float h = w * 1.325;
    float t = w / 4.0;
    float r = t / 4.0;
    float sw = w * 0.575;
    float st = t - 2.0 * r;

    CadModel target(RoundedCubeShape(w, t, h, r, m_steps, true, false), m_color, 1.0);
    CadModel tile0(RoundedCubeShape(w, t, h, r, m_steps, false, true), m_color, 0.0);
    CadModel stem(CubeShape(sw, st, h), m_color, 0.0);
    target.add(tile0);
    target.add(stem, 0.0, 0.0, -h);
    target.rotate_ax(-90.0);
    target.rotate_ay(m_angle);
    target.translate(m_position.v1, h / 2.0 - 0.2 * h, m_position.v2);
    return target;
}
