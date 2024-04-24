//
// rounded_plane_shape.cpp
//

#include "rounded_plane_shape.h"
#include "pi.h"
#include "math.h"

RoundedPlaneShape::RoundedPlaneShape(float dimx, float dimy, float dimz, float left_bend_radius, float right_bend_radius, int steps)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_left_bend_radius(left_bend_radius)
    , m_right_bend_radius(right_bend_radius)
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

RoundedPlaneShape::~RoundedPlaneShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int RoundedPlaneShape::facets() const
{
    return m_facet_count;
}

Facet RoundedPlaneShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void RoundedPlaneShape::define_shape()
{
    float x1 = -(m_dimx / 2.0 - m_left_bend_radius);
    float x2 = m_dimx / 2.0 - m_right_bend_radius;
    float z1 = -m_dimz / 2.0;
    float z2 = m_dimz / 2.0;
    float y1 = -m_dimy / 2.0;
    float y2 = m_dimy / 2.0;

    // Top and bottom face
    add_face({x1, y2, z1}, {x2, y2, z1}, {x2, y2, z2}, {x1, y2, z2}, true);
    add_face({x1, y1, z1}, {x2, y1, z1}, {x2, y1, z2}, {x1, y1, z2}, false);
    // Front and back
    add_face({x1, y1, z1}, {x2, y1, z1}, {x2, y2, z1}, {x1, y2, z1}, true);
    add_face({x1, y1, z2}, {x2, y1, z2}, {x2, y2, z2}, {x1, y2, z2}, false);
    if (m_left_bend_radius > 0.0) {
        float x0 = -m_dimx / 2.0;
        float za = -(m_dimz / 2.0 - m_left_bend_radius);
        float zb = m_dimz / 2.0 - m_left_bend_radius;
        // Top and bottom face of left patch
        add_face({x0, y2, za}, {x1, y2, za}, {x1, y2, zb}, {x0, y2, zb}, true);
        add_face({x0, y1, za}, {x1, y1, za}, {x1, y1, zb}, {x0, y1, zb}, false);
        // Left face of left patch
        add_face({x0, y1, za}, {x0, y2, za}, {x0, y2, zb}, {x0, y1, zb}, true);
        // Front left round
        add_round(x1, za, m_left_bend_radius, -90.0, -180.0);
        // Back left round
        add_round(x1, zb, m_left_bend_radius, -180.0, -270.0);
    } else {
        // Left face when there is no left patch
        add_face({x1, y1, z1}, {x1, y2, z1}, {x1, y2, z2}, {x1, y1, z2}, true);
    }
    if (m_right_bend_radius > 0.0) {
        float x3 = m_dimx / 2.0;
        float za = -(m_dimz / 2.0 - m_right_bend_radius);
        float zb = m_dimz / 2.0 - m_right_bend_radius;
        // Top and bottom face of right patch
        add_face({x2, y2, za}, {x3, y2, za}, {x3, y2, zb}, {x2, y2, zb}, true);
        add_face({x2, y1, za}, {x3, y1, za}, {x3, y1, zb}, {x2, y1, zb}, false);
        // Right face of right patch
        add_face({x3, y1, za}, {x3, y2, za}, {x3, y2, zb}, {x3, y1, zb}, false);
        // Front right round
        add_round(x2, za, m_right_bend_radius, 0.0, -90.0);
        // Back right round
        add_round(x2, zb, m_right_bend_radius, -270.0, -360.0);
    } else {
        // Right face when there is no right patch
        add_face({x2, y1, z1}, {x2, y2, z1}, {x2, y2, z2}, {x2, y1, z2}, false);
    }
}

void RoundedPlaneShape::add_round(float xc, float zc, float radius, float angle_i, float angle_f)
{
    float da = (angle_f - angle_i) / (float) m_steps;
    for (int i = 0; i < m_steps; i++) {
        float a1 = angle_i + da * (float) i;
        float a2 = angle_i + da * (float) (i + 1);
        float x1 = xc + radius * cos(a1 * PI / 180.0);
        float z1 = zc + radius * sin(a1 * PI / 180.0);
        float x2 = xc + radius * cos(a2 * PI / 180.0);
        float z2 = zc + radius * sin(a2 * PI / 180.0);
        float y = m_dimy / 2.0;
        // Top and bottom pie slice
        add_face({x1, y, z1}, {x2, y, z2}, {xc, y, zc}, false);
        add_face({x1, -y, z1}, {x2, -y, z2}, {xc, -y, zc}, true);
        // Outer face
        add_face({x1, -y, z1}, {x1, y, z1}, {x2, y, z2}, {x2, -y, z2}, true);
    }
}


#ifdef NEVERMORE
void RoundedCubeShape::ay_slice(int step)
{
    double day = 90.0 / (float) m_steps;
    float ay1 = day * (float) step;
    float ay2 = day * (float) (step + 1);

    float br = m_bend_radius;

    float y1 = -m_dimy / 2.0 + br;
    float y2 = m_dimy / 2.0 - br;
    float x1 = m_dimx / 2.0 - br + br * cos(ay1 * PI / 180.0);
    float z1 = m_dimz / 2.0 - br + br * sin(ay1 * PI / 180.0);
    float x2 = m_dimx / 2.0 - br + br * cos(ay2 * PI / 180.0);
    float z2 = m_dimz / 2.0 - br + br * sin(ay2 * PI / 180.0);
    // Four edges
    add_face({x1, y1, z1}, {x2, y1, z2}, {x2, y2, z2}, {x1, y2, z1}, true);
    add_face({x1, y1, -z1}, {x2, y1, -z2}, {x2, y2, -z2}, {x1, y2, -z1}, false);
    add_face({-x1, y1, z1}, {-x2, y1, z2}, {-x2, y2, z2}, {-x1, y2, z1}, false);
    add_face({-x1, y1, -z1}, {-x2, y1, -z2}, {-x2, y2, -z2}, {-x1, y2, -z1}, true);
    for (int i = 0; i < m_steps; i++) {
        bend_slice(i, ay1, ay2, true);   // top
        bend_slice(i, ay1, ay2, false);  // bottom
    }
}

void RoundedCubeShape::bend_slice(int step, float ay1, float ay2, bool top)
{
    double da = 90.0 / (float) m_steps;
    float a1 = da * (float) step;
    float a2 = da * (float) (step + 1);

    float br = m_bend_radius;
    float x1 = br * cos(a1 * PI / 180.0);
    float y1 = br * sin(a1 * PI / 180.0);
    float x2 = br * cos(a2 * PI / 180.0);
    float y2 = br * sin(a2 * PI / 180.0);
    float dx = m_dimx / 2.0 - br;
    float dy = m_dimy / 2.0 - br;
    float dz = m_dimz / 2.0 - br;
    if (!top) {
        y1 = -y1;
        y2 = -y2;
        dy = -dy;
    }

    Float3 p1 = {x1, y1, 0.0};
    Float3 p2 = {x2, y2, 0.0};
    Float3 p3 = {x2, y2, 0.0};
    Float3 p4 = {x1, y1, 0.0};

    Float3 pp1 = rotated(p1, ay1);
    Float3 pp2 = rotated(p2, ay1);
    Float3 pp3 = rotated(p3, ay2);
    Float3 pp4 = rotated(p4, ay2);

    Float3 ppp1 = translated(pp1, {dx, dy, dz});
    Float3 ppp2 = translated(pp2, {dx, dy, dz});
    Float3 ppp3 = translated(pp3, {dx, dy, dz});
    Float3 ppp4 = translated(pp4, {dx, dy, dz});
    add_face(ppp1, ppp2, ppp3, ppp4, !top);

    pp1 = rotated(p1, ay1 - 90.0);
    pp2 = rotated(p2, ay1 - 90.0);
    pp3 = rotated(p3, ay2 - 90.0);
    pp4 = rotated(p4, ay2 - 90.0);
    ppp1 = translated(pp1, {dx, dy, -dz});
    ppp2 = translated(pp2, {dx, dy, -dz});
    ppp3 = translated(pp3, {dx, dy, -dz});
    ppp4 = translated(pp4, {dx, dy, -dz});
    add_face(ppp1, ppp2, ppp3, ppp4, !top);

    pp1 = rotated(p1, ay1 - 180.0);
    pp2 = rotated(p2, ay1 - 180.0);
    pp3 = rotated(p3, ay2 - 180.0);
    pp4 = rotated(p4, ay2 - 180.0);
    ppp1 = translated(pp1, {-dx, dy, -dz});
    ppp2 = translated(pp2, {-dx, dy, -dz});
    ppp3 = translated(pp3, {-dx, dy, -dz});
    ppp4 = translated(pp4, {-dx, dy, -dz});
    add_face(ppp1, ppp2, ppp3, ppp4, !top);

    pp1 = rotated(p1, ay1 - 270.0);
    pp2 = rotated(p2, ay1 - 270.0);
    pp3 = rotated(p3, ay2 - 270.0);
    pp4 = rotated(p4, ay2 - 270.0);
    ppp1 = translated(pp1, {-dx, dy, dz});
    ppp2 = translated(pp2, {-dx, dy, dz});
    ppp3 = translated(pp3, {-dx, dy, dz});
    ppp4 = translated(pp4, {-dx, dy, dz});
    add_face(ppp1, ppp2, ppp3, ppp4, !top);


}

void RoundedCubeShape::ax_slice(int step)
{
    double dax = 90.0 / (float) m_steps;
    float ax1 = dax * (float) step;
    float ax2 = dax * (float) (step + 1);

    float br = m_bend_radius;

    float x1 = -m_dimx / 2.0 + br;
    float x2 = m_dimx / 2.0 - br;
    float z1 = m_dimz / 2.0 - br + br * cos(ax1 * PI / 180.0);
    float y1 = m_dimy / 2.0 - br + br * sin(ax1 * PI / 180.0);
    float z2 = m_dimz / 2.0 - br + br * cos(ax2 * PI / 180.0);
    float y2 = m_dimy / 2.0 - br + br * sin(ax2 * PI / 180.0);
    add_face({x1, y1, z1}, {x2, y1, z1}, {x2, y2, z2}, {x1, y2, z2}, false);
    add_face({x1, -y1, z1}, {x2, -y1, z1}, {x2, -y2, z2}, {x1, -y2, z2}, true);
    add_face({x1, y1, -z1}, {x2, y1, -z1}, {x2, y2, -z2}, {x1, y2, -z2}, true);
    add_face({x1, -y1, -z1}, {x2, -y1, -z1}, {x2, -y2, -z2}, {x1, -y2, -z2}, false);
}

void RoundedCubeShape::az_slice(int step)
{
    double daz = 90.0 / (float) m_steps;
    float az1 = daz * (float) step;
    float az2 = daz * (float) (step + 1);

    float br = m_bend_radius;

    float z1 = -m_dimz / 2.0 + br;
    float z2 = m_dimz / 2.0 - br;
    float x1 = m_dimx / 2.0 - br + br * cos(az1 * PI / 180.0);
    float y1 = m_dimy / 2.0 - br + br * sin(az1 * PI / 180.0);
    float x2 = m_dimx / 2.0 - br + br * cos(az2 * PI / 180.0);
    float y2 = m_dimy / 2.0 - br + br * sin(az2 * PI / 180.0);
    add_face({x1, y1, z1}, {x1, y1, z2}, {x2, y2, z2}, {x2, y2, z1}, true);
    add_face({x1, -y1, z1}, {x1, -y1, z2}, {x2, -y2, z2}, {x2, -y2, z1}, false);
    add_face({-x1, y1, z1}, {-x1, y1, z2}, {-x2, y2, z2}, {-x2, y2, z1}, false);
    add_face({-x1, -y1, z1}, {-x1, -y1, z2}, {-x2, -y2, z2}, {-x2, -y2, z1}, true);
}


Float3 RoundedCubeShape::rotated(Float3 point, float angle) const
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * point.v1 + sint * point.v3;
    float ty = point.v2;
    float tz = -sint * point.v1 + cost * point.v3;
    Float3 p = {tx, ty, -tz};
    return p;
}

Float3 RoundedCubeShape::translated(Float3 point, Float3 distance) const
{
    Float3 p = point;
    p.v1 += distance.v1;
    p.v2 += distance.v2;
    p.v3 += distance.v3;
    return p;
}
#endif

void RoundedPlaneShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void RoundedPlaneShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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


