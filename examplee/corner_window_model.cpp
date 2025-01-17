//
// corner_window_model.cpp
//

#include "corner_window_model.h"
#include "window_model.h"
#include "look.h"

CornerWindowModel::CornerWindowModel(float dimx, float dimy, float dimz, float dimb, int vgrilles, int hgrilles, float animation_id)
{
    WindowModel wm1(dimx, dimy, dimz, dimb, vgrilles, hgrilles, animation_id, false, true);
    WindowModel wm2(dimx, dimy, dimz, dimb, vgrilles, hgrilles, animation_id, true, false);
    wm2.rotate_ay(90.0);
    add(wm1, 0.0, 0.0, 0.0);
    add(wm2, dimx / 2.0 - dimz / 2.0, 0.0, -dimx/ 2.0 + dimz / 2.0);
}

CornerWindowModel::~CornerWindowModel()
{
}



