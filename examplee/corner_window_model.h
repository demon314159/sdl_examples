//
// corner_window_model.h
//

#ifndef _CORNER_WINDOW_MODEL_H_
#define _CORNER_WINDOW_MODEL_H_

#include "cad_model.h"

class CornerWindowModel: public CadModel
{
public:
    CornerWindowModel(float dimx, float dimy, float dimz, float dimb, int vgrilles, int hgrilles, float animation_id = 0.0);
    virtual ~CornerWindowModel();

private:
};

#endif // _CORNER_WINDOW_MODEL_H_
