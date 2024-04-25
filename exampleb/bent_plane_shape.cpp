//
// bent_plane_shape.cpp
//

#include "bent_plane_shape.h"
#include "pi.h"
#include "math.h"

BentPlaneShape::BentPlaneShape(float dimx, float dimy, float dimz, int steps)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
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

BentPlaneShape::~BentPlaneShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int BentPlaneShape::facets() const
{
    return m_facet_count;
}

Facet BentPlaneShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void BentPlaneShape::define_shape()
{
    for (int i = 0; i < m_steps; i++) {
        az_slice(i);
    }
}

void BentPlaneShape::az_slice(int step)
{
    float daz = 90.0 / (float) m_steps;
    float az1 = daz * (float) step;
    float az2 = daz * (float) (step + 1);
    float z = m_dimz / 2.0;

    float xc = -m_dimx / 2.0;
    float yc = m_dimx / 2.0;
    float ro = m_dimx;
    float ri = m_dimx - m_dimy;
    float x1 = xc + ri * sin(az1 * PI / 180.0);
    float y1 = yc - ri * cos(az1 * PI / 180.0);
    float x2 = xc + ro * sin(az1 * PI / 180.0);
    float y2 = yc - ro * cos(az1 * PI / 180.0);
    float x3 = xc + ro * sin(az2 * PI / 180.0);
    float y3 = yc - ro * cos(az2 * PI / 180.0);
    float x4 = xc + ri * sin(az2 * PI / 180.0);
    float y4 = yc - ri * cos(az2 * PI / 180.0);

    add_face({x1, y1, z}, {x2, y2, z}, {x3, y3, z}, {x4, y4, z}, false);
    add_face({x1, y1, -z}, {x2, y2, -z}, {x3, y3, -z}, {x4, y4, -z}, true);

    add_face({x1, y1, z}, {x4, y4, z}, {x4, y4, -z}, {x1, y1, -z}, false);
    add_face({x2, y2, z}, {x3, y3, z}, {x3, y3, -z}, {x2, y2, -z}, true);

    if (step == 0) {
        add_face({x1, y1, z}, {x2, y2, z}, {x2, y2, -z}, {x1, y1, -z}, true);
    }
    if (step == (m_steps -1)) {
        add_face({x4, y4, z}, {x3, y3, z}, {x3, y3, -z}, {x4, y4, -z}, false);
    }
}


void BentPlaneShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void BentPlaneShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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


