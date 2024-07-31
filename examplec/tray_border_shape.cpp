//
// tray_border_shape.cpp
//

#include "tray_border_shape.h"
#include "math.h"

TrayBorderShape::TrayBorderShape(float pitch, float width, float height, bool upper, bool lower, bool left, bool right)
    : m_pitch(pitch)
    , m_width(width)
    , m_height(height)
    , m_upper(upper)
    , m_lower(lower)
    , m_left(left)
    , m_right(right)
    , m_size_known(false)
    , m_facet_count(0)
    , m_facet(NULL)
{
    define_shape();
    m_size_known = true;
    if (m_facet_count > 0) {
        m_facet = new Facet[m_facet_count];
        m_facet_count = 0;
        define_shape();
    }
}

TrayBorderShape::~TrayBorderShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int TrayBorderShape::facets() const
{
    return m_facet_count;
}

Facet TrayBorderShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void TrayBorderShape::define_shape()
{
    float border = (m_pitch - m_width) / 2.0;
    float h = m_height / 2.0;
    float a1 = -m_pitch / 2.0;
    float a2 = -m_width / 2.0;
    float a3 = m_width / 2.0;
    float a4 = m_pitch / 2.0;

    // top
    if (m_upper) {
        add_face({a1 - border, h, a1 - border}, {a1 - border, h, a2}, {a4 + border, h, a2}, {a4 + border, h, a1 - border}, false);
        add_face({a1 - border, -h, a1 - border}, {a1 - border, -h, a2}, {a4 + border, -h, a2}, {a4 + border, -h, a1 - border}, true);
        add_face({a1 - border, h, a1 - border}, {a1 - border, -h, a1 - border}, {a4 + border, -h, a1 - border}, {a4 + border, h, a1 - border}, true);
    } else {
        add_face({a1, h, a1}, {a1, h, a2}, {a4, h, a2}, {a4, h, a1}, false);
        add_face({a1, -h, a1}, {a1, -h, a2}, {a4, -h, a2}, {a4, -h, a1}, true);
    }
    // bottom
    if (m_lower) {
        add_face({a1 - border, h, a4 + border}, {a1 - border, h, a3}, {a4 + border, h, a3}, {a4 + border, h, a4 + border}, true);
        add_face({a1 - border, -h, a4 + border}, {a1 - border, -h, a3}, {a4 + border, -h, a3}, {a4 + border, -h, a4 + border}, false);
        add_face({a1 - border, h, a4 + border}, {a1 - border, -h, a4 + border}, {a4 + border, -h, a4 + border}, {a4 + border, h, a4 + border}, false);
    } else {
        add_face({a1, h, a4}, {a1, h, a3}, {a4, h, a3}, {a4, h, a4}, true);
        add_face({a1, -h, a4}, {a1, -h, a3}, {a4, -h, a3}, {a4, -h, a4}, false);
    }
    // left
    if (m_left) {
        add_face({a1 - border, h, a1 - border}, {a2, h, a1 - border}, {a2, h, a4 + border}, {a1 - border, h, a4 + border}, true);
        add_face({a1 - border, -h, a1 - border}, {a2, -h, a1 - border}, {a2, -h, a4 + border}, {a1 - border, -h, a4 + border}, false);
        add_face({a1 - border, h, a1 - border}, {a1 - border, -h, a1 - border}, {a1 - border, -h, a4 + border}, {a1 - border, h, a4 + border}, false);
    } else {
        add_face({a1, h, a1}, {a2, h, a1}, {a2, h, a4}, {a1, h, a4}, true);
        add_face({a1, -h, a1}, {a2, -h, a1}, {a2, -h, a4}, {a1, -h, a4}, false);
    }
    // right
    if (m_right) {
        add_face({a3, h, a1 - border}, {a4 + border, h, a1 - border}, {a4 + border, h, a4 + border}, {a3, h, a4 + border}, true);
        add_face({a3, -h, a1 - border}, {a4 + border, -h, a1 - border}, {a4 + border, -h, a4 + border}, {a3, -h, a4 + border}, false);
        add_face({a4 + border, h, a1 - border}, {a4 + border, -h, a1 - border}, {a4 + border, -h, a4 + border}, {a4 + border, h, a4 + border}, true);
    } else {
        add_face({a3, h, a1}, {a4, h, a1}, {a4, h, a4}, {a3, h, a4}, true);
        add_face({a3, -h, a1}, {a4, -h, a1}, {a4, -h, a4}, {a3, -h, a4}, false);
    }
}

void TrayBorderShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void TrayBorderShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
{
    if (m_size_known) {
        m_facet[m_facet_count].animation_id = 0.0;
        m_facet[m_facet_count].color = {1.0, 1.0, 1.0};
        if (flip) {
            m_facet[m_facet_count].v1 = v1;
            m_facet[m_facet_count].v2 = v3;
            m_facet[m_facet_count].v3 = v2;
        } else {
            m_facet[m_facet_count].v1 = v1;
            m_facet[m_facet_count].v2 = v2;
            m_facet[m_facet_count].v3 = v3;
        }
    }
    ++m_facet_count;
}

