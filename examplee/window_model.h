//
// window_model.h
//

#ifndef _WINDOW_MODEL_H_
#define _WINDOW_MODEL_H_

#include "cad_model.h"

class WindowModel: public CadModel
{
public:
    WindowModel(float dimx, float dimy, float dimz, float dimb, int vgrilles, int hgrilles,
                float animation_id = 0.0,
                bool no_left_side = false, bool no_right_side = false);
    virtual ~WindowModel();

private:
};

#endif // _WINDOW_MODEL_H_
