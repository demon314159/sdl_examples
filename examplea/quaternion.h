//
// quaternion.h
//

#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "matrix4x4.h"
#include "float3.h"

class Quaternion
{
public:
    Quaternion(float angle, Float3 axes);
    ~Quaternion();
    Matrix4x4 to_matrix() const;

protected:
    float m_q0;
    float m_q1;
    float m_q2;
    float m_q3;
};

#endif // _QUATERNION_H_

