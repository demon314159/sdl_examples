//
// roof_element.cpp
//

#include "roof_element.h"
#include "roof_shape.h"
#include "look.h"

RoofElement::RoofElement(Int3 pos, int width, int orientation)
    : Element(pos, width, 1, orientation)
    , m_model()
{
    CadModel rm(RoofShape(DIMX, DIMX, DIMX, DIMB, DIMX / 20.0), ROOF_PAINT, 0.0);
    for (int i = 0; i < width; i++) {
        float hw = 0.5 * DIMX * (float) width;
        m_model.add(rm, 0.5 * DIMX - hw + DIMX * (float) i, -DIMY);
    }
    if (orientation == 1) {
        m_model.rotate_ay(90.0);
    } else if (orientation == 2) {
        m_model.rotate_ay(180.0);
    } else if (orientation == 3) {
        m_model.rotate_ay(270.0);
    }
}

void RoofElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "Roof(%0d, %0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_width, m_orientation);
}

const CadModel* RoofElement::model() const
{
    return &m_model;
}

int RoofElement::faces() const
{
    return 6;
}

Face RoofElement::face(int ix, bool* top_face) const
{
    Face f;

    float thickness = 1.5 * DIMX / 20.0;
    float underhang = DIMX / 4.0;

    float x0, x1, y0, y1, y2, y3, z0, z1;
    float bx = DIMX * (float) m_pos.v1;
    float by = DIMY * (float) m_pos.v2 - DIMY;
    float bz = DIMZ * (float) m_pos.v3;
    if (m_orientation == 3) {
        x0 = bx - 3.0 * DIMX / 4.0;
        x1 = bx + DIMX / 2.0;
        y0 = by - 3.0 * DIMY / 4.0;
        y1 = y0;
        y2 = by + DIMY / 2.0;
        y3 = y2;
        z0 = bz - 3.0 * DIMZ / 4.0;
        z1 = bz + 3.0 * DIMZ / 4.0 + DIMZ * (float) (m_width - 1);
    } else if (m_orientation == 2) {
        x0 = bx - 3.0 * DIMX / 4.0 - DIMX * (float) (m_width - 1);
        x1 = bx + 3.0 * DIMX / 4.0;
        y0 = by - 3.0 * DIMY / 4.0;
        y1 = by + DIMY / 2.0;
        y2 = y1;
        y3 = y0;
        z0 = bz - 3.0 * DIMZ / 4.0;
        z1 = bz + DIMZ / 2.0;
    } else if (m_orientation == 1) {
        x0 = bx - DIMX / 2.0;
        x1 = bx + 3.0 * DIMX / 4.0;
        y0 = by + DIMY / 2.0;
        y1 = y0;
        y2 = by - 3.0 * DIMY / 4.0;
        y3 = y2;
        z0 = bz - 3.0 * DIMZ / 4.0 - DIMZ * (float) (m_width - 1);
        z1 = bz + 3.0 * DIMZ / 4.0;
    } else {
        x0 = bx - 3.0 * DIMX / 4.0;
        x1 = bx + 3.0 * DIMX / 4.0 + DIMX * (float) (m_width - 1);
        y0 = by + DIMY / 2.0;
        y1 = by - 3.0 * DIMY / 4.0;
        y2 = y1;
        y3 = y0;
        z0 = bz - DIMZ / 2.0;
        z1 = bz + 3.0 * DIMZ / 4.0;
    }
    switch (ix) {
        case 0:
            f = {{x0, y0, z0}, {x0, y1, z1}, {x1, y2, z1}, {x1, y3, z0}};
            break;
        case 1:
            f = {{x0, y0 + thickness, z0}, {x0, y1 + thickness, z1}, {x1, y2 + thickness, z1}, {x1, y3 + thickness, z0}};
            break;
        case 2:
            f = {{x0, y0, z0}, {x0, y1, z1}, {x0, y1 + thickness, z1}, {x0, y0 + thickness, z0}};
            break;
        case 3:
            f = {{x1, y3, z0}, {x1, y2, z1}, {x1, y2 + thickness, z1}, {x1, y3 + thickness, z0}};
            break;
        case 4:
            f = {{x0, y1, z1}, {x1, y2, z1}, {x1, y2 + thickness, z1}, {x0, y1 + thickness, z1}};
            break;
        case 5:
            f = {{x0, y0, z0}, {x1, y3, z0}, {x1, y3 + thickness, z0}, {x0, y0 + thickness, z0}};
            break;
        default:
            f = {{x0, y0 + thickness, z0}, {x0, y1 + thickness, z1}, {x1, y2 + thickness, z1}, {x1, y3 + thickness, z0}};
    }
    if (top_face != NULL) {
        *top_face = false;
    }
    return f;
}

