//
// push_button.cpp
//

#include "push_button.h"
#include "plane_shape.h"

PushButton::PushButton(const Float2& dimension, const Float2& position)
    : m_dimension(dimension)
    , m_position(position)
{
}

PushButton::~PushButton()
{
}

bool PushButton::mouse_hit(const Float2& mouse_selection) const
{
    if (mouse_selection.v1 < (m_position.v1 - m_dimension.v1 / 2.0f)) {
        return false;
    }
    if (mouse_selection.v1 > (m_position.v1 + m_dimension.v1 / 2.0f)) {
        return false;
    }
    if (mouse_selection.v2 < (m_position.v2 - m_dimension.v2 / 2.0f)) {
        return false;
    }
    if (mouse_selection.v2 > (m_position.v2 + m_dimension.v2 / 2.0f)) {
        return false;
    }
    return true;
}

CadModel PushButton::model(float animation_id) const
{
    CadModel cm;

    CadModel pb(PlaneShape(m_dimension.v1, m_dimension.v2), PUSH_BUTTON_COLOR, animation_id);
    cm.add(pb, m_position.v1, 0.0, -m_position.v2);
    return cm;
}

