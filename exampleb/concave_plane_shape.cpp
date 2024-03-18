//
// concave_plane_shape.cpp
//

#include "concave_plane_shape.h"
#include "pi.h"
#include <math.h>
#include <cstddef>

ConcavePlaneShape::ConcavePlaneShape(float radius, float angle_i, float angle_f, float height, int steps)
    : m_radius(radius)
    , m_angle_i(angle_i)
    , m_angle_f(angle_f)
    , m_height(height)
    , m_steps(steps)
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

ConcavePlaneShape::~ConcavePlaneShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int ConcavePlaneShape::facets() const
{
    return m_facet_count;
}

Facet ConcavePlaneShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void ConcavePlaneShape::define_shape()
{
    for (int i = 0; i < m_steps; i++) {
        slice(i, m_radius, m_angle_i * PI / 180.0, m_angle_f * PI / 180.0);
    }
}

void ConcavePlaneShape::slice(int step, float r, float theta_i, float theta_f)
{
    double dtheta = (theta_f - theta_i) / (float) m_steps;
    float theta1 = theta_i + dtheta * (float) step;
    float theta2 = theta_i + dtheta * (float) (step + 1);

    float y1 = m_height / 2.0;
    float y0 = -m_height / 2.0;
    float x0 = 0.0;
    float z0 = 0.0;
    float x1 = r * cos(theta1);
    float z1 = -r * sin(theta1);
    float x2 = r * cos(theta2);
    float z2 = -r * sin(theta2);

    add_face({x1, y1, z1}, {x2, y1, z2}, {x2, y0, z2}, {x1, y0, z1}, false);
}

void ConcavePlaneShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void ConcavePlaneShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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
