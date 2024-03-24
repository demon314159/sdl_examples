//
// pipe_elbow_shape.cpp
//

#include "pipe_elbow_shape.h"
#include "pi.h"
#include "math.h"

PipeElbowShape::PipeElbowShape(float radius, float bend_radius, float bend_angle, int steps, int bend_steps)
    : m_radius(radius)
    , m_bend_radius(bend_radius)
    , m_bend_angle(bend_angle)
    , m_steps(steps)
    , m_bend_steps(bend_steps)
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

PipeElbowShape::~PipeElbowShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int PipeElbowShape::facets() const
{
    return m_facet_count;
}

Facet PipeElbowShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void PipeElbowShape::translate(Float3& point, float x, float y, float z) const
{
    point.v1 += x;
    point.v2 += y;
    point.v3 += z;
}

void PipeElbowShape::rotate_ay(Float3& point, float angle) const
{
    Float3 r;
    r.v1 = point.v1 * cos(angle * PI / 180.0) + point.v3 * sin(angle * PI / 180.0);
    r.v2 = point.v2;
    r.v3 = -point.v1 * sin(angle * PI / 180.0) + point.v3 * cos(angle * PI / 180.0);
    point = r;
}

void PipeElbowShape::define_shape()
{
    float ay_i = 0.0;
    float ay_f = m_bend_angle;
    for (int i = 0; i < m_bend_steps; i++) {
        bend_slice(i, ay_i, ay_f);
    }
}

void PipeElbowShape::bend_slice(int step, float ay_i, float ay_f)
{
    double d_ay = (ay_f - ay_i) / (float) m_steps;
    float ay1 = ay_i + d_ay * (float) step;
    float ay2 = ay_i + d_ay * (float) (step + 1);

    float ax_i = 0.0;
    float ax_f = 360.0;
    for (int i = 0; i < m_steps; i++) {
        slice(i, ax_i, ax_f, ay1, ay2);
    }
}

void PipeElbowShape::slice(int step, float ax_i, float ax_f, float ay1, float ay2)
{
    double d_ax = (ax_f - ax_i) / (float) m_steps;
    float ax1 = ax_i + d_ax * (float) step;
    float ax2 = ax_i + d_ax * (float) (step + 1);

    Float3 p1 = {0.0, m_radius * sinf(ax1 * PI / 180.0), m_radius * cosf(ax1 * PI / 180.0)};
    Float3 p2 = {0.0, m_radius * sinf(ax2 * PI / 180.0), m_radius * cosf(ax2 * PI / 180.0)};

    if (ay2 > ay1) {
        translate(p1, 0.0, 0.0, m_bend_radius);
        translate(p2, 0.0, 0.0, m_bend_radius);
    } else {
        translate(p1, 0.0, 0.0, -m_bend_radius);
        translate(p2, 0.0, 0.0, -m_bend_radius);
    }
    Float3 p3 = p2;
    Float3 p4 = p1;
    rotate_ay(p1, ay1);
    rotate_ay(p2, ay1);
    rotate_ay(p3, ay2);
    rotate_ay(p4, ay2);
    if (ay2 > ay1) {
        translate(p1, 0.0, 0.0, -m_bend_radius);
        translate(p2, 0.0, 0.0, -m_bend_radius);
        translate(p3, 0.0, 0.0, -m_bend_radius);
        translate(p4, 0.0, 0.0, -m_bend_radius);
    } else {
        translate(p1, 0.0, 0.0, m_bend_radius);
        translate(p2, 0.0, 0.0, m_bend_radius);
        translate(p3, 0.0, 0.0, m_bend_radius);
        translate(p4, 0.0, 0.0, m_bend_radius);
    }
    add_face(p1, p2, p3, p4, true);
}

void PipeElbowShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void PipeElbowShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

