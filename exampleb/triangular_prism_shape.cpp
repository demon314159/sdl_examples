//
// triangular_prism_shape.cpp
//

#include "triangular_prism_shape.h"
#include "pi.h"
#include "math.h"

TriangularPrismShape::TriangularPrismShape(float length, float width, float height, float corner_radius)
    : m_length(length)
    , m_width(width)
    , m_height(height)
    , m_corner_radius(corner_radius)
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

TriangularPrismShape::~TriangularPrismShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int TriangularPrismShape::facets() const
{
    return m_facet_count;
}

Facet TriangularPrismShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void TriangularPrismShape::define_shape()
{
    float r = 0.001;
    float x0 = -m_length / 2.0;
    float x1 = -(m_length - r) / 2.0;
    float x2 = (m_length -  r) / 2.0;
    float x3 = m_length / 2.0;
    float y0 = 0.0;
    float z0 = -m_width / 2.0;
    float z1 = -(m_width - r) / 2.0;
    float z2 = (m_width - r) / 2.0;
    float z3 = m_width / 2.0;

    float ux0 = -(m_length - m_width) / 2.0 - r;
    float ux1 = -(m_length - m_width) / 2.0;
    float ux2 = (m_length - m_width) / 2.0;
    float ux3 = (m_length - m_width) / 2.0 + r;
    float y1 = m_height;
    float uz0 = -r;
    float uz1 = r;

    add_face({x1, y0, z0}, {x2, y0, z0}, {ux2, y1, uz0}, {ux1, y1, uz0}, true);
    add_face({x1, y0, z3}, {x2, y0, z3}, {ux2, y1, uz1}, {ux1, y1, uz1}, false);
    add_face({x0, y0, z1}, {x0, y0, z2}, {ux0, y1, uz1}, {ux0, y1, uz0}, false);
    add_face({x3, y0, z1}, {x3, y0, z2}, {ux3, y1, uz1}, {ux3, y1, uz0}, true);

    add_face({x0, y0, z1}, {x1, y0, z0}, {ux1, y1, uz0}, {ux0, y1, 0.0}, true);
    add_face({x0, y0, z2}, {x1, y0, z3}, {ux1, y1, uz1}, {ux0, y1, 0.0}, false);
    add_face({x2, y0, z0}, {x3, y0, z1}, {ux3, y1, 0.0}, {ux2, y1, uz0}, true);
    add_face({x2, y0, z3}, {x3, y0, z2}, {ux3, y1, 0.0}, {ux2, y1, uz1}, false);

    add_face({ux0, y1, 0.0}, {ux3, y1, 0.0}, {ux2, y1, uz0}, {ux1, y1, uz0}, false);
    add_face({ux0, y1, 0.0}, {ux3, y1, 0.0}, {ux2, y1, uz1}, {ux1, y1, uz1}, true);

}

void TriangularPrismShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void TriangularPrismShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

