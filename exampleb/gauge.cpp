//
// gauge.cpp
//

#include "gauge.h"
#include "paint_can.h"
#include "plane_shape.h"
#include "cube_shape.h"
#include <math.h>

#define STEPS 31
#define INITIAL_STEP 16

Gauge::Gauge(const Float2& size, const Float3& position, float texture_id, int players)
    : m_size(size)
    , m_position(position)
    , m_texture_id(texture_id)
    , m_players(players)
    , m_player(0)
    , m_step(new int[players + 1])
    , m_steps(STEPS)
    , m_low_limit(size.v2 * 0.169f)
    , m_high_limit(size.v2 * 0.59f)
    , m_animate()
{
    for (int i = 0; i <= players; i++) {
        m_step[i] = INITIAL_STEP;
    }
}

Gauge::~Gauge()
{
    delete [] m_step;
}

void Gauge::set_player(int player)
{
    if (player == 0) {
        for (int i = 0; i <= m_players; i++) {
            m_step[i] = INITIAL_STEP;
        }
    }
    m_player = player;
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
    if (m_step[m_player] < (m_steps - 1)) {
        ++m_step[m_player];
    }
}

void Gauge::decrement()
{
    if (m_step[m_player] > 0) {
        --m_step[m_player];
    }
}

float Gauge::strength() const
{
    return (float) m_step[m_player] / (float) (m_steps - 1);
}

