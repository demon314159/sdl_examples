//
// layout_guide.cpp
//

#include "layout_guide.h"
#include "pi.h"
#include <math.h>

LayoutGuide::LayoutGuide(const Float2& p1, const Float2& p2, float item_width, int items)
    : m_p1(p1)
    , m_p2(p2)
    , m_item_width(item_width)
    , m_items(items)
{
}

Float2 LayoutGuide::position(int item) const
{
    float dx = m_p2.v1 - m_p1.v1;
    float dz = m_p2.v2 - m_p1.v2;
    float length = sqrt(dx * dx + dz * dz);
    int spaces = 2 * m_items;
    float k = (length - m_item_width * (float) m_items) / (float) spaces;
    float li = (2.0 * k + m_item_width) * (float) item - k - m_item_width / 2.0;
    Float2 pos;
    pos.v1 = dx * li / length + m_p1.v1;
    pos.v2 = dz * li / length + m_p1.v2;
    return pos;
}

float LayoutGuide::angle() const
{
    float dx = m_p2.v1 - m_p1.v1;
    float dz = m_p2.v2 - m_p1.v2;
    float angle = atan2(-dz, dx) * 180.0 / PI;
    return angle;
}

