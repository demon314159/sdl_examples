//
// look.h
//

#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

#define WHITE_COLOR PaintCan(1.0, 1.0, 1.0)

#define PLAYFIELD_X  0.4085f
#define PLAYFIELD_Y  0.030f
#define PLAYFIELD_Z  0.4165f

#define ANIMATION_ID_NORMAL 0.0
#define ANIMATION_ID_LIGHT 1.0
#define ANIMATION_ID_BALL 5.0
#define ANIMATION_ID_TRANSPARENT        99.0
#define ANIMATION_ID_FIXED              100.0

#define TEXTURE_ID_NORMAL      0.0
#define TEXTURE_ID_PLAYFIELD   1.0

#define RUBBER_COLOR PaintCan(0.6667, 0.2471, 0.3490)
#define METAL_COLOR PaintCan(0.42, 0.42, 0.42)
#define WOOD_COLOR PaintCan(0.9137, 0.7566, 0.4823)
#define FACE_PLATE_COLOR PaintCan(1.0, 1.0, 1.0)

#define BALL_RADIUS  0.008f
#define BALL_TOP_COLOR PaintCan(1.0, 0.0, 0.0)
#define BALL_MIDDLE_COLOR PaintCan(1.0, 1.0, 1.0)
#define BALL_BOTTOM_COLOR PaintCan(0.0, 0.0, 1.0)
#define BALL_SEGMENTS 80

#define RED_COLOR PaintCan(1.0, 0.0, 0.0)
#define WHITE_COLOR PaintCan(1.0, 0.0, 0.0)

class Look
{
public:
    static float cube_dimx;
    static float cube_dimy;
    static float cube_dimz;
    static PaintCan cube_paint();
};

#endif // _LOOK_H_
