//
// message_panel.cpp
//

#include "message_panel.h"
#include "plane_shape.h"
#include <math.h>

MessagePanel::MessagePanel(float width, float height, const Float2& position)
    : m_width(width)
    , m_height(height)
    , m_position(position)
    , m_visible(false)
    , m_animate(0.0)
{
}

MessagePanel::~MessagePanel()
{
}

void MessagePanel::set_visible(bool v)
{
    m_visible = v;
}

CadModel MessagePanel::model(float texture_id) const
{
    CadModel cm;
    CadModel ps(PlaneShape(m_width, m_height, texture_id, {0.0, 0.0}, {1.0, 0.5}), PaintCan(1.0, 1.0, 1.0), 99.0);

    cm.add(ps, m_position.v1, 0.0, -m_position.v2);
    return cm;
}

const float* MessagePanel::data()
{

    m_animate = m_visible ? 0.0 : 0.5;
    return &m_animate;
}
