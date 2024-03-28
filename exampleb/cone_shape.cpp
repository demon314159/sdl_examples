//
// cone_shape.cpp
//

#include "cone_shape.h"
#include "pi.h"
#include "math.h"

ConeShape::ConeShape(float bottom_radius, float top_radius, float height, int steps)
    : m_bottom_radius(bottom_radius)
    , m_top_radius(top_radius)
    , m_height(height)
    , m_steps(steps)
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

ConeShape::~ConeShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int ConeShape::facets() const
{
    return m_facet_count;
}

Facet ConeShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void ConeShape::define_shape()
{
    for (int i = 0; i < m_steps; i++) {
        ay_slice(i, m_steps);
    }
}

void ConeShape::ay_slice(int step, int steps)
{
    double da = 2.0 * PI / (float) steps;
    float a1 = da * (float) step;
    float a2 = da * (float) (step + 1);
    float x1 = m_bottom_radius * cos(a1);
    float z1 = m_bottom_radius * sin(a1);
    float x2 = m_bottom_radius * cos(a2);
    float z2 = m_bottom_radius * sin(a2);

    float ux1 = m_top_radius * cos(a1);
    float uz1 = m_top_radius * sin(a1);
    float ux2 = m_top_radius * cos(a2);
    float uz2 = m_top_radius * sin(a2);

    float y0 = 0.0;
    float y1 = m_height;


    add_face({x1, y0, z1}, {x2, y0, z2}, {ux2, y1, uz2}, {ux1, y1, uz1}, true);
    add_face({x1, y0, z1}, {x2, y0, z2}, {0.0, y0, 0.0}, false);
    if (m_top_radius >= 0.0) {
        add_face({ux1, y1, uz1}, {ux2, y1, uz2}, {0.0, y1, 0.0}, true);
    }
}

void ConeShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void ConeShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

