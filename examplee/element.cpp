//
// element.cpp
//

#include "element.h"
#include "look.h"
#include "gable_brick_shape.h"
#include "door_model.h"
#include "window_model.h"
#include "corner_window_model.h"
#include <algorithm>

Element::Element(Int3 pos, int width, int height, int orientation, bool corner_flag)
    : m_removed(false)
    , m_pos(pos)
    , m_width(width)
    , m_height(height)
    , m_orientation(orientation)
    , m_corner_flag(corner_flag)
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

bool Element::corner_flag() const
{
    return m_corner_flag;
}

const CadModel* Element::model() const
{
    if (m_width == 1 && m_height == 1) {
        return &m_half_brick_model;
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
    if (partial_contains(m_pos, m_width, m_height, m_orientation, x, y, z)) {
        return true;
    }
    if (m_corner_flag) {
        int t_orientation;
        Int3 t_pos;
        if (m_orientation == 3) {
            t_orientation = 0;
            t_pos = {m_pos.v1, m_pos.v2, m_pos.v3 + m_width - 1};
        } else if (m_orientation == 2) {
            t_orientation = 3;
            t_pos = {m_pos.v1 - m_width + 1, m_pos.v2, m_pos.v3};
        } else if (m_orientation == 1) {
            t_orientation = 2;
            t_pos = {m_pos.v1, m_pos.v2, m_pos.v3 - m_width + 1};
        } else {
            t_orientation = 1;
            t_pos = {m_pos.v1 + m_width - 1, m_pos.v2, m_pos.v3};
        }
        if (partial_contains(t_pos, m_width, m_height, t_orientation, x, y, z)) {
            return true;
        }
    }
    return false;
}

void Element::update_integer_bounding_box(IntegerBoundingBox& bb)
{
    // Do first unit at m_pos
    Int3 pos = m_pos;
    bb.vmin.v1 = std::min(bb.vmin.v1, pos.v1);
    bb.vmin.v2 = std::min(bb.vmin.v2, pos.v2);
    bb.vmin.v3 = std::min(bb.vmin.v3, pos.v3);
    bb.vmax.v1 = std::max(bb.vmax.v1, pos.v1);
    bb.vmax.v2 = std::max(bb.vmax.v2, pos.v2);
    bb.vmax.v3 = std::max(bb.vmax.v3, pos.v3);
    if (m_height > 0) {
        // Do top unit
        pos.v2 += (m_height - 1);
        bb.vmin.v2 = std::min(bb.vmin.v2, pos.v2);
        bb.vmax.v2 = std::max(bb.vmax.v2, pos.v2);
    }
    if (m_width > 0) {
        // Do last unit based on orientation
        if (m_orientation == 3) {
            pos.v3 += (m_width - 1);
        } else if (m_orientation == 2) {
            pos.v1 -= (m_width - 1);
        } else if (m_orientation == 1) {
            pos.v3 -= (m_width - 1);
        } else {
            pos.v1 += (m_width - 1);
        }
        bb.vmin.v1 = std::min(bb.vmin.v1, pos.v1);
        bb.vmin.v3 = std::min(bb.vmin.v3, pos.v3);
        bb.vmax.v1 = std::max(bb.vmax.v1, pos.v1);
        bb.vmax.v3 = std::max(bb.vmax.v3, pos.v3);
        if (m_corner_flag) {
            int t_orientation;
            if (m_orientation == 3) {
                t_orientation = 0;
                pos = {m_pos.v1, m_pos.v2, m_pos.v3 + m_width - 1};
            } else if (m_orientation == 2) {
                t_orientation = 3;
                pos = {m_pos.v1 - m_width + 1, m_pos.v2, m_pos.v3};
            } else if (m_orientation == 1) {
                t_orientation = 2;
                pos = {m_pos.v1, m_pos.v2, m_pos.v3 - m_width + 1};
            } else {
                t_orientation = 1;
                pos = {m_pos.v1 + m_width - 1, m_pos.v2, m_pos.v3};
            }
            // Do last unit based on orientation
            if (t_orientation == 3) {
                pos.v3 += (m_width - 1);
            } else if (t_orientation == 2) {
                pos.v1 -= (m_width - 1);
            } else if (t_orientation == 1) {
                pos.v3 -= (m_width - 1);
            } else {
                pos.v1 += (m_width - 1);
            }
            bb.vmin.v1 = std::min(bb.vmin.v1, pos.v1);
            bb.vmin.v3 = std::min(bb.vmin.v3, pos.v3);
            bb.vmax.v1 = std::max(bb.vmax.v1, pos.v1);
            bb.vmax.v3 = std::max(bb.vmax.v3, pos.v3);
        }
    }
}

bool Element::in_range(int v, int v1, int v2) const
{
    if (v1 > v2) {
        return v >= v2 && v <= v1;
    } else {
        return v >= v1 && v <= v2;
    }
}

bool Element::partial_contains(Int3 pos, int width, int height, int orientation, int x, int y, int z) const
{
    bool res;
    if (orientation == 3) {
        return pos.v1 == x && in_range(y, pos.v2, pos.v2 + height - 1) && in_range(z, pos.v3, pos.v3 + width - 1);
    } else if (orientation == 2) {
        return in_range(x, pos.v1, pos.v1 - width + 1) && in_range(y, pos.v2, pos.v2 + height - 1) && pos.v3 == z;
    } else if (orientation == 1) {
        return pos.v1 == x && in_range(y, pos.v2, pos.v2 + height - 1) && in_range(z, pos.v3, pos.v3 - width + 1);
    } else {
        return in_range(x, pos.v1, pos.v1 + width - 1) && in_range(y, pos.v2, pos.v2 + height - 1) && pos.v3 == z;
    }
}

//***  HalfBrickElement ***

CadModel Element::m_half_brick_model(BrickShape(DIMX, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);

HalfBrickElement::HalfBrickElement(Int3 pos)
    : Element(pos, 1, 1, 0)
{
}

void HalfBrickElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "HalfBrick(%0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3);
}

//***  BrickElement ***

CadModel Element::m_brick_model_ns(BrickShape(DIMX * 2.0f, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);
CadModel Element::m_brick_model_ew(BrickShape(DIMX, DIMY, DIMZ * 2.0f, DIMB), BRICK_PAINT, 0.0);

BrickElement::BrickElement(Int3 pos, int orientation)
    : Element(pos, 2, 1, orientation)
{
}

void BrickElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "Brick(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

//***  HalfFoundationElement ***

CadModel HalfFoundationElement::m_half_foundation_model(BrickShape(DIMX, DIMY, DIMZ, DIMB), FOUNDATION_PAINT, 0.0);

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

//***  FoundationElement ***

CadModel FoundationElement::m_foundation_model_ns(BrickShape(DIMX * 2.0f, DIMY, DIMZ, DIMB), FOUNDATION_PAINT, 0.0);
CadModel FoundationElement::m_foundation_model_ew(BrickShape(DIMX, DIMY, DIMZ * 2.0f, DIMB), FOUNDATION_PAINT, 0.0);

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

//***  DoubleFoundationElement ***

CadModel DoubleFoundationElement::m_double_foundation_model_ns(BrickShape(DIMX * 4.0f, DIMY, DIMZ, DIMB), FOUNDATION_PAINT, 0.0);
CadModel DoubleFoundationElement::m_double_foundation_model_ew(BrickShape(DIMX, DIMY, DIMZ * 4.0f, DIMB), FOUNDATION_PAINT, 0.0);

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

//***  DoubleFoundationElement ***

CadModel TripleFoundationElement::m_triple_foundation_model_ns(BrickShape(DIMX * 6.0f, DIMY, DIMZ, DIMB), FOUNDATION_PAINT, 0.0);
CadModel TripleFoundationElement::m_triple_foundation_model_ew(BrickShape(DIMX, DIMY, DIMZ * 6.0f, DIMB), FOUNDATION_PAINT, 0.0);

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

//***  GableBrickElement ***

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

//***  WindowElement ***

WindowElement::WindowElement(Int3 pos, int orientation)
    : Element(pos, 2, 4, orientation)
    , m_model()
{
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

//***  CornerWindowElement ***

CornerWindowElement::CornerWindowElement(Int3 pos, int orientation)
    : Element(pos, 5, 4, orientation, true)
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

//***  FrontDoorElement ***

FrontDoorElement::FrontDoorElement(Int3 pos, int orientation)
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

void FrontDoorElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "FrontDoor(%0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_orientation);
}

const CadModel* FrontDoorElement::model() const
{
    return &m_model;
}

//***  BackDoorElement ***

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



