//
// foundation_element.cpp
//

#include "foundation_element.h"
#include "look.h"

FoundationElement::FoundationElement(Int3 pos, int orientation)
    : Element(pos, 2, 1, orientation)
{
}

void FoundationElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "Foundation(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* FoundationElement::model() const
{
    if (m_orientation == 0 || m_orientation == 2) {
        return &m_foundation_model_ns;
    } else {
        return &m_foundation_model_ew;
    }
}

CadModel FoundationElement::m_foundation_model_ns(BrickShape(DIMX * 2.0f, DIMY, DIMZ, DIMB), FOUNDATION_PAINT, 0.0);
CadModel FoundationElement::m_foundation_model_ew(BrickShape(DIMX, DIMY, DIMZ * 2.0f, DIMB), FOUNDATION_PAINT, 0.0);

