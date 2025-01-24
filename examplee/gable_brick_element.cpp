//
// gable_brick_eleement.cpp
//

#include "gable_brick_element.h"
#include "gable_brick_shape.h"
#include "look.h"

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
    switch (ix) {
        case 0:
            f = tf;
            tf_flag = true;
            break;
        case 1:
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
        case 2:
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
        case 3:
            if (m_orientation == 1) {
            } else {
                f.v1 = bf.v2;
                f.v2 = bf.v3;
                f.v3 = tf.v3;
                f.v4 = tf.v2;
                tf_flag = false;
            }
            break;
        case 4:
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

