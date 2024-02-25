//
// look.h
//

#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

#define BODY_COLOR PaintCan(1.0, 1.0, 0.0)
#define BUMPER_COLOR PaintCan(1.0, 0.0, 0.0)

#define BALL_RADIUS 1.0
#define BALL_TOP_COLOR PaintCan(1.0, 0.0, 0.0)
#define BALL_MIDDLE_COLOR PaintCan(1.0, 1.0, 1.0)
#define BALL_BOTTOM_COLOR PaintCan(0.0, 0.0, 1.0)

#define FLIPPER_MAJOR_RADIUS 1.0f
#define FLIPPER_MINOR_RADIUS 0.4f
#define FLIPPER_LENGTH 5.0f
#define FLIPPER_HEIGHT 2.0f

#define BUMPER_RADIUS 2.0f
#define BUMPER_THICKNESS 0.2f
#define BUMPER_HEIGHT 1.6f

#define WALL_RADIUS 0.2f
#define WALL_HEIGHT 2.0f

#define WALL_REFLECTIVITY 0.2f
#define FLIPPER_REFLECTIVITY 0.2f
#define BUMPER_REFLECTIVITY 2.0f

class Look
{
public:
    static float cube_dimx;
    static float cube_dimy;
    static float cube_dimz;
    static PaintCan cube_paint();
};

#endif // _LOOK_H_
