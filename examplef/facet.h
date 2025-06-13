//
// facet.h
//

#ifndef _FACET_H_
#define _FACET_H_

#include "float3.h"

struct Facet {
    float animation_id;
    Float3 v1;
    Float3 v2;
    Float3 v3;
    Float3 color;
    float texture_id;
    Float2 texture_v1;
    Float2 texture_v2;
    Float2 texture_v3;
};

#endif // _FACET_H_
