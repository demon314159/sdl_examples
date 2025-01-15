//
// table.h
//

#ifndef _TABLE_H_
#define _TABLE_H_

#include "float3.h"
#include "cad_model.h"
#include "matrix4x4.h"
#include "texture.h"

class Table
{
public:
    Table(float dimx, float dimy, float dimz);
    ~Table();
    CadModel model(float animation_id) const;
    const float* data();
    const float* size_data();
    void change_size(Int2 base, Int2 size);
    void build_texture(Texture* texture) const;

protected:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    Int2 m_base;
    Int2 m_size;
    Matrix4x4 m_animate;
    float* m_size_vector;
};

#endif // _TABLE_H_
