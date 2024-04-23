//
// crown_nut_shape.cpp
//

#include "crown_nut_shape.h"
#include "pi.h"
#include "math.h"

CrownNutShape::CrownNutShape(float radius, float height, int major_steps, int minor_steps)
    : m_radius(radius)
    , m_height(height)
    , m_major_steps(major_steps)
    , m_minor_steps(minor_steps)
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

CrownNutShape::~CrownNutShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int CrownNutShape::facets() const
{
    return m_facet_count;
}

Facet CrownNutShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void CrownNutShape::define_shape()
{
    int steps = 6;
    for (int i = 0; i < steps; i++) {
        slice_ay(i, steps);
    }
    float radius = m_radius * 0.7;
    for (int i = 0; i < m_minor_steps; i++) {
        sphere_slice(i, m_minor_steps, radius, 0.0, PI / 2.0);
    }
}

void CrownNutShape::sphere_slice(int step, int steps, float r, float lattitude_i, float lattitude_f)
{
    double dlattitude = (lattitude_f - lattitude_i) / (float) steps;
    float lattitude1 = lattitude_i + dlattitude * (float) step;
    float lattitude2 = lattitude_i + dlattitude * (float) (step + 1);
    for (int j = 0; j < m_major_steps; j++) {
        ring_slice(j, m_major_steps, r, lattitude1, lattitude2);
    }
}

void CrownNutShape::ring_slice(int step, int steps, float r, float lattitude1, float lattitude2)
{
    float dlong = 2.0 * PI / (float) steps;
    float longitude1 = dlong * (float) step;
    float longitude2 = dlong * (float) (step + 1);
    float x1 = r * cos(longitude1) * cos(lattitude1);
    float x2 = r * cos(longitude2) * cos(lattitude1);
    float x3 = r * cos(longitude2) * cos(lattitude2);
    float x4 = r * cos(longitude1) * cos(lattitude2);
    float z1 = r * sin(longitude1) * cos(lattitude1);
    float z2 = r * sin(longitude2) * cos(lattitude1);
    float z3 = r * sin(longitude2) * cos(lattitude2);
    float z4 = r * sin(longitude1) * cos(lattitude2);
    float y0 = r * sin(lattitude1) + m_height;
    float y1 = r * sin(lattitude2) + m_height;

    add_face({x2, y0, z2}, {x1, y0, z1}, {x4, y1, z4}, {x3, y1, z3}, false);
}

void CrownNutShape::slice_ay(int step, int steps)
{
    double day = 360.0 / (float) steps;
    float ay1 = day * (float) step;
    float ay2 = day * (float) (step + 1);

    float x1 = m_radius * cos(ay1 * PI / 180.0);
    float z1 = m_radius * sin(ay1 * PI / 180.0);
    float x2 = m_radius * cos(ay2 * PI / 180.0);
    float z2 = m_radius * sin(ay2 * PI / 180.0);
    float y1 = 0.0;
    float y2 = m_height;
    add_face({x1, y2, z1}, {x2, y2, z2}, {0.0, y2, 0.0}, true);
    add_face({x1, y1, z1}, {x2, y1, z2}, {0.0, y1, 0.0}, false);
    add_face({x1, y1, z1}, {x2, y1, z2}, {x2, y2, z2}, {x1, y2, z1}, true);
    float r = m_radius * 0.7;

}

void CrownNutShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void CrownNutShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

