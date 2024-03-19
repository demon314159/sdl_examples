//
// bottom_panel_shape.cpp
//

#include "bottom_panel_shape.h"
#include <cstddef>
#include "pi.h"
#include <math.h>

BottomPanelShape::BottomPanelShape(float x1, float x2, float x3, float x4, float z1, float z2, float z3)
    : m_x1(x1)
    , m_x2(x2)
    , m_x3(x3)
    , m_x4(x4)
    , m_z1(z1)
    , m_z2(z2)
    , m_z3(z3)
    , m_size_known(false)
    , m_facet_count(0)
    , m_facet(NULL)
{
    define_shape();  // Pass 1 counts the facets to determine size
    m_size_known = true;
    if (m_facet_count > 0) {
        m_facet = new Facet[m_facet_count];
        m_facet_count = 0;
        define_shape();  // Pass 2 loads facets once size is known
    }
}

BottomPanelShape::~BottomPanelShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int BottomPanelShape::facets() const
{
    return m_facet_count;
}

Facet BottomPanelShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void BottomPanelShape::define_shape()
{
    add_face({m_x1, 0.0, m_z3}, {m_x1, 0.0, m_z1}, {m_x2, 0.0, m_z2}, {m_x2, 0.0, m_z3}, true);
    add_face({m_x2, 0.0, m_z3}, {m_x2, 0.0, m_z2}, {m_x3, 0.0, m_z2}, {m_x3, 0.0, m_z3}, true);
    add_face({m_x3, 0.0, m_z3}, {m_x3, 0.0, m_z2}, {m_x4, 0.0, m_z1}, {m_x4, 0.0, m_z3}, true);
}

void BottomPanelShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void BottomPanelShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

