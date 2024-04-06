//
// atomic_shape.cpp
//

#include "atomic_shape.h"
#include "pi.h"
#include "math.h"

AtomicShape::AtomicShape(float major_radius, float minor_radius, float height)
    : m_major_radius(major_radius)
    , m_minor_radius(minor_radius)
    , m_height(height)
    , m_steps(10)
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

AtomicShape::~AtomicShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int AtomicShape::facets() const
{
    return m_facet_count;
}

Facet AtomicShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void AtomicShape::define_shape()
{
    for (int i = 0; i < m_steps; i++) {
        slice(i);
    }
}

void AtomicShape::slice(int step)
{
    float da = 360.0 / (float) m_steps;
    float a1 = da * (float) step;
    float a2 = da * (float) (step + 1);
    float x1 = m_major_radius * cos(a1 * PI / 180.0);
    float z1 = -m_major_radius * sin(a1 * PI / 180.0);
    float x2 = m_major_radius * cos(a2 * PI / 180.0);
    float z2 = -m_major_radius * sin(a2 * PI / 180.0);
    float x3 = m_minor_radius * cos(a1 * PI / 180.0);
    float z3 = -m_minor_radius * sin(a1 * PI / 180.0);
    float x4 = m_minor_radius * cos(a2 * PI / 180.0);
    float z4 = -m_minor_radius * sin(a2 * PI / 180.0);
    add_line(x1, z1, x4, z4, true);
    add_line(x2, z2, x3, z3, false);
}

void AtomicShape::add_line(float x1, float z1, float x2, float z2, bool flag)
{
    float y1 = -m_height / 2.0;
    float y2 = m_height / 2.0;
    float dx = x2 - x1;
    float dz = z2 - z1;
    float length = sqrt(dx * dx + dz * dz) * 1.05;
    float angle = atan2(-dz, dx) * 180.0 / PI;
    Float2 position = {(x1 + x2) / 2.0f, (z1 + z2) / 2.0f};

    Float2 p1 = {-length / 2.0f, -m_height / 2.0f};
    Float2 p2 = {length / 2.0f, -m_height / 2.0f};
    Float2 p3 = {length / 2.0f, m_height / 2.0f};
    Float2 p4 = {-length / 2.0f, m_height / 2.0f};

    rotate(p1, angle);
    rotate(p2, angle);
    rotate(p3, angle);
    rotate(p4, angle);
    translate(p1, position);
    translate(p2, position);
    translate(p3, position);
    translate(p4, position);
    add_face({p1.v1, y2, p1.v2}, {p2.v1, y2, p2.v2}, {p3.v1, y2, p3.v2}, {p4.v1, y2, p4.v2}, true);
    add_face({p1.v1, y1, p1.v2}, {p2.v1, y1, p2.v2}, {p3.v1, y1, p3.v2}, {p4.v1, y1, p4.v2}, false);
    add_face({p1.v1, y1, p1.v2}, {p2.v1, y1, p2.v2}, {p2.v1, y2, p2.v2}, {p1.v1, y2, p1.v2}, true);
    add_face({p2.v1, y1, p2.v2}, {p3.v1, y1, p3.v2}, {p3.v1, y2, p3.v2}, {p2.v1, y2, p2.v2}, true);
    add_face({p3.v1, y1, p3.v2}, {p4.v1, y1, p4.v2}, {p4.v1, y2, p4.v2}, {p3.v1, y2, p3.v2}, true);
    add_face({p4.v1, y1, p4.v2}, {p1.v1, y1, p1.v2}, {p1.v1, y2, p1.v2}, {p4.v1, y2, p4.v2}, true);

    float f = 0.3;
    scale(p1, f);
    scale(p2, f);
    scale(p3, f);
    scale(p4, f);

    if (flag) {
        add_face({0.0, y2, 0.0}, {p2.v1, y2, p2.v2}, {p3.v1, y2, p3.v2}, {p4.v1, y2, p4.v2}, true);
    } else {
        add_face({p1.v1, y2, p1.v2}, {p2.v1, y2, p2.v2}, {0.0, y2, 0.0}, {p4.v1, y2, p4.v2}, true);
    }
}

void AtomicShape::rotate(Float2& point, float angle) const
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * point.v1 + sint * point.v2;
    float tz = -sint * point.v1 + cost * point.v2;
    point = {tx, tz};
}

void AtomicShape::translate(Float2& point, Float2 distance) const
{
    point.v1 += distance.v1;
    point.v2 += distance.v2;
}

void AtomicShape::scale(Float2& point, float f) const
{
    point.v1 *= f;
    point.v2 *= f;
}

void AtomicShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void AtomicShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

