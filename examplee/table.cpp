//
// table.cpp
//

#include "table.h"
#include "plane_shape.h"
#include "look.h"
#include "pi.h"
#include <math.h>

#define TABLE_THICKNESS 0.002

Table::Table(float dimx, float dimy, float dimz)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_base({1,1})
    , m_size({1,1})
    , m_animate()
{
    m_size_vector[0] = 1.0;
    m_size_vector[1] = 1.0;

}

Table::~Table()
{
}

CadModel Table::model(float animation_id) const
{
    CadModel cm;
    CadModel ps(PlaneShape(m_dimx, m_dimz, TABLE_TEXTURE_ID), TABLE_PAINT, animation_id);
    cm.add(ps, 0.0, 0.0, 0.0);
    ps.rotate_ax(180.0);
    cm.add(ps, 0.0, 0.0, 0.0);

    return cm;
}

const float* Table::size_data()
{
    m_size_vector[0] = (float) m_size.v1;
    m_size_vector[1] = (float) m_size.v2;
    return m_size_vector;
}

const float* Table::data()
{
    m_animate.unity();
    float xc = -m_dimx /2.0 + (m_dimx * (float) m_size.v1 / 2.0);
    float zc = m_dimz / 2.0 - (m_dimz * (float) m_size.v2 / 2.0);
    m_animate.translate(xc + m_dimx * (float) m_base.v1, -TABLE_THICKNESS / 2.0 - m_dimy / 2.0, zc + m_dimz * (float) m_base.v2);
    m_animate.stretch((float) m_size.v1, 1.0, (float) m_size.v2);
    return m_animate.data();
}

void Table::change_size(Int2 base, Int2 size)
{
    m_base = base;
    m_size = size;
}

void Table::build_texture(Texture* texture) const
{
    texture->add("p_table.png", "texture8");
}

void Table::build_uniform(Uniform* uniform)
{
    uniform->add("animation_12_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, data());
    uniform->add("table_size", UNIFORM_TYPE_1_FLOAT_VECTOR, 2, size_data());
}

void Table::update_uniform()
{
    data();
    size_data();
}

bool Table::contains(int x, int z) const
{
    if (x < m_base.v1) {
        return false;
    }
    if (x > (m_base.v1 + m_size.v1 - 1)) {
        return false;
    }
    if (z > m_base.v2) {
        return false;
    }
    if ( z < (m_base.v2 - m_size.v2 + 1)) {
        return false;
    }
    return true;
}

