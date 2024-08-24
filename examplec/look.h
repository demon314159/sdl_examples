//
// look.h
//

#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

#define BACKGROUND_COLOR PaintCan(0.298, 0.6, 0.749);

class Look
{
public:
    static float cube_dimx;
    static float cube_dimy;
    static float cube_dimz;
    static PaintCan cube_paint();
};

#endif // _LOOK_H_
