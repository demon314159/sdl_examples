//
// element.cpp
//

#include "element.h"
#include "look.h"
#include "gable_brick_shape.h"
#include "door_model.h"
#include "window_model.h"

Element::Element(Int3 pos, int width, int height, int orientation)
    : m_removed(false)
    , m_pos(pos)
    , m_width(width)
    , m_height(height)
    , m_orientation(orientation)
    , m_model()
{
    if (m_width > 2 || m_height > 1) {
        if (orientation == 0 || orientation == 2) {
            m_model.add(BrickShape(DIMX * (float) m_width, DIMY * (float) m_height, DIMZ, DIMB), BRICK_PAINT, 0.0);
        } else {
            m_model.add (BrickShape(DIMX, DIMY * (float) m_height, DIMZ * (float) m_width, DIMB), BRICK_PAINT, 0.0);
        }
    }
}

Element::~Element()
{
}

void Element::remove()
{
    m_removed = true;
}

void Element::unremove()
{
    m_removed = false;
}

bool Element::removed() const
{
    return m_removed;
}

Int3 Element::pos() const
{
    return m_pos;
}

Float3 Element::model_pos() const
{
    Float3 fpos = {DIMX * (float) m_pos.v1, DIMY * (float) m_pos.v2, DIMZ * (float) m_pos.v3};
    float fw = DIMX * (float) (m_width - 1);
    float fh = DIMY * (float) (m_height - 1);

    if (m_orientation == 3) {
        return {fpos.v1, fpos.v2 + fh / 2.0f, fpos.v3 + fw / 2.0f};
    } else if (m_orientation == 2) {
        return {fpos.v1 - fw / 2.0f, fpos.v2 + fh / 2.0f, fpos.v3};
    } else if (m_orientation == 1) {
        return {fpos.v1, fpos.v2 + fh / 2.0f, fpos.v3 - fw / 2.0f};
    } else {
        return {fpos.v1 + fw / 2.0f, fpos.v2 + fh / 2.0f, fpos.v3};
    }
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

//void Element::save_to_file(FILE* ffo) const
//{
//    fprintf(ffo, "Brick(%0d, %0d, %0d, %0d, %0d, %0d)\n",
//        m_pos.v1, m_pos.v2, m_pos.v3, m_width, m_height, m_orientation);
//}

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

bool Element::contains(int x, int y, int z) const
{
    if (m_orientation == 3) {
        return m_pos.v1 == x && in_range(y, m_pos.v2, m_pos.v2 + m_height - 1) && in_range(z, m_pos.v3, m_pos.v3 + m_width - 1);
    } else if (m_orientation == 2) {
        return in_range(x, m_pos.v1, m_pos.v1 - m_width + 1) && in_range(y, m_pos.v2, m_pos.v2 + m_height - 1) && m_pos.v3 == z;
    } else if (m_orientation == 1) {
        return m_pos.v1 == x && in_range(y, m_pos.v2, m_pos.v2 + m_height - 1) && in_range(z, m_pos.v3, m_pos.v3 - m_width + 1);
    } else {
        return in_range(x, m_pos.v1, m_pos.v1 + m_width - 1) && in_range(y, m_pos.v2, m_pos.v2 + m_height - 1) && m_pos.v3 == z;
    }
    return false;
}

bool Element::in_range(int v, int v1, int v2) const
{
    if (v1 > v2) {
        return v >= v2 && v <= v1;
    } else {
        return v >= v1 && v <= v2;
    }
}

CadModel Element::m_halfbrick_model(BrickShape(DIMX, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);
CadModel Element::m_brick_model_ns(BrickShape(DIMX * 2.0f, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);
CadModel Element::m_brick_model_ew(BrickShape(DIMX, DIMY, DIMZ * 2.0f, DIMB), BRICK_PAINT, 0.0);

HalfBrickElement::HalfBrickElement(Int3 pos)
    : Element(pos, 1, 1, 0)
{
}

void HalfBrickElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "HalfBrick(%0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3);
}

BrickElement::BrickElement(Int3 pos, int orientation)
    : Element(pos, 2, 1, orientation)
{
}

void BrickElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "Brick(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

DoubleBrickElement::DoubleBrickElement(Int3 pos, int orientation)
    : Element(pos, 4, 1, orientation)
{
}

void DoubleBrickElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "DoubleBrick(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* DoubleBrickElement::model() const
{
    if (m_orientation == 0 || m_orientation == 2) {
        return &m_double_brick_model_ns;
    } else {
        return &m_double_brick_model_ew;
    }
}

CadModel DoubleBrickElement::m_double_brick_model_ns(BrickShape(DIMX * 4.0f, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);
CadModel DoubleBrickElement::m_double_brick_model_ew(BrickShape(DIMX, DIMY, DIMZ * 4.0f, DIMB), BRICK_PAINT, 0.0);

TripleBrickElement::TripleBrickElement(Int3 pos, int orientation)
    : Element(pos, 6, 1, orientation)
{
}

void TripleBrickElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "TripleBrick(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* TripleBrickElement::model() const
{
    if (m_orientation == 0 || m_orientation == 2) {
        return &m_triple_brick_model_ns;
    } else {
        return &m_triple_brick_model_ew;
    }
}

CadModel TripleBrickElement::m_triple_brick_model_ns(BrickShape(DIMX * 6.0f, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);
CadModel TripleBrickElement::m_triple_brick_model_ew(BrickShape(DIMX, DIMY, DIMZ * 6.0f, DIMB), BRICK_PAINT, 0.0);

GableBrickElement::GableBrickElement(Int3 pos, int orientation)
    : Element(pos, 1, 1, orientation)
    , m_model()
{
    m_model.add(GableBrickShape(DIMX, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);
    if (orientation == 1) {
        m_model.rotate_ay(90.0);
    } else if (orientation == 2) {
        m_model.rotate_ay(180.0);
    } else if (orientation == 3) {
        m_model.rotate_ay(270.0);
    }
}

void GableBrickElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "GableBrick(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* GableBrickElement::model() const
{
    return &m_model;
}

WindowElement::WindowElement(Int3 pos, int orientation)
    : Element(pos, 2, 4, orientation)
    , m_model()
{
//    m_model.add(WindowModel(DIMX * (float) m_width, DIMY * (float) m_height, DIMZ, DIMB, 1, 2, 0.0), 0.0, 0.0, 0.0);
    m_model.add(WindowModel(DIMX * (float) m_width, DIMY * (float) m_height, DIMZ, DIMB, 2, 3, 0.0), 0.0, 0.0, 0.0);
    if (orientation == 1) {
        m_model.rotate_ay(90.0);
    } else if (orientation == 2) {
        m_model.rotate_ay(180.0);
    } else if (orientation == 3) {
        m_model.rotate_ay(270.0);
    }
}

void WindowElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "Window(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* WindowElement::model() const
{
    return &m_model;
}

DoorElement::DoorElement(Int3 pos, int orientation)
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

void DoorElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "Door(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* DoorElement::model() const
{
    return &m_model;
}
