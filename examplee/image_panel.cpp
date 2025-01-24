//
// image_panel.cpp
//

#include "image_panel.h"
#include "plane_shape.h"
#include <math.h>

ImagePanel::ImagePanel(float width, float height, const Float3& position)
    : m_width(width)
    , m_height(height)
    , m_position(position)
{
}

ImagePanel::~ImagePanel()
{
}

float ImagePanel::width() const
{
    return m_width;
}

float ImagePanel::height() const
{
    return m_height;
}

Float3 ImagePanel::position() const
{
    return m_position;
}

CadModel ImagePanel::model(float animation_id, float texture_id) const
{
    CadModel cm;
    CadModel ps(PlaneShape(m_width, m_height, texture_id), PaintCan(1.0, 1.0, 1.0), animation_id);
    ps.rotate_ax(90.0);

    cm.add(ps, m_position.v1 + m_width / 2.0, m_position.v2, m_position.v3);
    return cm;
}

