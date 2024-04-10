//
// flat_rail_shape.cpp
//

#include "flat_rail_shape.h"
#include "pi.h"
#include "math.h"

FlatRailShape::FlatRailShape(float length, float width, float thickness, float bend_radius,
                             float height, int steps)
    : m_length(length)
    , m_width(width)
    , m_thickness(thickness)
    , m_bend_radius(bend_radius)
    , m_height(height)
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

FlatRailShape::~FlatRailShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int FlatRailShape::facets() const
{
    return m_facet_count;
}

Facet FlatRailShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void FlatRailShape::define_shape()
{
    float angle = acos((m_bend_radius - m_width) / m_bend_radius) * 180.0 / PI;
    float k = m_bend_radius * sin(angle * PI / 180.0);
    float l1 = m_length - 2.0 * k;
    box_shape(m_thickness, m_height, l1);
    for (int i = 0; i < m_steps; i++) {
        ay_slice(i, angle, l1);
    }
}

void FlatRailShape::ay_slice(int step, float angle, float l1)
{
    double day = angle / (float) m_steps;
    float ay1 = day * (float) step;
    float ay2 = day * (float) (step + 1);
    float rminor = m_bend_radius - m_thickness;
    float rmajor = m_bend_radius;

    float x1 = -rmajor + rmajor * cos(ay1 * PI / 180.0);
    float z1 = -l1 / 2.0 - rmajor * sin(ay1 * PI / 180.0);
    float x2 = -rmajor + rminor * cos(ay1 * PI / 180.0);
    float z2 = -l1 / 2.0 - rminor * sin(ay1 * PI / 180.0);
    float x3 = -rmajor + rminor * cos(ay2 * PI / 180.0);
    float z3 = -l1 / 2.0 - rminor * sin(ay2 * PI / 180.0);
    float x4 = -rmajor + rmajor * cos(ay2 * PI / 180.0);
    float z4 = -l1 / 2.0 - rmajor * sin(ay2 * PI / 180.0);

    float y1 = -m_height / 2.0;
    float y2 = m_height / 2.0;

    // Top and bottom faces
    add_face({x1, y2, z1}, {x2, y2, z2}, {x3, y2, z3}, {x4, y2, z4}, true);
    add_face({x1, y1, z1}, {x2, y1, z2}, {x3, y1, z3}, {x4, y1, z4}, false);
    // Top and bottom reflection
    add_face({x1, y2, -z1}, {x2, y2, -z2}, {x3, y2, -z3}, {x4, y2, -z4}, false);
    add_face({x1, y1, -z1}, {x2, y1, -z2}, {x3, y1, -z3}, {x4, y1, -z4}, true);
    // Left and right faces
    add_face({x2, y2, z2}, {x3, y2, z3}, {x3, y1, z3}, {x2, y1, z2}, false);
    add_face({x1, y2, z1}, {x4, y2, z4}, {x4, y1, z4}, {x1, y1, z1}, true);
    // Left and right reflection
    add_face({x2, y2, -z2}, {x3, y2, -z3}, {x3, y1, -z3}, {x2, y1, -z2}, true);
    add_face({x1, y2, -z1}, {x4, y2, -z4}, {x4, y1, -z4}, {x1, y1, -z1}, false);
    if (step == (m_steps - 1)) {
        // End face
        add_face({x1, y2, z1}, {x2, y2, z2}, {x2, y1, z2}, {x1, y1, z1}, true);
        // End face reflection
        add_face({x1, y2, -z1}, {x2, y2, -z2}, {x2, y1, -z2}, {x1, y1, -z1}, false);
    }

}

void FlatRailShape::box_shape(float dimx, float dimy, float dimz)
{
    // top and borrom face
    add_face({-dimx, dimy / 2.0f, -dimz / 2.0f}, {-dimx, dimy / 2.0f, dimz / 2.0f}, {0.0, dimy / 2.0f, dimz / 2.0f}, {0.0, dimy / 2.0f, -dimz / 2.0f}, false);
    add_face({-dimx, -dimy / 2.0f, -dimz / 2.0f}, {-dimx, -dimy / 2.0f, dimz / 2.0f}, {0.0, -dimy / 2.0f, dimz / 2.0f}, {0.0, -dimy / 2.0f, -dimz / 2.0f}, true);
    // left and right face
    add_face({-dimx, dimy / 2.0f, -dimz / 2.0f}, {-dimx, dimy / 2.0f, dimz / 2.0f}, {-dimx, -dimy / 2.0f, dimz / 2.0f}, {-dimx, -dimy / 2.0f, -dimz / 2.0f}, true);
    add_face({0.0, dimy / 2.0f, -dimz / 2.0f}, {0.0, dimy / 2.0f, dimz / 2.0f}, {0.0, -dimy / 2.0f, dimz / 2.0f}, {0.0, -dimy / 2.0f, -dimz / 2.0f}, false);
}

void FlatRailShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void FlatRailShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

