
#ifndef _MOUSE_VECTOR_H_
#define _MOUSE_VECTOR_H_

#include "float3.h"

class MouseVector
{
public:
    MouseVector(Float3 origin, Float3 vector);
    ~MouseVector();
    Float3 origin() const;
    Float3 vector() const;
    void set_new_vector(Float3 origin, Float3 vector);
    void translate(Float3 off);
    void rotate_ax(float deg);
    void rotate_ay(float deg);
    void rotate_az(float deg);
    Float2 position_at_x(float x, float& depth) const;
    Float2 position_at_y(float y, float& depth) const;
    Float2 position_at_z(float z, float& depth) const;

private:
    Float3 m_origin;
    Float3 m_vector;
};

#endif // _MOUSE_VECTOR_H_
