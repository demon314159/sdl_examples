//
// table.h
//

#ifndef _TABLE_H_
#define _TABLE_H_

#include "float3.h"
#include "cad_model.h"
#include "matrix4x4.h"

class Table
{
public:
    Table(float dimx, float dimy, float dimz);
    ~Table();
    CadModel model(float animation_id) const;
    const float* data();

protected:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    Matrix4x4 m_animate;
};

#endif // _TABLE_H_
