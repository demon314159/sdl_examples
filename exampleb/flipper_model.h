//
// flipper_model.h
//

#ifndef _FLIPPER_MODEL_H_
#define _FLIPPER_MODEL_H_

#include "cad_model.h"

class FlipperModel: public CadModel
{
public:
    FlipperModel(float animation_id,
                 const PaintCan& flipper_color, const PaintCan& rubber_color,
                 float r1, float r2, float length, float height,
                 float rubber_thickness, float rubber_height);
    ~FlipperModel();

private:
};

#endif // _FLIPPER_MODEL_H_
