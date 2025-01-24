//
// front_door_element.cpp
//

#include "front_door_element.h"
#include "front_door_model.h"
#include "look.h"

FrontDoorElement::FrontDoorElement(Int3 pos, int orientation)
    : Element(pos, 2, 6, orientation)
    , m_model()
{
    m_model.add(FrontDoorModel(DIMX * (float) m_width, DIMY * (float) m_height, DIMZ, DIMB, 2, 4, 0.0), 0.0, 0.0, 0.0);
    if (orientation == 1) {
        m_model.rotate_ay(90.0);
    } else if (orientation == 2) {
        m_model.rotate_ay(180.0);
    } else if (orientation == 3) {
        m_model.rotate_ay(270.0);
    }
}

void FrontDoorElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "FrontDoor(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* FrontDoorElement::model() const
{
    return &m_model;
}

