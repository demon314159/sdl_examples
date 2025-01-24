//
// element.cpp
//

#include "element.h"
#include "look.h"
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
        case 0:
            f = bf;
            tf_flag = false;
            break;
        case 1:
            f = tf;
            tf_flag = true;
            break;
        case 2:
            f.v1 = bf.v1;
            f.v2 = bf.v2;
            f.v3 = tf.v2;
            f.v4 = tf.v1;
            tf_flag = false;
            break;
        case 3:
            f.v1 = bf.v4;
            f.v2 = bf.v3;
            f.v3 = tf.v3;
            f.v4 = tf.v4;
            tf_flag = false;
            break;
        case 4:
            f.v1 = bf.v2;
            f.v2 = bf.v3;
            f.v3 = tf.v3;
            f.v4 = tf.v2;
            tf_flag = false;
            break;
        case 5:
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

CadModel Element::m_half_brick_model(BrickShape(DIMX, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);
CadModel Element::m_brick_model_ns(BrickShape(DIMX * 2.0f, DIMY, DIMZ, DIMB), BRICK_PAINT, 0.0);
CadModel Element::m_brick_model_ew(BrickShape(DIMX, DIMY, DIMZ * 2.0f, DIMB), BRICK_PAINT, 0.0);

