//
// diamond_shape.cpp
//

#include "diamond_shape.h"
#include "pi.h"
#include "math.h"

DiamondShape::DiamondShape(float length, float width, float height)
    : m_length(length)
    , m_width(width)
    , m_height(height)
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

DiamondShape::~DiamondShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int DiamondShape::facets() const
{
    return m_facet_count;
}

Facet DiamondShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void DiamondShape::define_shape()
{
    float l = m_length / 2.0;
    float w = m_width / 2.0;
    float y1 = -m_height / 2.0;
    float y2 = m_height / 2.0;

    add_face({-l, y2, 0.0}, {0.0, y2, -w}, {l, y2, 0.0}, {0.0, y2, w}, true);
    add_face({-l, y1, 0.0}, {0.0, y1, -w}, {l, y1, 0.0}, {0.0, y1, w}, false);
    add_face({-l, y1, 0.0}, {0.0, y1, -w}, {0.0, y2, -w}, {-l, y2, 0.0}, true);
    add_face({-l, y1, 0.0}, {0.0, y1, w}, {0.0, y2, w}, {-l, y2, 0.0}, false);
    add_face({l, y1, 0.0}, {0.0, y1, -w}, {0.0, y2, -w}, {l, y2, 0.0}, false);
    add_face({l, y1, 0.0}, {0.0, y1, w}, {0.0, y2, w}, {l, y2, 0.0}, true);
}

void DiamondShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void DiamondShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

