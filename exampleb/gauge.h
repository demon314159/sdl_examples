//
// gauge.h
//

#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "cad_model.h"
#include "matrix4x4.h"

class Gauge
{
public:
    Gauge(const Float2& size, const Float3& position, float texture_id, int players);
    Gauge(const Gauge&) = delete;
    ~Gauge();

    CadModel model(float animation_id) const;
    const float* data();

    void set_player(int player);
    void increment();
    void decrement();
    float strength() const;

private:
    Float2 m_size;
    Float3 m_position;
    float m_texture_id;
    int m_players;
    int m_player;
    int* m_step;
    int m_steps;
    float m_low_limit;
    float m_high_limit;
    Matrix4x4 m_animate;
};

#endif // _GAUGE_H_
