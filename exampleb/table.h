//
// table.h
//

#ifndef _TABLE_H_
#define _TABLE_H_

#include "flat_rail.h"
#include "drop_target.h"
#include "disc_target.h"
#include "bumper.h"
#include "one_post.h"
#include "two_post.h"
#include "three_post.h"
#include "three_post_kicker.h"
#include "lane_guide.h"
#include "pyramid_lane_guide.h"
#include "straight_wire_guide.h"
#include "ring.h"
#include "straight_strip.h"
#include "straight_diode_strip.h"
#include "concave_strip.h"
#include "convex_strip.h"
#include "cad_model.h"
#include "float3.h"
#include "matrix4x4.h"
#include "pi.h"
#include "look.h"
#include <math.h>

class Table
{
public:
    Table();
    ~Table();
    CadModel model() const;
    void collide(Ball* ball) const;
    float ball_z_limit() const;
    Float2 ball_home_position() const;

private:
    float m_ball_z_limit;
    Float2 m_ball_home_position;
    StraightStrip* m_strip1;
    StraightStrip* m_strip2;
    StraightStrip* m_strip3;
    ConvexStrip* m_strip4;
    StraightStrip* m_strip5;
    StraightStrip* m_strip6;
    StraightStrip* m_strip7;
    StraightStrip* m_strip8;
    ConcaveStrip* m_strip9;
    StraightStrip* m_strip10;
    StraightDiodeStrip* m_strip11;
    Ring* m_ring1;
    StraightWireGuide* m_wire_guide1;
    StraightWireGuide* m_wire_guide2;
    StraightWireGuide* m_wire_guide3;
    StraightWireGuide* m_wire_guide35;
    StraightWireGuide* m_wire_guide4;
    StraightWireGuide* m_wire_guide45;
    StraightWireGuide* m_wire_guide5;
    StraightWireGuide* m_wire_guide6;
    StraightWireGuide* m_wire_guide7;
    StraightWireGuide* m_wire_guide8;
    PyramidLaneGuide* m_lane_guide1;
    PyramidLaneGuide* m_lane_guide2;
    LaneGuide* m_lane_guide3;
    LaneGuide* m_lane_guide4;
    LaneGuide* m_lane_guide5;
    LaneGuide* m_lane_guide6;
    ThreePost* m_three_post1;
    ThreePost* m_three_post2;
    ThreePostKicker* m_three_post3;
    ThreePost* m_three_post4;
    ThreePost* m_three_post5;
    ThreePost* m_three_post6;
    TwoPost* m_two_post1;
    TwoPost* m_two_post2;
    TwoPost* m_two_post3;
    Bumper* m_bumper1;
    Bumper* m_bumper2;
    DiscTarget* m_disc_target;
    DropTarget* m_drop_target1;
    DropTarget* m_drop_target2;
    DropTarget* m_drop_target3;
    DropTarget* m_drop_target4;
    DropTarget* m_drop_target5;
    DropTarget* m_drop_target6;
    DropTarget* m_drop_target7;
    DropTarget* m_drop_target8;
    DropTarget* m_drop_target9;
    DropTarget* m_drop_target10;
    DropTarget* m_drop_target11;
    DropTarget* m_drop_target12;
    DropTarget* m_drop_target13;
    DropTarget* m_drop_target14;
    DropTarget* m_drop_target15;
    OnePost* m_one_post1;
    OnePost* m_one_post2;
    FlatRail* m_flat_rail;

    float R1 = 0.148;
    float R2 = 0.145;
    float T1 = 0.010;
    float Y1 = 0.010;
    float ANGLE1 = 0.0;
    float ANGLE2 = 145.452;
    float ANGLE3 = 30.12;
    float ANGLE4 = 59.7693;
    float ANGLE5 = ANGLE2 - 9.0;
    float ANGLE6 = 53.0;
    float X1 =  0.007;
    float X6 = 0.283;
    float X8 = 0.312;
    float Z0 = 0.0;
    float Z1 = T1;
    float ZA = 0.1476 - 0.017;
    float Z3 = 0.164;
    float Z4 = 0.161;
    float Z5 = 0.520;
    float Z7 = 0.57725;
    float Z8 = 0.610;
    int TOP_PANEL_STEPS = 200;
    float X0 = X1 - T1;
    float X3 = X1 + R2 * cos(ANGLE3 * PI / 180.0);
    float X5 = X6 - R2 * cos(ANGLE3 * PI / 180.0);
    float X7 = X6 + T1;
    float X9 = X8 + T1;
    float X4 = X8 - R1;
    float X2 = X4 + R1 * cos(ANGLE2 * PI / 180.0);
    float Z2 = Z4 - R1 * sin(ANGLE2 * PI / 180.0);
    float Z6 = Z5 + R2 * sin(ANGLE3 * PI / 180.0);
    float Z9 = PLAYFIELD_Z - T1;
    float Z10 = PLAYFIELD_Z;
    float R4 = sqrt((X2 - X1) * (X2 - X1) + (ZA - Z2) * (ZA - Z2));
    float TB = (X8 - X7) * 0.7;
    float TDIODE = (X8 - X7) * 1.4;
    float YB = BALL_RADIUS * 2.5 * 1.414;
    float XB = X4 + (R1 - TB / 2.0) * cos(ANGLE5 * PI / 180.0);
    float ZB = Z4 - (R1 - TB / 2.0) * sin(ANGLE5 * PI / 180.0);
    float XC = X4 + (R1 - TB / 2.0) * cos(ANGLE6 * PI / 180.0);
    float ZC = Z4 - (R1 - TB / 2.0) * sin(ANGLE6 * PI / 180.0);
    float TC = TDIODE / 10.0;
};

#endif // _TABLE_H_
