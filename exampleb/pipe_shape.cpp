//
// pipe_shape.cpp
//

#include "pipe_shape.h"
#include "pi.h"
#include "math.h"

PipeShape::PipeShape(float radius, float length, int steps)
    : m_radius(radius)
    , m_length(length)
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

PipeShape::~PipeShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int PipeShape::facets() const
{
    return m_facet_count;
}

Facet PipeShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void PipeShape::define_shape()
{
    float angle_i = 0.0;
    float angle_f = 2.0 * PI;
    for (int i = 0; i < m_steps; i++) {
        slice(i, angle_i, angle_f);
    }
}

void PipeShape::slice(int step, float angle_i, float angle_f)
{
    double dangle = (angle_f - angle_i) / (float) m_steps;
    float angle1 = angle_i + dangle * (float) step;
    float angle2 = angle_i + dangle * (float) (step + 1);

    float x2 = m_length;
    float x1 = 0.0;
    float y1 = m_radius * cos(angle1);
    float z1 = m_radius * sin(angle1);
    float y2 = m_radius * cos(angle2);
    float z2 = m_radius * sin(angle2);

    add_face({x1, y1, z1}, {x1, y2, z2}, {x2, y2, z2}, {x2, y1, z1}, false);
}

void PipeShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void PipeShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

