//
// triple_foundation_element.cpp
//

#include "triple_foundation_element.h"
#include "look.h"

TripleFoundationElement::TripleFoundationElement(Int3 pos, int orientation)
    : Element(pos, 6, 1, orientation)
{
}

void TripleFoundationElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "TripleFoundation(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* TripleFoundationElement::model() const
{
    if (m_orientation == 0 || m_orientation == 2) {
        return &m_triple_foundation_model_ns;
    } else {
        return &m_triple_foundation_model_ew;
    }
}

CadModel TripleFoundationElement::m_triple_foundation_model_ns(BrickShape(DIMX * 6.0f, DIMY, DIMZ, DIMB), FOUNDATION_PAINT, 0.0);
CadModel TripleFoundationElement::m_triple_foundation_model_ew(BrickShape(DIMX, DIMY, DIMZ * 6.0f, DIMB), FOUNDATION_PAINT, 0.0);

