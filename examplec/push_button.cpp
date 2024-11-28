//
// push_button.cpp
//

#include "push_button.h"
#include "button_shape.h"
#include "ring_shape.h"
#include "plane_shape.h"
#include "pi.h"
#include <math.h>

#define PUSH_BUTTON_COLOR PaintCan(1.0, 0.25, 0.25)
#define BEVEL_COLOR PaintCan(0.25, 0.25, 0.25)

#define MAJOR_STEPS 100
#define MINOR_STEPS 20
#define RATIO 6.0f

PushButton::PushButton(float radius, float height, const Float2& position)
    : m_radius(radius)
    , m_height(height)
    , m_position(position)
    , m_pressed(false)
    , m_animate()
{
}

PushButton::~PushButton()
{
}

bool PushButton::mouse_hit(const Float2& mouse_selection)
{
    double dx = mouse_selection.v1 - m_position.v1;
    double dy = mouse_selection.v2 - m_position.v2;
    double r = sqrt(dx * dx + dy * dy);
    m_pressed = (m_radius >= r);
    return m_pressed;
}

void PushButton::release()
{
    m_pressed = false;
}

CadModel PushButton::model(float animation_id, float texture_id) const
{
    float bh = m_height * 0.7f;
    float ri = m_radius + 0.0015;
    float ro = ri + 0.0015;
    float len = 2.0 * m_radius;
    CadModel cm;
    CadModel pb(ButtonShape(m_radius, m_height, m_radius / RATIO, MAJOR_STEPS, MINOR_STEPS), PUSH_BUTTON_COLOR, animation_id);
    CadModel bezel(RingShape(ro, ri, bh, MAJOR_STEPS), BEVEL_COLOR, 0.0);
    CadModel ps(PlaneShape(len, len, texture_id), PUSH_BUTTON_COLOR, animation_id);

    cm.add(pb, m_position.v1, 0.0, -m_position.v2);
    cm.add(bezel, m_position.v1, bh / 2.0, -m_position.v2);
    cm.add(ps, m_position.v1, m_height + 0.001, -m_position.v2);
    return cm;
}

const float* PushButton::data()
{
    m_animate.unity();
    m_animate.translate(0.0, m_pressed ? -0.001 : 0.0, 0.0);
    return m_animate.data();
}
