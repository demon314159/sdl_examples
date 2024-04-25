//
// diamond_plane_shape.cpp
//

#include "diamond_plane_shape.h"
#include <cstddef>

DiamondPlaneShape::DiamondPlaneShape(float dimx, float dimy, float dimz, float diamond_dimx, float diamond_dimz)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_diamond_dimx(diamond_dimx)
    , m_diamond_dimz(diamond_dimz)
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

DiamondPlaneShape::~DiamondPlaneShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int DiamondPlaneShape::facets() const
{
    return m_facet_count;
}

Facet DiamondPlaneShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void DiamondPlaneShape::define_shape()
{
    float x = m_dimx / 2.0;
    float y = m_dimy / 2.0;
    float z = m_dimz / 2.0;
    float dx = m_diamond_dimx / 2.0;
    float dz = m_diamond_dimz / 2.0;

    // Top face
    add_face({-x, y, -z}, {-x + dx, y, -z}, {-x + dx, y, z}, {-x, y, z}, true);
    add_face({-x + dx, y, z}, {-x + dx, y, 0.0}, {0.0, y, dz}, {0.0, y, z}, true);
    add_face({-x + dx, y, -z}, {-x + dx, y, 0.0}, {0.0, y, -dz}, {0.0, y, -z}, false);
    add_face({x - dx, y, -z}, {x - dx, y, 0.0}, {0.0, y, -dz}, {0.0, y, -z}, true);
    add_face({x - dx, y, z}, {x - dx, y, 0.0}, {0.0, y, dz}, {0.0, y, z}, false);
    add_face({x, y, -z}, {x - dx, y, -z}, {x - dx, y, z}, {x, y, z}, false);

    // Bottom face
    add_face({-x, -y, -z}, {-x + dx, -y, -z}, {-x + dx, -y, z}, {-x, -y, z}, false);
    add_face({-x + dx, -y, z}, {-x + dx, -y, 0.0}, {0.0, -y, dz}, {0.0, -y, z}, false);
    add_face({-x + dx, -y, -z}, {-x + dx, -y, 0.0}, {0.0, -y, -dz}, {0.0, -y, -z}, true);
    add_face({x - dx, -y, -z}, {x - dx, -y, 0.0}, {0.0, -y, -dz}, {0.0, -y, -z}, false);
    add_face({x - dx, -y, z}, {x - dx, -y, 0.0}, {0.0, -y, dz}, {0.0, -y, z}, true);
    add_face({x, -y, -z}, {x - dx, -y, -z}, {x - dx, -y, z}, {x, -y, z}, true);

    // Left face
    add_face({-x, -y, -z}, {-x, -y, z}, {-x, y, z}, {-x, y, -z}, false);
    // Right face
    add_face({x, -y, -z}, {x, -y, z}, {x, y, z}, {x, y, -z}, true);
    // Front face
    add_face({-x, -y, z}, {x, -y, z}, {x, y, z}, {-x, y, z}, false);
    // Back face
    add_face({-x, -y, -z}, {x, -y, -z}, {x, y, -z}, {-x, y, -z}, true);

    // Inside faces
    add_face({-dx, -y, 0.0}, {0.0, -y, -dz}, {0.0, y, -dz}, {-dx, y, 0.0}, false);
    add_face({-dx, -y, 0.0}, {0.0, -y, dz}, {0.0, y, dz}, {-dx, y, 0.0}, true);
    add_face({dx, -y, 0.0}, {0.0, -y, -dz}, {0.0, y, -dz}, {dx, y, 0.0}, true);
    add_face({dx, -y, 0.0}, {0.0, -y, dz}, {0.0, y, dz}, {dx, y, 0.0}, false);
}

void DiamondPlaneShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void DiamondPlaneShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

