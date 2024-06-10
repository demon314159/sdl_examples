//
// gauge.h
//

#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "cad_model.h"
#include "float3.h"
#include "matrix4x4.h"
#include "quaternion.h"
#include "ball.h"

class Gauge
{
public:
    Gauge(const Float2& size, const Float3& position, float texture_id);
    ~Gauge();

    CadModel model(float animation_id) const;
    const float* data();

private:
    Float2 m_size;
    Float3 m_position;
    float m_texture_id;
    Matrix4x4 m_animate;
};

#endif // _GAUGE_H_
