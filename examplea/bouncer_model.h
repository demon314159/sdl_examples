//
// bouncer_model.h
//

#ifndef _BOUNCER_MODEL_H_
#define _BOUNCER_MODEL_H_

#include "cad_model.h"

class BouncerModel: public CadModel
{
public:
    BouncerModel(float animation_id,
                 const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color,
                 float wall_radius, float stem_radius, float wall_height, float stem_height,
                 int steps);
    ~BouncerModel();

private:
};

#endif // _BOUNCER_MODEL_H_
