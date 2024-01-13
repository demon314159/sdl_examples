//
// flipper_model.h
//

#if !defined(_FLIPPER_MODEL_H_)
#define _FLIPPER_MODEL_H_

#include "cad_model.h"

class FlipperModel: public CadModel
{
public:
    FlipperModel(float animation_id,
                 const PaintCan& flipper_color, const PaintCan& bumper_color,
                 float r1, float r2, float length, float height,
                 float bumper_thickness, float bumper_height);
    ~FlipperModel();

private:
};

#endif // _FLIPPER_MODEL_H_
