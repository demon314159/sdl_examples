//
// disc_shape.cpp
//

#include "disc_shape.h"
#include "pi.h"
#include "math.h"

DiscShape::DiscShape(float radius, float height, int major_steps, int minor_steps, bool top_only,
                     bool lit_only, bool unlit_only)
    : m_radius(radius)
    , m_height(height)
    , m_major_steps(major_steps)
    , m_minor_steps(minor_steps)
    , m_top_only(top_only)
    , m_lit_only(lit_only)
    , m_unlit_only(unlit_only)
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

DiscShape::~DiscShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int DiscShape::facets() const
{
    return m_facet_count;
}

Facet DiscShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void DiscShape::define_shape()
{
    for (int i = 0; i < m_major_steps; i++) {
        slice_ay(i);
    }
}

void DiscShape::slice_ay(int step)
{
    double day = 360.0 / (float) m_major_steps;
    float ay1 = day * (float) step;
    float ay2 = day * (float) (step + 1);
    float rminor = m_height / 2.0;
    float rmajor = m_radius - rminor;

    float x1 = rmajor * cos(ay1 * PI / 180.0);
    float z1 = rmajor * sin(ay1 * PI / 180.0);
    float x2 = rmajor * cos(ay2 * PI / 180.0);
    float z2 = rmajor * sin(ay2 * PI / 180.0);
    float y1 = -m_height / 2.0;
    float y2 = m_height / 2.0;
    if (!m_unlit_only) {
        add_face({x1, y2, z1}, {x2, y2, z2}, {0.0, y2, 0.0}, true);
    }
    if (!m_lit_only) {
        if (!m_top_only) {
            add_face({x1, y1, z1}, {x2, y1, z2}, {0.0, y1, 0.0}, false);
        }
        for (int j = 0; j < m_minor_steps; j++) {
            edge_slice(j, rmajor, rminor, ay1, ay2);
        }
    }
}

void DiscShape::edge_slice(int step, float rmajor, float rminor, float ay1, float ay2)
{
    double dax = 180.0 / (float) m_minor_steps;
    float ax1 = -90.0 + dax * (float) step;
    float ax2 = -90.0 + dax * (float) (step + 1);

    float x1 = rmajor + rminor * cos(ax1 * PI / 180.0);
    float y1 = rminor * sin(ax1 * PI / 180.0);
    float x2 = rmajor + rminor * cos(ax2 * PI / 180.0);
    float y2 = rminor * sin(ax2 * PI / 180.0);

    Float3 p1 = {x1, y1, 0.0};
    Float3 p2 = {x2, y2, 0.0};
    Float3 p3 = {x2, y2, 0.0};
    Float3 p4 = {x1, y1, 0.0};
    rotate(p1, ay1);
    rotate(p2, ay1);
    rotate(p3, ay2);
    rotate(p4, ay2);
    if (m_top_only) {
        if (ax1 >= 0.0 && ax2 >= 0.0) {
            add_face(p1, p2, p3, p4, true);
        }
    } else {
        add_face(p1, p2, p3, p4, true);
    }
}

void DiscShape::rotate(Float3& point, float angle) const
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * point.v1 + sint * point.v3;
    float ty = point.v2;
    float tz = -sint * point.v1 + cost * point.v3;
    point = {tx, ty, tz};
}

void DiscShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void DiscShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

