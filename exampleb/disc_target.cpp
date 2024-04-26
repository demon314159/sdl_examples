//
// disc_target.cpp
//

#include "disc_target.h"
#include "ring_shape.h"

DiscTarget::DiscTarget(Float2 position, float angle, float radius, float width, const PaintCan& color1,
                       const PaintCan& color2, const PaintCan& color3, float reflectivity, int steps,
                       int sensor_id)
    : m_position(position)
    , m_angle(angle)
    , m_radius(radius)
    , m_width(width)
    , m_color1(color1)
    , m_color2(color2)
    , m_color3(color3)
    , m_steps(steps)
    , m_sensor_id(sensor_id)
    , m_reflector(2.0f * radius, reflectivity)
{
    m_reflector.rotate(angle);
    m_reflector.translate({position.v1, position.v2 - width / 2.0f});
}

DiscTarget::~DiscTarget()
{
}

void DiscTarget::collide(Ball* ball, Sensor* sensor) const
{
    bool res = m_reflector.collide(ball);
    if (res && m_sensor_id) {
        sensor->set(m_sensor_id);
    }
}

CadModel DiscTarget::model(float animation_id) const
{
    float r1 = m_radius;
    float r2 = m_radius * 2.0 / 3.0;
    float r3 = m_radius * 1.0 / 3.0;
    float r4 = r3 / 3.0;
    CadModel disc(RingShape(r1, r2, m_width, m_steps), m_color1, animation_id);
    CadModel disc2(RingShape(r2, r3, m_width, m_steps), m_color2, animation_id);
    CadModel disc3(RingShape(r3, r4, m_width, m_steps), m_color3, animation_id);
    disc.add(disc2);
    disc.add(disc3);
    disc.rotate_ax(90.0);
    disc.rotate_ay(m_angle);
    CadModel mm;
    mm.add(disc, m_position.v1, m_radius + 0.002, m_position.v2);
    return mm;
}
