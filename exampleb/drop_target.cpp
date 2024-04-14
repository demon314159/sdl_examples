//
// drop_target.cpp
//

#include "drop_target.h"
#include "cube_shape.h"
#include "plane_shape.h"
#include "rounded_cube_shape.h"

#define OFFSET (-0.002f)

DropTarget::DropTarget(Float2 position, float angle, float width, float height, float thickness,
                       const PaintCan& color, float reflectivity, int steps,
                       float texture_id, int section)
    : m_dropped(false)
    , m_position(position)
    , m_angle(angle)
    , m_width(width)
    , m_height(height)
    , m_thickness(thickness)
    , m_color(color)
    , m_steps(steps)
    , m_texture_id(texture_id)
    , m_section(section)
    , m_reflector1({0.0, 0.0}, thickness / 4.0, 90.0, 180.0, reflectivity)
    , m_reflector2({0.0, 0.0}, thickness / 4.0, 0.0, 90.0, reflectivity)
    , m_reflector3(width - 2.0 * thickness / 4.0, reflectivity)
{
    m_reflector1.translate({-width / 2.0f + thickness / 4.0f, OFFSET + thickness / 2.0f + thickness / 4.0f});
    m_reflector1.rotate(angle);
    m_reflector2.translate({width / 2.0f - thickness / 4.0f, OFFSET - thickness / 2.0f + thickness / 4.0f});
    m_reflector2.rotate(angle);
    m_reflector3.translate({0.0, OFFSET - thickness / 2.0f});
    m_reflector3.rotate(angle);
    m_reflector1.translate(m_position);
    m_reflector2.translate(m_position);
    m_reflector3.translate(m_position);
}

DropTarget::~DropTarget()
{
}

bool DropTarget::dropped() const
{
    return m_dropped;
}

void DropTarget::set_dropped(bool v)
{
    m_dropped = v;
}

void DropTarget::collide(Ball* ball) const
{
    m_reflector1.collide(ball);
    m_reflector2.collide(ball);
    m_reflector3.collide(ball);
}

CadModel DropTarget::model(float animation_id) const
{
    float w = m_width;
    float h = w * 1.325;
    float t = m_thickness;
    float r = t / 4.0;
    float sw = w * 0.575;
    float st = t - 2.0 * r;
    CadModel mm;
//    CadModel target(RoundedCubeShape(w, t, h, r, m_steps, true, false), m_color, 1.0);

    Float2 p1;
    Float2 p2;
    if (m_section > 4) {
         p1.v1 = 0.2 * (float) (m_section - 5 + 1);
         p1.v2 = 1.0;
         p2.v1 = 0.2 * (float) (m_section - 5);
         p2.v2 = 0.5;
    } else {
         p1.v1 = 0.2 * (float) (m_section + 1);
         p1.v2 = 0.5;
         p2.v1 = 0.2 * (float) m_section;
         p2.v2 = 0.0;
    }

    CadModel target(PlaneShape(w - t / 2.0, h - t / 2.0, m_texture_id, p1, p2), m_color, animation_id);
    mm.add(target, 0.0, t / 2.0, 0.0);

    CadModel tile0(RoundedCubeShape(w, t, h, r, m_steps, false, true), m_color, animation_id);
    CadModel stem(CubeShape(sw, st, h / 2.0), m_color, animation_id);
    mm.add(tile0);
    mm.add(stem, 0.0, 0.0, -h + h / 4.0);
    mm.rotate_ax(-90.0);

    mm.translate(0.0, 0.0, OFFSET);


    mm.rotate_ay(m_angle);
    mm.translate(m_position.v1, h / 2.0 - 0.2 * h, m_position.v2);
    return mm;
}
