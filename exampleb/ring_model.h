//
// ring_model.h
//

#ifndef _RING_MODEL_H_
#define _RING_MODEL_H_

#include "cad_model.h"

class RingModel: public CadModel
{
public:
    RingModel(float animation_id, const PaintCan& color, float angle, float outer_radius, float inner_radius,
              float width, int steps);
    ~RingModel();

private:
};

#endif // _RING_MODEL_H_
