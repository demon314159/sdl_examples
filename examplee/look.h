//
// look.h
//

#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

#define BACKGROUND_COLOR PaintCan(0.5, 0.5, 0.5)
#define BRICK_PAINT PaintCan(1.0, 0.0, 0.0)

class Look
{
public:
    static float cube_dimx;
    static float cube_dimy;
    static float cube_dimz;
    static PaintCan cube_paint();
};

#endif // _LOOK_H_
