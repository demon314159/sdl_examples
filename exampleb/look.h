//
// look.h
//

#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

#define PLAYFIELD_X  317.56f
#define PLAYFIELD_Y  4.0f
#define PLAYFIELD_Z  557.50f

#define LAMP_SIZE {30.0, 30.0}
#define LAMP28_ID  128.0f
#define LAMP28_POSITION {145.0, -PLAYFIELD_Y / 3.0, 308.0}
#define LAMP28_ON_COLOR {1.0, 1.0, 0.0}
#define LAMP28_OFF_COLOR {0.5, 0.5, 0.5}


class Look
{
public:
    static float cube_dimx;
    static float cube_dimy;
    static float cube_dimz;
    static PaintCan cube_paint();
};

#endif // _LOOK_H_
