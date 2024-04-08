//
// layout_guide.h
//

#ifndef _LAYOUT_GUIDE_H_
#define _LAYOUT_GUIDE_H_

#include "float3.h"

class LayoutGuide
{
public:
    LayoutGuide(const Float2& p1, const Float2& p2, float item_width, int items);

    Float2 position(int item) const;
    float angle() const;

protected:
    Float2 m_p1;
    Float2 m_p2;
    float m_item_width;
    int m_items;
};

#endif // _LAYOUT_GUIDE_H_

