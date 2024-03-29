//
// look.h
//

#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

#define ANIMATION_MATRICES 4
#define ANIMATION_ID_0 2.0
#define ANIMATION_ID_1 3.0
#define ANIMATION_ID_2 4.0
#define ANIMATION_ID_3 5.0

#define PLAYFIELD_X  0.320675f
#define PLAYFIELD_Y  0.006f
#define PLAYFIELD_Z  0.663927777f

#define LAMP_SIZE {0.020, 0.030}

#define WOOD_COLOR PaintCan(0.9137, 0.7566, 0.4823)
#define FACE_PLATE_COLOR PaintCan(1.0, 1.0, 1.0)

#define LAMP28_IX  0
#define LAMP8_IX   1
#define LAMP10_IX  2
#define LAMP9_IX   3
#define LAMP11_IX  4
#define LAMP12_IX  5
#define LAMP14_IX  6
#define LAMP13_IX  7
#define LAMP15_IX  8
#define LAMP16_IX  9
#define LAMP18_IX  10
#define LAMP23_IX  11
#define LAMP21_IX  12
#define LAMP22_IX  13
#define LAMP27_IX  14
#define LAMP25_IX  15
#define LAMP26_IX  16
#define LAMP24_IX  17

#define LAMP4_IX   18
#define LAMP20_IX  19
#define LAMP19_IX  20

#define LAMP_Y_POSITION (-PLAYFIELD_Y / 6.0)

#define LAMP4_POSITION  {0.14625, LAMP_Y_POSITION, 0.56175}
#define LAMP8_POSITION  {0.1585, LAMP_Y_POSITION,  0.3680}
#define LAMP9_POSITION  {0.1515, LAMP_Y_POSITION,  0.4315}
#define LAMP10_POSITION {0.1550, LAMP_Y_POSITION,  0.4000}
#define LAMP11_POSITION {0.14825, LAMP_Y_POSITION, 0.46325}
#define LAMP12_POSITION {0.14475, LAMP_Y_POSITION, 0.4950}
#define LAMP13_POSITION {0.1785, LAMP_Y_POSITION,  0.4030}
#define LAMP14_POSITION {0.18225, LAMP_Y_POSITION, 0.3710}
#define LAMP15_POSITION {0.17575, LAMP_Y_POSITION, 0.43425}
#define LAMP16_POSITION {0.1720, LAMP_Y_POSITION,  0.4660}
#define LAMP18_POSITION {0.1685, LAMP_Y_POSITION,  0.4970}
#define LAMP19_POSITION {0.2730, LAMP_Y_POSITION,  0.1910}
#define LAMP20_POSITION {0.2485, LAMP_Y_POSITION,  0.1350}
#define LAMP21_POSITION {0.19825, LAMP_Y_POSITION, 0.05425}
#define LAMP22_POSITION {0.22525, LAMP_Y_POSITION, 0.05425}
#define LAMP23_POSITION {0.17325, LAMP_Y_POSITION, 0.05425}
#define LAMP24_POSITION {0.2720, LAMP_Y_POSITION,  0.4220}
#define LAMP25_POSITION {0.0380, LAMP_Y_POSITION,  0.4140}
#define LAMP26_POSITION {0.25125, LAMP_Y_POSITION, 0.4140}
#define LAMP27_POSITION {0.0165, LAMP_Y_POSITION,  0.4220}
#define LAMP28_POSITION {0.1455, LAMP_Y_POSITION,  0.3365}

#define TYPE1_ON_COLOR {1.0, 1.0, 1.0}
#define TYPE1_OFF_COLOR {0.4, 0.4, 0.4}

#define TYPE2_ON_COLOR {1.0, 1.0, 0.0}
#define TYPE2_OFF_COLOR {0.4, 0.4, 0.0}

#define TYPE3_ON_COLOR {0.0, 1.0, 0.0}
#define TYPE3_OFF_COLOR {0.0, 0.4, 0.0}

#define TYPE4_ON_COLOR {1.0, 0.624, 0.842}
#define TYPE4_OFF_COLOR {0.5216, 0.3255, 0.4392}

#define TYPE5_ON_COLOR {1.0, 0.0, 0.0}
#define TYPE5_OFF_COLOR {0.5, 0.0, 0.0}

#define FLIPPER_CLEARANCE 0.002f

#define TOP_FLIPPER_SEGMENTS 50
#define TOP_FLIPPER_ANGLE (180.0f + 64.0f)
#define TOP_FLIPPER_POSITION {0.1615, TOP_FLIPPER_HEIGHT / 2.0 + FLIPPER_CLEARANCE, 0.2025}
#define TOP_FLIPPER_HEIGHT 0.016
#define TOP_FLIPPER_LENGTH 0.027f
#define TOP_FLIPPER_MAJOR_RADIUS 0.005f
#define TOP_FLIPPER_MINOR_RADIUS 0.002f
#define TOP_FLIPPER_TRAVEL 40.0
#define TOP_FLIPPER_SPEED (1.0f * 1120.0f)
#define TOP_FLIPPER_REFLECTIVITY 0.2f

#define BOTTOM_FLIPPER_SEGMENTS 50
#define BOTTOM_FLIPPER_ANGLE 26.0f
#define BOTTOM_FLIPPER_HEIGHT 0.016
#define LEFT_FLIPPER_ANGLE -BOTTOM_FLIPPER_ANGLE
#define LEFT_FLIPPER_POSITION {0.088, BOTTOM_FLIPPER_HEIGHT / 2.0 + FLIPPER_CLEARANCE, 0.528}
#define RIGHT_FLIPPER_ANGLE (180.0 + BOTTOM_FLIPPER_ANGLE)
#define RIGHT_FLIPPER_POSITION {0.204, BOTTOM_FLIPPER_HEIGHT / 2.0 + FLIPPER_CLEARANCE, 0.528}
#define BOTTOM_FLIPPER_LENGTH 0.040f
#define BOTTOM_FLIPPER_MAJOR_RADIUS 0.007f
#define BOTTOM_FLIPPER_MINOR_RADIUS 0.003f
#define BOTTOM_FLIPPER_TRAVEL 40.0
#define BOTTOM_FLIPPER_SPEED 1120.0
#define BOTTOM_FLIPPER_REFLECTIVITY 0.2f

#define TOP_FLIPPER_COLOR PaintCan(1.0, 1.0, 1.0)
#define BOTTOM_FLIPPER_COLOR PaintCan(1.0, 1.0, 1.0)
#define RUBBER_COLOR PaintCan(1.0, 0.0, 0.0)
#define RUBBER_THICKNESS 0.002
#define RUBBER_HEIGHT 0.012

#define BALL_RADIUS  0.008f
#define BALL_TOP_COLOR PaintCan(1.0, 0.0, 0.0)
#define BALL_MIDDLE_COLOR PaintCan(1.0, 1.0, 1.0)
#define BALL_BOTTOM_COLOR PaintCan(0.0, 0.0, 1.0)
#define BALL_SEGMENTS 80

#define RING_SEGMENTS 50
#define RING_REFLECTIVITY  0.6

#define ROLLOVER_WIRE_DIAMETER 0.00125
#define ROLLOVER_SEGMENTS 25
#define ROLLOVER_COLOR PaintCan(0.42, 0.42, 0.42)

#define WIRE_GUIDE_DIAMETER 0.002
#define WIRE_GUIDE_SEGMENTS 25
#define WIRE_GUIDE_COLOR PaintCan(0.42, 0.42, 0.42)
#define WIRE_GUIDE_REFLECTIVITY  0.2

#define PYRAMID_LANE_GUIDE_WIDTH 0.010
#define PYRAMID_LANE_GUIDE_SEGMENTS 50
#define PYRAMID_LANE_GUIDE_COLOR PaintCan(1.0, 1.0, 0.0)
#define PYRAMID_LANE_GUIDE_REFLECTIVITY  0.6

#define METAL_COLOR PaintCan(0.42, 0.42, 0.42)

class Look
{
public:
    static float cube_dimx;
    static float cube_dimy;
    static float cube_dimz;
    static PaintCan cube_paint();
};

#endif // _LOOK_H_
