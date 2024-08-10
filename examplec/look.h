//
// look.h
//

#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

#define WHITE_COLOR PaintCan(1.0, 1.0, 1.0)
#define RED_COLOR PaintCan(1.0, 0.0, 0.0)

class Look
{
public:
    static float cube_dimx;
    static float cube_dimy;
    static float cube_dimz;
    static PaintCan cube_paint();
};

#endif // _LOOK_H_
