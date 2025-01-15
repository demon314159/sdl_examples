//
// table.cpp
//

#include "table.h"
#include "cube_shape.h"
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
}

Table::~Table()
{
}

CadModel Table::model(float animation_id) const
{
    CadModel cm(CubeShape(m_dimx, TABLE_THICKNESS, m_dimz), TABLE_PAINT, animation_id);
    return cm;
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
