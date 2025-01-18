//
// look.h
//

#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

#define BACKGROUND_COLOR PaintCan(1.0, 0.682, 0.259)
#define MARKER_COLOR PaintCan(0.0, 1.0, 0.0)
#define BRICK_PAINT PaintCan(1.0, 0.0, 0.0)
#define FOUNDATION_PAINT PaintCan(0.8, 0.8, 0.8)
#define DOOR_PAINT PaintCan(1.0, 1.0, 1.0)
#define WINDOW_PAINT PaintCan(1.0, 1.0, 1.0)
#define PANE_PAINT PaintCan(0.25, 0.25, 0.25)
#define TABLE_PAINT PaintCan(0.4, 0.8, 1.0)

#define DEFAULT_ANIMATION_ID 0.0f
#define LIGHT_ANIMATION_ID   1.0f
#define FIXED_ANIMATION_ID   2.0f
#define HIDE_FIXED_ANIMATION_ID 3.0f

#define MARKER_ANIMATION_ID   4.0f
#define BUTTON1_ANIMATION_ID  5.0f
#define BUTTON2_ANIMATION_ID  6.0f
#define BUTTON3_ANIMATION_ID  7.0f
#define BUTTON4_ANIMATION_ID  8.0f
#define BUTTON5_ANIMATION_ID  9.0f
#define BUTTON6_ANIMATION_ID  10.0f
#define BUTTON7_ANIMATION_ID  11.0f
#define BUTTON8_ANIMATION_ID  12.0f
#define BUTTON9_ANIMATION_ID  13.0f
#define BUTTON10_ANIMATION_ID 14.0f
#define BUTTON11_ANIMATION_ID 15.0f
#define TABLE_ANIMATION_ID    16.0f

#define IMAGE1_TEXTURE_ID 1.0f
#define IMAGE2_TEXTURE_ID 2.0f
#define IMAGE3_TEXTURE_ID 3.0f
#define IMAGE4_TEXTURE_ID 4.0f
#define IMAGE5_TEXTURE_ID 5.0f
#define IMAGE6_TEXTURE_ID 6.0f
#define IMAGE7_TEXTURE_ID 7.0f
#define LAMP1_TEXTURE_ID  8.0f
#define LAMP2_TEXTURE_ID  9.0f
#define LAMP3_TEXTURE_ID  10.0f
#define LAMP4_TEXTURE_ID  11.0f
#define LAMP5_TEXTURE_ID  12.0f
#define LAMP6_TEXTURE_ID  13.0f
#define LAMP7_TEXTURE_ID  14.0f
#define LAMP8_TEXTURE_ID  15.0f
#define LAMP9_TEXTURE_ID  16.0f
#define LAMP10_TEXTURE_ID 17.0f

class Look
{
public:
    static float cube_dimx;
    static float cube_dimy;
    static float cube_dimz;
    static PaintCan cube_paint();
};

#endif // _LOOK_H_
