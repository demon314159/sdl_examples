//
// half_brick_element.cpp
//

#include "half_brick_element.h"

HalfBrickElement::HalfBrickElement(Int3 pos)
    : Element(pos, 1, 1, 0)
{
}

void HalfBrickElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "HalfBrick(%0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3);
}

