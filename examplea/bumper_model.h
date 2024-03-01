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
                const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color,
                float wall_radius, float stem_radius, float wall_height, float stem_height,
                int steps);
    ~BumperModel();

private:
};

#endif // _BUMPER_MODEL_H_
