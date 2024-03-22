//
// ring_model.cpp
//

#include "ring_model.h"
#include "ring_shape.h"
#include <math.h>

RingModel::RingModel(float animation_id, const PaintCan& color, float angle,
                     float outer_radius, float inner_radius, float width, int steps)
{
    CadModel ring(RingShape(outer_radius, inner_radius, width, steps), color, 0.0);
    ring.rotate_ax(90.0);
    ring.rotate_ay(angle - 90.0);
    add(ring, 0.0, outer_radius, 0.0);
}

RingModel::~RingModel()
{
}


