//
// back_door_element.cpp
//

#include "back_door_element.h"
#include "door_model.h"
#include "look.h"

BackDoorElement::BackDoorElement(Int3 pos, int orientation)
    : Element(pos, 2, 6, orientation)
    , m_model()
{
    m_model.add(DoorModel(DIMX * (float) m_width, DIMY * (float) m_height, DIMZ, DIMB, 2, 1, 0.0), 0.0, 0.0, 0.0);
    if (orientation == 1) {
        m_model.rotate_ay(90.0);
    } else if (orientation == 2) {
        m_model.rotate_ay(180.0);
    } else if (orientation == 3) {
        m_model.rotate_ay(270.0);
    }
}

void BackDoorElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "BackDoor(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* BackDoorElement::model() const
{
    return &m_model;
}


