//
// corner_window_element.cpp
//

#include "corner_window_element.h"
#include "corner_window_model.h"
#include "look.h"

CornerWindowElement::CornerWindowElement(Int3 pos, int orientation)
    : Element(pos, 5, 4, orientation)
    , m_model()
{
    m_model.add(CornerWindowModel(DIMX * (float) m_width, DIMY * (float) m_height, DIMZ, DIMB, 7, 3, 0.0), 0.0, 0.0, 0.0);
    if (orientation == 1) {
        m_model.rotate_ay(90.0);
    } else if (orientation == 2) {
        m_model.rotate_ay(180.0);
    } else if (orientation == 3) {
        m_model.rotate_ay(270.0);
    }
}

void CornerWindowElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "CornerWindow(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* CornerWindowElement::model() const
{
    return &m_model;
}

bool CornerWindowElement::corner_flag() const
{
    return true;
}

int CornerWindowElement::faces() const
{
    return 12;
}

Face CornerWindowElement::face(int ix, bool* top_face) const
{
    if (ix < 6) {
        return general_face(m_pos, m_width, m_height, m_orientation, ix, top_face);
    } else {
        Int3 pos = m_pos;
        int orientation;
        if (m_orientation == 3) {
            pos.v3 += (m_width - 1);
            orientation = 0;
        } else if (m_orientation == 2) {
            pos.v1 -= (m_width - 1);
            orientation = 3;
        } else if (m_orientation == 1) {
            pos.v3 -= (m_width - 1);
            orientation = 2;
        } else {
            pos.v1 += (m_width - 1);
            orientation = 1;
        }
        return general_face(pos, m_width, m_height, orientation, ix - 6, top_face);
    }
}

