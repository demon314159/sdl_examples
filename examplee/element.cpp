//
// element.cpp
//

#include "element.h"
#include "look.h"

#define DIMX  0.1f
#define DIMY  (DIMX * 2.0f / 3.0f)
#define DIMZ  DIMX
#define DIMB  (DIMX / 40.0f)

Element::Element(Int3 pos, int width, int height, int orientation)
    : m_pos(pos)
    , m_width(width)
    , m_height(height)
    , m_orientation(orientation)
    , m_model()
{
    if (m_width > 2 || m_height > 1) {
        if (orientation == 0 || orientation == 2) {
            m_model = CadModel(BrickShape(DIMX * (float) m_width, DIMY * (float) m_height, DIMZ, DIMB), BRICK_PAINT, 0.0);
        } else {
            m_model = CadModel(BrickShape(DIMX, DIMY * (float) m_height, DIMZ * (float) m_width, DIMB), BRICK_PAINT, 0.0);
        }
    }
}

Element::~Element()
{
}

Int3 Element::pos() const
{
    return m_pos;
}

int Element::width() const
{
    return m_width;
}

int Element::height() const
{
    return m_height;
}

int Element::orientation() const
{
    return m_orientation;
}

void Element::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "Brick(%0d, %0d, %0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_width, m_height, m_orientation);
}

const CadModel* Element::model() const
{
    if (m_width == 1 && m_height == 1) {
        return &m_halfbrick_model;
    } else if (m_width == 2 && m_height == 1) {
        if (m_orientation == 0 || m_orientation == 2) {
            return &m_brick_model_ns;
        } else {
            return &m_brick_model_ew;
        }
    }
    return &m_model;
}

CadModel Element::m_halfbrick_model(BrickShape(DIMX, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);
CadModel Element::m_brick_model_ns(BrickShape(DIMX * 2.0f, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);
CadModel Element::m_brick_model_ew(BrickShape(DIMX, DIMY, DIMZ * 2.0f, DIMB), BRICK_PAINT, 0.0);

