//
// top_panel_shape.cpp
//

#include "top_panel_shape.h"
#include <cstddef>
#include "pi.h"
#include <math.h>

TopPanelShape::TopPanelShape(float dimx, float radius, float angle_i, float angle_f, Float2 focus, float left_x, float left_z, int steps)
    : m_dimx(dimx)
    , m_radius(radius)
    , m_angle_i(angle_i)
    , m_angle_f(angle_f)
    , m_focus(focus)
    , m_left_x(left_x)
    , m_left_z(left_z)
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

TopPanelShape::~TopPanelShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int TopPanelShape::facets() const
{
    return m_facet_count;
}

Facet TopPanelShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void TopPanelShape::define_shape()
{
    for (int i = 0; i < m_steps; i++) {
        slice(i);
    }
    float x1 = m_focus.v1 + m_radius * cos(m_angle_f * PI / 180.0);
    float z1 = m_focus.v2 - m_radius * sin(m_angle_f * PI / 180.0);
    float x2 = m_left_x;
    float z2 = m_left_z;
    add_face({x1, 0.0, z1}, {x2, 0.0, z2}, {x2, 0.0, 0.0}, {x1, 0.0, 0.0}, true);
}

void TopPanelShape::slice(int step)
{
    double dtheta = (m_angle_f - m_angle_i) / (float) m_steps;
    float theta1 = m_angle_i + dtheta * (float) step;
    float theta2 = m_angle_i + dtheta * (float) (step + 1);

    float x1 = m_focus.v1 + m_radius * cos(theta1 * PI / 180.0);
    float z1 = m_focus.v2 - m_radius * sin(theta1 * PI / 180.0);
    float x2 = m_focus.v1 + m_radius * cos(theta2 * PI / 180.0);
    float z2 = m_focus.v2 - m_radius * sin(theta2 * PI / 180.0);

    add_face({x1, 0.0, z1}, {x2, 0.0, z2}, {x2, 0.0, 0.0}, {x1, 0.0, 0.0}, true);
}

void TopPanelShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void TopPanelShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

