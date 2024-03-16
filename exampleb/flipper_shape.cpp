//
// flipper_shape.cpp
//

#include "flipper_shape.h"
#include "pi.h"
#include "math.h"

FlipperShape::FlipperShape(float r1, float r2, float length, float height)
    : m_r1(r1)
    , m_r2(r2)
    , m_length(length)
    , m_height(height)
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

FlipperShape::~FlipperShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int FlipperShape::facets() const
{
    return m_facet_count;
}

Facet FlipperShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void FlipperShape::define_shape()
{
    define_cylinders();
    define_walls();
}

void FlipperShape::define_cylinders()
{
    int steps = 50;
    double theta = asin((m_r1 - m_r2) / m_length);
    float theta_i = PI / 2.0 - theta;
    float theta_f = 3.0 * PI / 2.0 + theta;
    for (int i = 0; i < steps; i++) {
        cylinder_slice(i, steps, m_r1, theta_i, theta_f, 0.0);
    }
    theta_i = 3.0 * PI / 2.0 + theta;
    theta_f = 2.0 * PI + PI / 2.0 - theta;
    for (int i = 0; i < steps; i++) {
        cylinder_slice(i, steps, m_r2, theta_i, theta_f, m_length);
    }
}

void FlipperShape::define_walls()
{
    double theta = asin((m_r1 - m_r2) / m_length);
    float theta_i1 = PI / 2.0 - theta;
    float theta_f2 = 2.0 * PI + PI / 2.0 - theta;
    float x1 = m_r1 * cos(theta_i1);
    float z1 = m_r1 * sin(theta_i1);
    float x2 = m_r2 * cos(theta_f2) + m_length;
    float z2 = m_r2 * sin(theta_f2);
    float y1 = m_height / 2.0;
    float y0 = -m_height / 2.0;

    // top face
    add_face({x1, y1, z1}, {x2, y1, z2}, {m_length, y1, 0.0}, {0.0, y1, 0.0}, false);
    add_face({x1, y1, -z1}, {0.0, y1, 0.0}, {m_length, y1, 0.0}, {x2, y1, -z2}, false);

    // bottom face
    add_face({x1, y0, z1}, {x2, y0, z2}, {m_length, y0, 0.0}, {0.0, y0, 0.0}, true);
    add_face({x1, y0, -z1}, {0.0, y0, 0.0}, {m_length, y0, 0.0}, {x2, y0, -z2}, true);

    // sides
    add_face({x1, y1, z1}, {x1, y0, z1}, {x2, y0, z2}, {x2, y1, z2}, false);
    add_face({x1, y1, -z1}, {x1, y0, -z1}, {x2, y0, -z2}, {x2, y1, -z2}, true);
}

void FlipperShape::cylinder_slice(int step, int steps, float r, float theta_i, float theta_f, float xoff)
{
    double dtheta = (theta_f - theta_i) / (float) steps;
    float theta1 = theta_i + dtheta * (float) step;
    float theta2 = theta_i + dtheta * (float) (step + 1);

    float y1 = m_height / 2.0;
    float y0 = -m_height / 2.0;
    float x0 = 0.0 + xoff;
    float z0 = 0.0;
    float x1 = r * cos(theta1) + xoff;
    float z1 = r * sin(theta1);
    float x2 = r * cos(theta2) + xoff;
    float z2 = r * sin(theta2);

    add_face({x0, y1, z0}, {x1, y1, z1}, {x2, y1, z2}, true);
    add_face({x1, y1, z1}, {x2, y1, z2}, {x2, y0, z2}, {x1, y0, z1}, false);
    add_face({x0, y0, z0}, {x1, y0, z1}, {x2, y0, z2}, false);
}

void FlipperShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void FlipperShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

