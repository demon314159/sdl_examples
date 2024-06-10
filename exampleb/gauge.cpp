//
// gauge.cpp
//

#include "gauge.h"
#include "paint_can.h"
#include "plane_shape.h"
#include <math.h>

Gauge::Gauge(const Float2& size, const Float3& position, float texture_id)
    : m_size(size)
    , m_position(position)
    , m_texture_id(texture_id)
    , m_animate()
{
}

Gauge::~Gauge()
{
}

CadModel Gauge::model(float animation_id) const
{
    CadModel mm;

    CadModel gauge(PlaneShape(m_size.v1, m_size.v2, m_texture_id), PaintCan(1.0, 1.0, 1.0), 0.0);

    mm.add(gauge, m_position.v1, m_position.v2, m_position.v3);

    return mm;
}

const float* Gauge::data()
{
    m_animate.unity();
    return m_animate.data();
}
