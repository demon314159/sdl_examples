//
// quaternion.cpp
//

#include <cmath>
#include "quaternion.h"
#include "pi.h"

Quaternion::Quaternion(float angle, Float3 axes)
{
    m_q0 = cos(angle / 2.0);
    m_q1 = axes.v1 * sin(angle / 2.0);
    m_q2 = axes.v2 * sin(angle / 2.0);
    m_q3 = axes.v3 * sin(angle / 2.0);
}

Quaternion::~Quaternion()
{
}

Matrix4x4 Quaternion::to_matrix(void) const
{
    Matrix4x4 t;

    t.set(0, 0, m_q0 * m_q0 + m_q1 * m_q1 - m_q2 * m_q2 - m_q3 * m_q3);
    t.set(0, 1, 2.0 * m_q1 * m_q2 - 2.0 * m_q0 * m_q3);
    t.set(0, 2, 2.0 * m_q1 * m_q3 + 2.0 * m_q0 * m_q2);
    t.set(0, 3, 0.0);

    t.set(1, 0, 2.0 * m_q1 * m_q2 + 2.0 * m_q0 * m_q3);
    t.set(1, 1, m_q0 * m_q0 - m_q1 * m_q1 + m_q2 * m_q2 - m_q3 * m_q3);
    t.set(1, 2, 2.0 * m_q2 * m_q3 - 2.0 * m_q0 * m_q1);
    t.set(1, 3, 0.0);

    t.set(2, 0, 2.0 * m_q1 * m_q3 - 2.0 * m_q0 * m_q2);
    t.set(2, 1, 2.0 * m_q2 * m_q3 + 2.0 * m_q0 * m_q1);
    t.set(2, 2, m_q0 * m_q0 - m_q1 * m_q1 - m_q2 * m_q2 + m_q3 * m_q3);
    t.set(2, 3, 0.0);

    t.set(3, 0, 0.0);
    t.set(3, 1, 0.0);
    t.set(3, 2, 0.0);
    t.set(3, 3, 1.0);
    return t;
}


