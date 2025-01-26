//
// image_button.cpp
//

#include "image_button.h"
#include "pi.h"
#include <math.h>

ImageButton::ImageButton(const ImagePanel* panel, float image_dimx, float image_dimy,
                         const Float2& region_pos, const Float2& region_size)
    : m_image_dimx(image_dimx)
    , m_image_dimy(image_dimy)
    , m_region_pos(region_pos)
    , m_region_size(region_size)
    , m_panel(panel)
{
}

ImageButton::~ImageButton()
{
}

bool ImageButton::collide(const Float3& sel_pos, const Float3& top_corner) const
{
    float bpx = m_panel->position().v1 + top_corner.v1;
    float bpy = m_panel->position().v2 + top_corner.v2 + m_panel->height() / 2.0;
    float rx = bpx + m_panel->width() * m_region_pos.v1 / m_image_dimx;
    float ry = bpy - m_panel->height() * m_region_pos.v2 / m_image_dimy;
    float dx = m_panel->width() * m_region_size.v1 / m_image_dimx;
    float dy = m_panel->height() * m_region_size.v2 / m_image_dimy;
    if (sel_pos.v1 < rx)
        return false;
    if (sel_pos.v1 > (rx + dx))
        return false;
    if (sel_pos.v2 > ry)
        return false;
    if (sel_pos.v2 < (ry - dy))
        return false;
    return true;
}
