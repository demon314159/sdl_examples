//
// look.h
//

#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

#define BACKGROUND_COLOR PaintCan(1.0, 0.682, 0.259)
#define MARKER_COLOR PaintCan(0.0, 1.0, 0.0)
#define BRICK_PAINT PaintCan(1.0, 0.0, 0.0)
#define DOOR_PAINT PaintCan(1.0, 1.0, 1.0)
#define WINDOW_PAINT PaintCan(1.0, 1.0, 1.0)
#define GLASS_PAINT PaintCan(0.96, 0.99, 1.0)

#define MARKER_ANIMATION_ID 2.0f
#define GLASS_ANIMATION_ID 99.0f

class Look
{
public:
    static float cube_dimx;
    static float cube_dimy;
    static float cube_dimz;
    static PaintCan cube_paint();
};

#endif // _LOOK_H_
