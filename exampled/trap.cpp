//
// trap.cpp
//

#include "trap.h"
#include "pi.h"
#include <math.h>
#include "cylinder_shape.h"

Trap::Trap(Float2 p1, float radius)
    : m_p1(p1)
    , m_radius(radius)
{
}

Trap::~Trap()
{
}

void Trap::collide(Ball* ball) const
{
    Float2 bp = ball->position();
    float dx = bp.v1 - m_p1.v1;
    float dz = bp.v2 - m_p1.v2;
    float dist = sqrt(dx * dx + dz * dz);
    float ir = m_radius / 5.0;
    if (dist < ir) {
        ball->set_position(m_p1);
        ball->set_velocity({0.0, 0.0});
        ball->set_acceleration({0.0, 0.0});
    } else if (dist < m_radius) {
        float acc = 1.0;
        float ax = -(dx / dist) * acc;
        float az = -(dz / dist) * acc;
        ball->set_acceleration({ax, az});
        Float2 v = ball->velocity();
        float f = 0.99;
        float vx = v.v1 * f;
        float vz = v.v2 * f;

        ball->set_velocity({vx, vz});
    }
}


