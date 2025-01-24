//
// half_foundation_element.cpp
//

#include "half_foundation_element.h"
#include "look.h"

HalfFoundationElement::HalfFoundationElement(Int3 pos)
    : Element(pos, 1, 1, 0)
{
}

void HalfFoundationElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "HalfFoundation(%0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3);
}

const CadModel* HalfFoundationElement::model() const
{
    return &m_half_foundation_model;
}

CadModel HalfFoundationElement::m_half_foundation_model(BrickShape(DIMX, DIMY, DIMZ, DIMB), FOUNDATION_PAINT, 0.0);
