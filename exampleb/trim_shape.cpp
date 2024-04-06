//
// trim_shape.cpp
//

#include "trim_shape.h"
#include "pi.h"
#include "math.h"

TrimShape::TrimShape(float major_radius, float minor_radius, float height, int steps)
    : m_major_radius(major_radius)
    , m_minor_radius(minor_radius)
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

TrimShape::~TrimShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int TrimShape::facets() const
{
    return m_facet_count;
}

Facet TrimShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void TrimShape::define_shape()
{
    for (int i = 0; i < m_steps; i++) {
        slice_ay(i);
    }
}

void TrimShape::slice_ay(int step)
{
    float y2 = m_height / 2.0;
    float y1 = -m_height / 2.0;
    double da = 360.0 / (float) m_steps;
    float a1 = da * (float) step;
    float a2 = da * (float) (step + 1);

    float k1 = (m_major_radius - m_minor_radius) * fabs(cos(4.0 * a1 * PI / 180.0));
    float k2 = (m_major_radius - m_minor_radius) * fabs(cos(4.0 * a2 * PI / 180.0));
    float x1 = (m_major_radius - k1) * cos(a1 * PI / 180.0);
    float z1 = (m_major_radius - k1) * sin(a1 * PI / 180.0);
    float x2 = (m_major_radius - k2) * cos(a2 * PI / 180.0);
    float z2 = (m_major_radius - k2) * sin(a2 * PI / 180.0);
    add_face({x1, y2, z1}, {x2, y2, z2}, {0.0, y2, 0.0}, true);
    add_face({x1, y1, z1}, {x2, y1, z2}, {0.0, y1, 0.0}, true);
    add_face({x1, y1, z1}, {x2, y1, z2}, {x2, y2, z2}, {x1, y2, z1}, true);
}

void TrimShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void TrimShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

