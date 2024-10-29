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
        ball->set_acceleration({0.0, 0.0});
        ball->set_velocity({0.0, 0.0});
        ball->set_position(m_p1);
    } else if (dist < m_radius) {
        float vel = 0.1;
        float vx = -(dx / dist) * vel;
        float vz = -(dz / dist) * vel;
        ball->set_acceleration({0.0, 0.0});
        ball->set_velocity({vx, vz});
    }
}


