//
// table.cpp
//

#include "table.h"
#include "cube_shape.h"
#include "look.h"
#include "pi.h"
#include <math.h>

Table::Table(float dimx, float dimy, float dimz)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_animate()
{
}

Table::~Table()
{
}

CadModel Table::model(float animation_id) const
{
    CadModel cm(CubeShape(m_dimx, m_dimy, m_dimz), TABLE_PAINT, animation_id);
    return cm;
}

const float* Table::data()
{
    m_animate.unity();
    return m_animate.data();
}

