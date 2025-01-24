//
// flat_roof_element.cpp
//

#include "flat_roof_element.h"
#include "look.h"

FlatRoofElement::FlatRoofElement(Int3 pos, int width, int orientation)
    : Element(pos, width, 1, orientation)
    , m_model()
{
    float thickness = 1.1 * (DIMY / 2.0);
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
    Face bf; // bottom_face
    Face tf; // top_face
    tf = flat_roof_top_face(m_pos, m_width, m_orientation);
    bf = flat_roof_bottom_face(m_pos, m_width, m_orientation);
    switch (ix) {
        case 0:
            f = bf;
            break;
        case 1:
            f = tf;
            break;
        case 2:
            f.v1 = bf.v1;
            f.v2 = bf.v2;
            f.v3 = tf.v2;
            f.v4 = tf.v1;
            break;
        case 3:
            f.v1 = bf.v4;
            f.v2 = bf.v3;
            f.v3 = tf.v3;
            f.v4 = tf.v4;
            break;
        case 4:
            f.v1 = bf.v2;
            f.v2 = bf.v3;
            f.v3 = tf.v3;
            f.v4 = tf.v2;
            break;
        case 5:
            f.v1 = bf.v1;
            f.v2 = bf.v4;
            f.v3 = tf.v4;
            f.v4 = tf.v1;
            break;
        default:
            f = tf;
    }
    if (top_face != NULL) {
        *top_face = false;
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

