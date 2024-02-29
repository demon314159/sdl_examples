//
// look.h
//

#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

#define BODY_COLOR PaintCan(1.0, 1.0, 0.0)
#define BUMPER_COLOR PaintCan(1.0, 0.0, 0.0)
#define BOUNCER_TOP_COLOR PaintCan(0.0, 0.0, 1.0)
#define BOUNCER_MIDDLE_COLOR PaintCan(1.0, 1.0, 1.0)
#define BOUNCER_BOTTOM_COLOR PaintCan(1.0, 0.0, 0.0)

#define BALL_RADIUS 1.0
#define BALL_TOP_COLOR PaintCan(1.0, 0.0, 0.0)
#define BALL_MIDDLE_COLOR PaintCan(1.0, 1.0, 1.0)
#define BALL_BOTTOM_COLOR PaintCan(0.0, 0.0, 1.0)

#define FLIPPER_MAJOR_RADIUS 1.0f
#define FLIPPER_MINOR_RADIUS 0.4f
#define FLIPPER_LENGTH 5.0f
#define FLIPPER_HEIGHT 2.0f
#define FLIPPER_VELOCITY (280.0 * 4.0)

#define BUMPER_THICKNESS 0.2f
#define BUMPER_HEIGHT 1.6f

#define WALL_RADIUS 0.2f
#define WALL_HEIGHT 2.0f

#define BOUNCER_WALL_RADIUS 2.0f
#define BOUNCER_STEM_RADIUS 1.0f
#define BOUNCER_WALL_HEIGHT BUMPER_THICKNESS
#define BOUNCER_STEM_HEIGHT (WALL_HEIGHT / 2.0f)

#define WALL_REFLECTIVITY 0.2f
#define FLIPPER_REFLECTIVITY 0.2f
#define BOUNCER_KICKER_VELOCITY 50.0f

#define WALL_SEGMENTS 50
#define FLIPPER_SEGMENTS 50
#define BOUNCER_SEGMENTS 100
#define BALL_SEGMENTS 50

#endif // _LOOK_H_
