//
// toroid_shape.cpp
//

#include "toroid_shape.h"
#include "pi.h"
#include "math.h"

ToroidShape::ToroidShape(float major_radius, float minor_radius, int steps, float major_angle_i, float major_angle_f, float minor_angle_i, float minor_angle_f)
    : m_major_radius(major_radius)
    , m_minor_radius(minor_radius)
    , m_steps(steps)
    , m_major_angle_i(major_angle_i * PI / 180.0)
    , m_major_angle_f(major_angle_f * PI / 180.0)
    , m_minor_angle_i(minor_angle_i * PI / 180.0)
    , m_minor_angle_f(minor_angle_f * PI / 180.0)
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

ToroidShape::~ToroidShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int ToroidShape::facets() const
{
    return m_facet_count;
}

Facet ToroidShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void ToroidShape::define_shape()
{
    int steps = round(m_steps * (m_major_angle_f - m_major_angle_i) / (2.0 * PI));
    steps = (steps < 1) ? 1 : steps;
    for (int i = 0; i < steps; i++) {
        ay_slice(i, steps);
    }
}

void ToroidShape::ay_slice(int step, int steps)
{
    int steps2 = round(m_steps * (m_minor_angle_f - m_minor_angle_i) / (2.0 * PI));
    double da = (m_major_angle_f - m_major_angle_i) / (float) steps;
    float major_a1 = m_major_angle_i + da * (float) step;
    float major_a2 = m_major_angle_i + da * (float) (step + 1);
    for (int j = 0; j < steps2; j++) {
        ax_slice(j, steps2, major_a1, major_a2);
    }
}

void ToroidShape::ax_slice(int step, int steps, float major_a1, float major_a2)
{
    double da = (m_minor_angle_f - m_minor_angle_i) / (float) steps;
    float minor_a1 = m_minor_angle_i + da * (float) step;
    float minor_a2 = m_minor_angle_i + da * (float) (step + 1);
    one_square(major_a1, major_a2, minor_a1, minor_a2);
}

void ToroidShape::one_square(float major_a1, float major_a2, float minor_a1, float minor_a2)
{
    Float3 p1;
    Float3 p2;

    p1.v1 = 0.0;
    p1.v2 = m_minor_radius * sin(minor_a1);
    p1.v3 = m_minor_radius * cos(minor_a1) + m_major_radius;
    p2.v1 = 0.0;
    p2.v2 = m_minor_radius * sin(minor_a2);
    p2.v3 = m_minor_radius * cos(minor_a2) + m_major_radius;

    Float3 v1 = rotate_ay(p1, major_a1);
    Float3 v2 = rotate_ay(p2, major_a1);
    Float3 v3 = rotate_ay(p2, major_a2);
    Float3 v4 = rotate_ay(p1, major_a2);

    add_face(v1, v2, v3, v4, true);
}

void ToroidShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void ToroidShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

Float3 ToroidShape::rotate_ay(Float3 p, float angle) const
{
   Float3 p1 = p;
   p1.v1 = p.v1 * cos(angle) + p.v3 * sin(angle);
   p1.v3 = -p.v1 * sin(angle) + p.v3 * cos(angle);
   return p1;
}
