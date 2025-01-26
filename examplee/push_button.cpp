//
// push_button.cpp
//

#include "push_button.h"
#include "button_shape.h"
#include "ring_shape.h"
#include "look.h"
#include "pi.h"
#include <math.h>

#define MAJOR_STEPS 100
#define MINOR_STEPS 20
#define RATIO 6.0f

PushButton::PushButton(float radius, float height, const Float3& position)
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

void PushButton::press()
{
    m_pressed = true;
}

void PushButton::release()
{
    m_pressed = false;
}

bool PushButton::pressed() const
{
    return m_pressed;
}

CadModel PushButton::model(float body_animation_id, float button_animation_id, float lamp_texture_id) const
{
    float bh = m_height * 0.7f;
    float ri = m_radius * 1.15;
    float ro = m_radius * 1.3;
    CadModel cm;
    CadModel pb(ButtonShape(m_radius, m_height, m_radius / RATIO, MAJOR_STEPS, MINOR_STEPS, lamp_texture_id), PUSH_BUTTON_COLOR, button_animation_id);
    CadModel bezel(RingShape(ro, ri, bh, MAJOR_STEPS), BEVEL_COLOR, body_animation_id);
    pb.rotate_ax(90.0);
    bezel.rotate_ax(90.0);
    cm.add(pb, m_position.v1, m_position.v2, m_position.v3);
    cm.add(bezel, m_position.v1, m_position.v2, m_position.v3 + bh / 2.0);
    return cm;
}

const float* PushButton::data()
{
    m_animate.unity();
    m_animate.translate(0.0, 0.0, m_pressed ? (-m_radius / 10.0f) : 0.0);
    return m_animate.data();
}

bool PushButton::collide(const Float3& sel_pos, const Float3& top_corner) const
{
    float bpx = m_position.v1 + top_corner.v1;
    float bpy = m_position.v2 + top_corner.v2;
    float dx = sel_pos.v1 - bpx;
    float dy = sel_pos.v2 - bpy;
    float r = sqrt(dx * dx + dy * dy);
    return r <= (1.8 * m_radius);


}
