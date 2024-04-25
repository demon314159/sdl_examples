//
// tapered_cube_shape.cpp
//

#include "tapered_cube_shape.h"
#include <cstddef>

TaperedCubeShape::TaperedCubeShape(float dimx, float dimy, float dimz, float left_dx, float right_dx,
                                    float front_dz, float back_dz)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_left_dx(left_dx)
    , m_right_dx(right_dx)
    , m_front_dz(front_dz)
    , m_back_dz(back_dz)
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

TaperedCubeShape::~TaperedCubeShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int TaperedCubeShape::facets() const
{
    return m_facet_count;
}

Facet TaperedCubeShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void TaperedCubeShape::define_shape()
{
    // Bottom face
    float x = m_dimx / 2.0;
    float y = m_dimy / 2.0;
    float z = m_dimz / 2.0;
    add_face({-x, -y, -z}, {-x, -y, z}, {x, -y, z}, {x, -y, -z}, true);
    // Top face
    add_face({-x + m_left_dx, y, -z + m_back_dz}, {-x + m_left_dx, y, z + m_front_dz}, {x + m_right_dx, y, z + m_front_dz}, {x + m_right_dx, y, -z + m_back_dz}, false);
    // Left face
    add_face({-x, -y, -z}, {-x, -y, z}, {-x + m_left_dx, y, z + m_front_dz}, {-x + m_left_dx, y, -z + m_back_dz}, false);
    // Right face
    add_face({x, -y, -z}, {x, -y, z}, {x + m_right_dx, y, z + m_front_dz}, {x + m_right_dx, y, -z + m_back_dz}, true);
    // Front face
    add_face({-x, -y, z}, {x, -y, z}, {x + m_right_dx, y, z + m_front_dz}, {-x + m_left_dx, y, z + m_front_dz}, false);
    // Back face
    add_face({-x, -y, -z}, {x, -y, -z}, {x + m_right_dx, y, -z + m_back_dz}, {-x + m_left_dx, y, -z + m_back_dz}, true);
}

void TaperedCubeShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void TaperedCubeShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

