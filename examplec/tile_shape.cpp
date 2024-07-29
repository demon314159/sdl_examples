//
// tile_shape.cpp
//

#include "tile_shape.h"
#include "math.h"

TileShape::TileShape(float pitch, float width, float height, float border,
                     bool upper, bool lower, bool left, bool right,
                     bool upper_left, bool upper_right, bool lower_left, bool lower_right)
    : m_pitch(pitch)
    , m_width(width)
    , m_height(height)
    , m_border(border)
    , m_upper(upper)
    , m_lower(lower)
    , m_left(left)
    , m_right(right)
    , m_upper_left(upper_left)
    , m_upper_right(upper_right)
    , m_lower_left(lower_left)
    , m_lower_right(lower_right)
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

TileShape::~TileShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int TileShape::facets() const
{
    return m_facet_count;
}

Facet TileShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void TileShape::define_shape()
{

    float upperz = m_upper ? -m_pitch / 2.0 : -m_width / 2.0;
    float lowerz = m_lower ? m_pitch / 2.0 : m_width / 2.0;
    float leftx = m_left ? -m_pitch / 2.0 : -m_width / 2.0;
    float rightx = m_right ? m_pitch / 2.0 : m_width / 2.0;
    float w = m_width / 2.0;
    float h = m_height / 2.0;
    add_face({-w, h, -w}, {-w, h, w}, {w, h, w}, {w, h, -w}, false);
    add_face({-w, -h, -w}, {-w, -h, w}, {w, -h, w}, {w, -h, -w}, true);

    if (m_upper) {
        add_face({-w, h, -w}, {-w, h, upperz}, {w, h, upperz}, {w, h, -w}, true);
        add_face({-w, -h, -w}, {-w, -h, upperz}, {w, -h, upperz}, {w, -h, -w}, false);
    }
    if (m_lower) {
        add_face({-w, h, w}, {-w, h, lowerz}, {w, h, lowerz}, {w, h, w}, false);
        add_face({-w, -h, w}, {-w, -h, lowerz}, {w, -h, lowerz}, {w, -h, w}, true);
    }
    if (m_left) {
        add_face({leftx, h, w}, {-w, h, w}, {-w, h, -w}, {leftx, h, -w}, false);
        add_face({leftx, -h, w}, {-w, -h, w}, {-w, -h, -w}, {leftx, -h, -w}, true);
    }
    if (m_right) {
        add_face({w, h, w}, {rightx, h, w}, {rightx, h, -w}, {w, h, -w}, false);
        add_face({w, -h, w}, {rightx, -h, w}, {rightx, -h, -w}, {w, -h, -w}, true);
    }
    if (m_upper_left) {
        add_face({leftx, h, upperz}, {leftx, h, -w}, {-w, h, -w}, {-w, h, upperz}, false);
        add_face({leftx, -h, upperz}, {leftx, -h, -w}, {-w, -h, -w}, {-w, -h, upperz}, true);
    }
    if (m_upper_right) {
        add_face({w, h, upperz}, {w, h, -w}, {rightx, h, -w}, {rightx, h, upperz}, false);
        add_face({w, -h, upperz}, {w, -h, -w}, {rightx, -h, -w}, {rightx, -h, upperz}, true);
    }
    if (m_lower_left) {
        add_face({leftx, h, w}, {leftx, h, lowerz}, {-w, h, lowerz}, {-w, h, w}, false);
        add_face({leftx, -h, w}, {leftx, -h, lowerz}, {-w, -h, lowerz}, {-w, -h, w}, true);
    }
    if (m_lower_right) {
        add_face({w, h, w}, {w, h, lowerz}, {rightx, h, lowerz}, {rightx, h, w}, false);
        add_face({w, -h, w}, {w, -h, lowerz}, {rightx, -h, lowerz}, {rightx, -h, w}, true);
    }
}

void TileShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void TileShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

