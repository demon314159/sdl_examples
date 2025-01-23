//
// element.cpp
//

#include "element.h"
#include "look.h"
#include "gable_brick_shape.h"
#include "door_model.h"
#include "front_door_model.h"
#include "window_model.h"
#include "corner_window_model.h"
#include "roof_shape.h"
#include <algorithm>

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

bool Element::corner_flag() const
{
    return false;
}

bool Element::gable_flag() const
{
    return false;
}

bool Element::roof_flag() const
{
    return false;
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
    if (m_removed) {
        return false;
    }
    if (partial_contains(m_pos, m_width, m_height, m_orientation, x, y, z)) {
        return true;
    }
    if (corner_flag()) {
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
        if (corner_flag()) {
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

int Element::faces() const
{
    return 6;
}

Face Element::face(int ix, bool* top_face) const
{
    return general_face(m_pos, m_width, m_height, m_orientation, ix, top_face);
}

Face Element::general_top_face(Int3 pos, int width, int height, int orientation) const
{
    Face tf; // top_face
    if (orientation == 3) {
        tf.v1 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
        tf.v2 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 - DIMZ / 2.0f + DIMZ * (float) width};
        tf.v3 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 - DIMZ / 2.0f + DIMZ * (float) width};
        tf.v4 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
    } else if (orientation == 2) {
        tf.v1 = {DIMX * (float) pos.v1 + DIMX / 2.0f - DIMX * (float) width, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
        tf.v2 = {DIMX * (float) pos.v1 + DIMX / 2.0f - DIMX * (float) width, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        tf.v3 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        tf.v4 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
    } else if (orientation == 1) {
        tf.v1 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 + DIMZ / 2.0f - DIMZ * (float) width};
        tf.v2 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        tf.v3 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        tf.v4 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 + DIMZ / 2.0f - DIMZ * (float) width};
    } else {
        tf.v1 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
        tf.v2 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        tf.v3 = {DIMX * (float) pos.v1 - DIMX / 2.0f + DIMX * (float) width, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        tf.v4 = {DIMX * (float) pos.v1 - DIMX / 2.0f + DIMX * (float) width, DIMY * (float) pos.v2 - DIMY / 2.0f + DIMY * (float) height, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
    }
    return tf;
}

Face Element::general_bottom_face(Int3 pos, int width, int height, int orientation) const
{
    Face bf; // bottom_face
    if (orientation == 3) {
        bf.v1 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
        bf.v2 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - DIMZ / 2.0f + DIMZ * (float) width};
        bf.v3 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - DIMZ / 2.0f + DIMZ * (float) width};
        bf.v4 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
    } else if (orientation == 2) {
        bf.v1 = {DIMX * (float) pos.v1 + DIMX / 2.0f - DIMX * (float) width, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
        bf.v2 = {DIMX * (float) pos.v1 + DIMX / 2.0f - DIMX * (float) width, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        bf.v3 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        bf.v4 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
    } else if (orientation == 1) {
        bf.v1 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + DIMZ / 2.0f - DIMZ * (float) width};
        bf.v2 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        bf.v3 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        bf.v4 = {DIMX * (float) pos.v1 + DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + DIMZ / 2.0f - DIMZ * (float) width};
    } else {
        bf.v1 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
        bf.v2 = {DIMX * (float) pos.v1 - DIMX / 2.0f, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        bf.v3 = {DIMX * (float) pos.v1 - DIMX / 2.0f + DIMX * (float) width, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + DIMZ / 2.0f};
        bf.v4 = {DIMX * (float) pos.v1 - DIMX / 2.0f + DIMX * (float) width, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - DIMZ / 2.0f};
    }
    return bf;
}

Face Element::general_face(Int3 pos, int width, int height, int orientation, int ix, bool* top_face) const
{
    Face f;
    bool tf_flag;
    Face bf; // bottom_face
    Face tf; // top_face
    tf = general_top_face(pos, width, height, orientation);
    bf = general_bottom_face(pos, width, height, orientation);
    switch (ix) {
        case BOTTOM_FACE:
            f = bf;
            tf_flag = false;
            break;
        case TOP_FACE:
            f = tf;
            tf_flag = true;
            break;
        case LEFT_FACE:
            f.v1 = bf.v1;
            f.v2 = bf.v2;
            f.v3 = tf.v2;
            f.v4 = tf.v1;
            tf_flag = false;
            break;
        case RIGHT_FACE:
            f.v1 = bf.v4;
            f.v2 = bf.v3;
            f.v3 = tf.v3;
            f.v4 = tf.v4;
            tf_flag = false;
            break;
        case FRONT_FACE:
            f.v1 = bf.v2;
            f.v2 = bf.v3;
            f.v3 = tf.v3;
            f.v4 = tf.v2;
            tf_flag = false;
            break;
        case BACK_FACE:
            f.v1 = bf.v1;
            f.v2 = bf.v4;
            f.v3 = tf.v4;
            f.v4 = tf.v1;
            tf_flag = false;
            break;
        default:
            f = tf;
            tf_flag = true;
    }
    if (top_face != NULL) {
        *top_face = tf_flag;
    }
    return f;
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

bool GableBrickElement::gable_flag() const
{
    return true;
}

int GableBrickElement::faces() const
{
    return 5;
}

Face GableBrickElement::face(int ix, bool* top_face) const
{
    Face f;
    bool tf_flag;
    Face bf; // bottom_face
    Face tf; // top_face
    tf = general_top_face(m_pos, m_width, m_height, m_orientation);
    bf = general_bottom_face(m_pos, m_width, m_height, m_orientation);
    if (m_orientation == 3) {
        tf.v4 = bf.v4;
        tf.v1 = bf.v1;
    } else if (m_orientation == 2) {
        tf.v3 = bf.v3;
        tf.v4 = bf.v4;
    } else if (m_orientation == 1) {
        tf.v2 = bf.v2;
        tf.v3 = bf.v3;
    } else {
        tf.v1 = bf.v1;
        tf.v2 = bf.v2;
    }
    switch (ix + 1) {

//  This can never be chosen and it is returned by
//  the forbiden face of each orentation
//        case BOTTOM_FACE:
//            f = bf;
//            tf_flag = false;
//            break;

        case TOP_FACE:
            f = tf;
            tf_flag = true;
            break;
        case LEFT_FACE:
            if (m_orientation == 0) {
                f = bf;
                tf_flag = false;
            } else {
                f.v1 = bf.v1;
                f.v2 = bf.v2;
                f.v3 = tf.v2;
                f.v4 = tf.v1;
                tf_flag = false;
            }
            break;
        case RIGHT_FACE:
            if (m_orientation == 2) {
                f = bf;
                tf_flag = false;
            } else {
                f.v1 = bf.v4;
                f.v2 = bf.v3;
                f.v3 = tf.v3;
                f.v4 = tf.v4;
                tf_flag = false;
            }
            break;
        case FRONT_FACE:
            if (m_orientation == 1) {
            } else {
                f.v1 = bf.v2;
                f.v2 = bf.v3;
                f.v3 = tf.v3;
                f.v4 = tf.v2;
                tf_flag = false;
            }
            break;
        case BACK_FACE:
            if (m_orientation == 3) {
                f = bf;
                tf_flag = false;
            } else {
                f.v1 = bf.v1;
                f.v2 = bf.v4;
                f.v3 = tf.v4;
                f.v4 = tf.v1;
                tf_flag = false;
            }
            break;
        default:
            f = tf;
            tf_flag = true;
    }
    if (top_face != NULL) {
        *top_face = tf_flag;
    }
    return f;
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

//***  TripleFoundationElement ***

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

//***  RoofElement ***

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

bool RoofElement::roof_flag() const
{
    return true;
}

int RoofElement::faces() const
{
    return 6;
}

Face RoofElement::face(int ix, bool* top_face) const
{
    Face f;
    bool tf_flag;

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
        case BOTTOM_FACE:
            f = {{x0, y0, z0}, {x0, y1, z1}, {x1, y2, z1}, {x1, y3, z0}};
            tf_flag = false;
            break;
        case TOP_FACE:
            f = {{x0, y0 + thickness, z0}, {x0, y1 + thickness, z1}, {x1, y2 + thickness, z1}, {x1, y3 + thickness, z0}};
            tf_flag = true;
            break;
        case LEFT_FACE:
            f = {{x0, y0, z0}, {x0, y1, z1}, {x0, y1 + thickness, z1}, {x0, y0 + thickness, z0}};
            tf_flag = false;
            break;
        case RIGHT_FACE:
            f = {{x1, y3, z0}, {x1, y2, z1}, {x1, y2 + thickness, z1}, {x1, y3 + thickness, z0}};
            tf_flag = false;
            break;
        case FRONT_FACE:
            f = {{x0, y1, z1}, {x1, y2, z1}, {x1, y2 + thickness, z1}, {x0, y1 + thickness, z1}};
            tf_flag = false;
            break;
        case BACK_FACE:
            f = {{x0, y0, z0}, {x1, y3, z0}, {x1, y3 + thickness, z0}, {x0, y0 + thickness, z0}};
            tf_flag = false;
            break;
        default:
            f = {{x0, y0 + thickness, z0}, {x0, y1 + thickness, z1}, {x1, y2 + thickness, z1}, {x1, y3 + thickness, z0}};
            tf_flag = true;
    }
    if (top_face != NULL) {
        *top_face = tf_flag;
    }
    return f;
}
//***  FlatRoofElement ***

FlatRoofElement::FlatRoofElement(Int3 pos, int width, int orientation)
    : Element(pos, width, 1, orientation)
    , m_model()
{

//    CadModel rm(FlatRoofShape(DIMX, DIMX, DIMX, DIMB, DIMX / 20.0), ROOF_PAINT, 0.0);
//    for (int i = 0; i < width; i++) {
//        float hw = 0.5 * DIMX * (float) width;
//        m_model.add(rm, 0.5 * DIMX - hw + DIMX * (float) i);
//    }

    float thickness = 1.1 * (DIMY / 2.0);
//    float thickness = 2.0 * DIMX / 20.0 + DIMX / 40.0;

    CadModel rm(BrickShape(DIMX * 1.5, thickness, DIMX * 1.5, DIMB), ROOF_PAINT, 0.0);
    for (int i = 0; i < width; i++) {
        float hw = 0.5 * DIMX * (float) width;
        m_model.add(rm, 0.5 * DIMX - hw + DIMX * (float) i, -(DIMY - thickness) / 2.0);
    }
    if (orientation == 1) {
        m_model.rotate_ay(90.0);
    } else if (orientation == 2) {
        m_model.rotate_ay(180.0);
    } else if (orientation == 3) {
        m_model.rotate_ay(270.0);
    }
}

void FlatRoofElement::save_to_file(FILE* ffo) const
{
    fprintf(ffo, "FlatRoof(%0d, %0d, %0d, %0d, %0d)\n",
        m_pos.v1, m_pos.v2, m_pos.v3, m_width, m_orientation);
}

const CadModel* FlatRoofElement::model() const
{
    return &m_model;
}

int FlatRoofElement::faces() const
{
    return 6;
}

Face FlatRoofElement::face(int ix, bool* top_face) const
{
    Face f;
    bool tf_flag;
    Face bf; // bottom_face
    Face tf; // top_face
    tf = flat_roof_top_face(m_pos, m_width, m_orientation);
    bf = flat_roof_bottom_face(m_pos, m_width, m_orientation);
    switch (ix) {
        case BOTTOM_FACE:
            f = bf;
            tf_flag = false;
            break;
        case TOP_FACE:
            f = tf;
            tf_flag = true;
            break;
        case LEFT_FACE:
            f.v1 = bf.v1;
            f.v2 = bf.v2;
            f.v3 = tf.v2;
            f.v4 = tf.v1;
            tf_flag = false;
            break;
        case RIGHT_FACE:
            f.v1 = bf.v4;
            f.v2 = bf.v3;
            f.v3 = tf.v3;
            f.v4 = tf.v4;
            tf_flag = false;
            break;
        case FRONT_FACE:
            f.v1 = bf.v2;
            f.v2 = bf.v3;
            f.v3 = tf.v3;
            f.v4 = tf.v2;
            tf_flag = false;
            break;
        case BACK_FACE:
            f.v1 = bf.v1;
            f.v2 = bf.v4;
            f.v3 = tf.v4;
            f.v4 = tf.v1;
            tf_flag = false;
            break;
        default:
            f = tf;
            tf_flag = true;
    }
    if (top_face != NULL) {
        *top_face = tf_flag;
    }
    return f;
}

Face FlatRoofElement::flat_roof_top_face(Int3 pos, int width, int orientation) const
{
    float thickness = 1.1 * (DIMY / 2.0);
    Face tf; // top_face
    float short_x = 3.0 * DIMX / 4.0;
    float long_x = DIMX * (float) (m_width - 1) + 3.0 * DIMX / 4.0;
    if (orientation == 3) {
        tf.v1 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 - short_x};
        tf.v2 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 + long_x};
        tf.v3 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 + long_x};
        tf.v4 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 - short_x};
    } else if (orientation == 2) {
        tf.v1 = {DIMX * (float) pos.v1 - long_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 - short_x};
        tf.v2 = {DIMX * (float) pos.v1 - long_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 + short_x};
        tf.v3 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 + short_x};
        tf.v4 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 - short_x};
    } else if (orientation == 1) {
        tf.v1 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 - long_x};
        tf.v2 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 + short_x};
        tf.v3 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 + short_x};
        tf.v4 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 - long_x};
    } else {
        tf.v1 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 - short_x};
        tf.v2 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 + short_x};
        tf.v3 = {DIMX * (float) pos.v1 + long_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 + short_x};
        tf.v4 = {DIMX * (float) pos.v1 + long_x, DIMY * (float) pos.v2 - DIMY / 2.0f + thickness, DIMZ * (float) pos.v3 - short_x};
    }
    return tf;
}

Face FlatRoofElement::flat_roof_bottom_face(Int3 pos, int width, int orientation) const
{
    float thickness = 1.1 * (DIMY / 2.0);
    Face bf; // bottom_face
    float short_x = 3.0 * DIMX / 4.0;
    float long_x = DIMX * (float) (m_width - 1) + 3.0 * DIMX / 4.0;
    if (orientation == 3) {
        bf.v1 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - short_x};
        bf.v2 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + long_x};
        bf.v3 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + long_x};
        bf.v4 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - short_x};
    } else if (orientation == 2) {
        bf.v1 = {DIMX * (float) pos.v1 - long_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - short_x};
        bf.v2 = {DIMX * (float) pos.v1 - long_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + short_x};
        bf.v3 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + short_x};
        bf.v4 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - short_x};
    } else if (orientation == 1) {
        bf.v1 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - long_x};
        bf.v2 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + short_x};
        bf.v3 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + short_x};
        bf.v4 = {DIMX * (float) pos.v1 + short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - long_x};
    } else {
        bf.v1 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - short_x};
        bf.v2 = {DIMX * (float) pos.v1 - short_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + short_x};
        bf.v3 = {DIMX * (float) pos.v1 + long_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 + short_x};
        bf.v4 = {DIMX * (float) pos.v1 + long_x, DIMY * (float) pos.v2 - DIMY / 2.0f, DIMZ * (float) pos.v3 - short_x};
    }
    return bf;
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

//***  FrontDoorElement ***

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



