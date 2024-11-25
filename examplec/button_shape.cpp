//
// button_shape.cpp
//

#include "button_shape.h"
#include "math.h"

ButtonShape::ButtonShape(float radius, float height, float minor_radius, int steps, int minor_steps)
    : m_height(height)
    , m_major_radius(radius)
    , m_minor_radius(minor_radius)
    , m_major_steps(steps)
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

ButtonShape::~ButtonShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int ButtonShape::facets() const
{
    return m_facet_count;
}

Facet ButtonShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void ButtonShape::define_shape()
{
    for (int i = 0; i < m_minor_steps; i++) {
        button_slice(i, m_minor_steps);
    }
}

void ButtonShape::button_slice(int step, int steps)
{
    double dax = (PI / 2.0) / (float) steps;
    float ax1 = dax * (float) step;
    float ax2 = dax * (float) (step + 1);
    float px1 = 0.0;
    float py1 = m_height - m_minor_radius + m_minor_radius * sin(ax1);
    float pz1 = m_major_radius + m_minor_radius * cos(ax1);
    float px2 = 0.0;
    float py2 = m_height - m_minor_radius + m_minor_radius * sin(ax2);
    float pz2 = m_major_radius + m_minor_radius * cos(ax2);
    for (int j = 0; j < m_major_steps; j++) {
        slice_slice(j, m_major_steps, {px1, py1, pz1}, {px2, py2, pz2}, step == (steps - 1), step == 0);
    }
}

void ButtonShape::slice_slice(int step, int steps, const Float3& pa, const Float3& pb, bool top, bool bottom)
{
    double day = (2.0 * PI) / (float) steps;
    float ay1 = day * (float) step;
    float ay2 = day * (float) (step + 1);
    Float3 p1 = rotate_ay(pa, ay1);
    Float3 p2 = rotate_ay(pa, ay2);
    Float3 p3 = rotate_ay(pb, ay2);
    Float3 p4 = rotate_ay(pb, ay1);
    add_face(p1, p2, p3, p4);
    if (top) {
        add_face({0.0, m_height, 0.0}, p4, p3);
    }
    if (bottom) {
        add_face(p1, p2, {p2.v1, 0.0, p2.v3}, {p1.v1, 0.0, p1.v3}, true);
    }

}


void ButtonShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void ButtonShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

Float3 ButtonShape::rotate_ay(Float3 p, float angle) const
{
   Float3 p1 = p;
   p1.v1 = p.v1 * cos(angle) + p.v3 * sin(angle);
   p1.v3 = -p.v1 * sin(angle) + p.v3 * cos(angle);
   return p1;
}
