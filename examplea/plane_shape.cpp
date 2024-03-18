//
// plane_shape.cpp
//

#include "plane_shape.h"
#include <cstddef>

PlaneShape::PlaneShape(float dimx, float dimz)
    : m_dimx(dimx)
    , m_dimz(dimz)
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

PlaneShape::~PlaneShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int PlaneShape::facets() const
{
    return m_facet_count;
}

Facet PlaneShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void PlaneShape::define_shape()
{
    float x = m_dimx / 2.0;
    float y = 0.0;
    float z = m_dimz / 2.0;
    // top face only
    add_face({-x, y, -z}, {-x, y, z}, {x, y, z}, {x, y, -z}, false);
}

void PlaneShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void PlaneShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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
