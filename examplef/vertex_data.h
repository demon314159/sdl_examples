//
// vertex_data.h
//

#ifndef _VERTEX_DATA_H_
#define _VERTEX_DATA_H_

#include "float3.h"

struct VertexData
{
    Float3 position;
    Float3 normal;
    Float3 color;
    Float2 texture_position;
    float animation_id;
    float texture_id;
};

#endif // _VERTEX_DATA_H_
