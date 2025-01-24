//
// brick_element.cpp
//

#include "brick_element.h"

BrickElement::BrickElement(Int3 pos, int orientation)
    : Element(pos, 2, 1, orientation)
{
}

void BrickElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "Brick(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

