//
// bumper_model.h
//

#ifndef _BUMPER_MODEL_H_
#define _BUMPER_MODEL_H_

#include "cad_model.h"

class BumperModel: public CadModel
{
public:
    BumperModel(float animation_id,
                 const PaintCan& body_color, const PaintCan& bumper_color,
                 float radius, float height,
                 float bumper_thickness, float bumper_height);
    ~BumperModel();

private:
};

#endif // _BUMPER_MODEL_H_
