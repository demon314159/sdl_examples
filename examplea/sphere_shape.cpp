//
// sphere_shape.cpp
//

#include "sphere_shape.h"
#include "math.h"

#define TOTAL_STEPS 25

SphereShape::SphereShape(float radius, float lattitude_i, float lattitude_f)
    : m_radius(radius)
    , m_lattitude_i(lattitude_i)
    , m_lattitude_f(lattitude_f)
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

SphereShape::~SphereShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int SphereShape::facets() const
{
    return m_facet_count;
}

Facet SphereShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void SphereShape::define_shape()
{
    int steps = round(TOTAL_STEPS * (m_lattitude_f - m_lattitude_i) / PI);
    steps = (steps < 1) ? 1 : steps;
    for (int i = 0; i < steps; i++) {
        sphere_slice(i, steps, m_radius, m_lattitude_i, m_lattitude_f);
    }
}

void SphereShape::sphere_slice(int step, int steps, float r, float lattitude_i, float lattitude_f)
{
    double dlattitude = (lattitude_f - lattitude_i) / (float) steps;
    float lattitude1 = lattitude_i + dlattitude * (float) step;
    float lattitude2 = lattitude_i + dlattitude * (float) (step + 1);
    for (int j = 0; j < TOTAL_STEPS; j++) {
        ring_slice(j, TOTAL_STEPS, r, lattitude1, lattitude2);
    }
}

void SphereShape::ring_slice(int step, int steps, float r, float lattitude1, float lattitude2)
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
    float y0 = r * sin(lattitude1);
    float y1 = r * sin(lattitude2);

    add_face({x2, y0, z2}, {x1, y0, z1}, {x4, y1, z4}, {x3, y1, z3}, false);
}

void SphereShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void SphereShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

