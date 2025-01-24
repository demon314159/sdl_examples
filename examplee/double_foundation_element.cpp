//
// double_foundation_element.cpp
//

#include "double_foundation_element.h"
#include "look.h"

DoubleFoundationElement::DoubleFoundationElement(Int3 pos, int orientation)
    : Element(pos, 4, 1, orientation)
{
}

void DoubleFoundationElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "DoubleFoundation(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* DoubleFoundationElement::model() const
{
    if (m_orientation == 0 || m_orientation == 2) {
        return &m_double_foundation_model_ns;
    } else {
        return &m_double_foundation_model_ew;
    }
}

CadModel DoubleFoundationElement::m_double_foundation_model_ns(BrickShape(DIMX * 4.0f, DIMY, DIMZ, DIMB), FOUNDATION_PAINT, 0.0);
CadModel DoubleFoundationElement::m_double_foundation_model_ew(BrickShape(DIMX, DIMY, DIMZ * 4.0f, DIMB), FOUNDATION_PAINT, 0.0);

