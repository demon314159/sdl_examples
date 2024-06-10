//
// gauge.cpp
//

#include "gauge.h"
#include "paint_can.h"
#include "plane_shape.h"
#include "cube_shape.h"
#include <math.h>

#define STEPS 81
#define INITIAL_STEP 40

Gauge::Gauge(const Float2& size, const Float3& position, float texture_id)
    : m_size(size)
    , m_position(position)
    , m_texture_id(texture_id)
    , m_step(INITIAL_STEP)
    , m_steps(STEPS)
    , m_low_limit(size.v2 * 0.169f)
    , m_high_limit(size.v2 * 0.59f)
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
    float thick = 0.001;
    CadModel bar(CubeShape(m_size.v1, thick, thick), PaintCan(0.0, 0.0, 0.0), animation_id);

    mm.add(gauge, m_position.v1, m_position.v2, m_position.v3);

    float bar_pos = m_position.v3 - m_size.v2 / 2.0f + m_low_limit;
    mm.add(bar, m_position.v1, m_position.v2 + thick / 2.0, bar_pos);

    return mm;
}

const float* Gauge::data()
{
    m_animate.unity();
    m_animate.translate(0.0, 0.0, strength() * (m_high_limit - m_low_limit));
    return m_animate.data();
}

void Gauge::increment()
{
    if (m_step < (m_steps - 1)) {
        ++m_step;
    }
}

void Gauge::decrement()
{
    if (m_step > 0) {
        --m_step;
    }
}

float Gauge::strength() const
{
    return (float) m_step / (float) (m_steps - 1);
}

