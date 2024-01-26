//
// quaternion.cpp
//

#include <math.h>
#include "quaternion.h"
#include "pi.h"

Quaternion::Quaternion(float q0, float q1, float q2, float q3)
{
    m_q0 = q0;
    m_q1 = q1;
    m_q2 = q2;
    m_q3 = q3;
}
Quaternion::Quaternion(float angle, Float3 axes)
{
    float tangle = angle * PI / 180.0;
    m_q0 = cos(tangle / 2.0);
    m_q1 = axes.v1 * sin(tangle / 2.0);
    m_q2 = axes.v2 * sin(tangle / 2.0);
    m_q3 = axes.v3 * sin(tangle / 2.0);
}

Quaternion::Quaternion()
{
    m_q0 = 1.0;
    m_q1 = 0.0;
    m_q2 = 0.0;
    m_q3 = 0.0;
}

Quaternion::~Quaternion()
{
}

void Quaternion::normalize()
{
    double mag = sqrt(m_q0 * m_q0 + m_q1 * m_q1 + m_q2 * m_q2 + m_q3 * m_q3);
    m_q0 = m_q0 / mag;
    m_q1 = m_q1 / mag;
    m_q2 = m_q2 / mag;
    m_q3 = m_q3 / mag;
}

Quaternion Quaternion::operator * (const Quaternion& q) const
{
    double t0 = m_q0 * q.m_q0 - m_q1 * q.m_q1 - m_q2 * q.m_q2 - m_q3 * q.m_q3;

    double t1 = m_q0 * q.m_q1 + m_q1 * q.m_q0 - m_q2 * q.m_q3 + m_q3 * q.m_q2;

    double t2 = m_q0 * q.m_q2 + m_q1 * q.m_q3 + m_q2 * q.m_q0 - m_q3 * q.m_q1;

    double t3 = m_q0 * q.m_q3 - m_q1 * q.m_q2 + m_q2 * q.m_q1 + m_q3 * q.m_q0;
    return Quaternion((float) t0, (float) t1, (float) t2, (float) t3);
}

Matrix4x4 Quaternion::rotation_matrix(void) const
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

