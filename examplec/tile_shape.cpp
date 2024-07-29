//
// tile_shape.cpp
//

#include "tile_shape.h"
#include "math.h"

TileShape::TileShape(float pitch, float width, float height, float border, bool upper, bool lower, bool left, bool right)
    : m_pitch(pitch)
    , m_width(width)
    , m_height(height)
    , m_border(border)
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
    float h = m_height / 2.0;
    add_face({leftx, h, upperz}, {leftx, h, lowerz}, {rightx, h, lowerz}, {rightx, h, upperz}, false);
    add_face({leftx, -h, upperz}, {leftx, -h, lowerz}, {rightx, -h, lowerz}, {rightx, -h, upperz}, true);
    if (!m_upper) {
        add_face({leftx, -h, upperz}, {leftx, h, upperz}, {rightx, h, upperz}, {rightx, -h, upperz}, false);
    }
    if (!m_lower) {
        add_face({leftx, -h, lowerz}, {leftx, h, lowerz}, {rightx, h, lowerz}, {rightx, -h, lowerz}, true);
    }
    if (!m_left) {
        add_face({leftx, -h, lowerz}, {leftx, h, lowerz}, {leftx, h, upperz}, {leftx, -h, upperz}, false);
    }
    if (!m_right) {
        add_face({rightx, -h, lowerz}, {rightx, h, lowerz}, {rightx, h, upperz}, {rightx, -h, upperz}, true);
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

