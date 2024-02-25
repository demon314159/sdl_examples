//
// pole_model.h
//

#ifndef _POLE_MODEL_H_
#define _POLE_MODEL_H_

#include "cad_model.h"

class PoleModel: public CadModel
{
public:
    PoleModel(float animation_id,
              const PaintCan& body_color, const PaintCan& bumper_color,
              float radius, float height,
              float bumper_thickness, float bumper_height);
    ~PoleModel();

private:
};

#endif // _POLE_MODEL_H_
