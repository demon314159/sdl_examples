//
// table.cpp
//

#include "table.h"
#include "plane_shape.h"
#include "cube_shape.h"
#include "cylinder_shape.h"
#include "ring_shape.h"
#include "top_panel_shape.h"
#include "bottom_panel_shape.h"

#include "rollover.h"
#include "straight_wire_guide.h"


#include <stdio.h>

Table::Table()
    : m_ball_z_limit(0.0)
    , m_ball_home_position({0.0, 0.0})
    , m_strip1(NULL)
    , m_strip2(NULL)
    , m_strip3(NULL)
    , m_strip4(NULL)
    , m_strip5(NULL)
    , m_strip6(NULL)
    , m_strip7(NULL)
    , m_strip8(NULL)
    , m_strip9(NULL)
    , m_strip10(NULL)
    , m_strip11(NULL)
    , m_ring1(NULL)
    , m_wire_guide1(NULL)
    , m_wire_guide2(NULL)
    , m_wire_guide3(NULL)
    , m_wire_guide35(NULL)
    , m_wire_guide4(NULL)
    , m_wire_guide45(NULL)
    , m_wire_guide5(NULL)
    , m_wire_guide6(NULL)
    , m_wire_guide7(NULL)
    , m_wire_guide8(NULL)
    , m_lane_guide1(NULL)
    , m_lane_guide2(NULL)
    , m_lane_guide3(NULL)
    , m_lane_guide4(NULL)
    , m_lane_guide5(NULL)
    , m_lane_guide6(NULL)
    , m_three_post1(NULL)
    , m_three_post2(NULL)
    , m_three_post3(NULL)
    , m_three_post4(NULL)
    , m_three_post5(NULL)
    , m_three_post6(NULL)
    , m_two_post1(NULL)
    , m_two_post2(NULL)
    , m_two_post3(NULL)
{
    m_ball_home_position = {(X7 + X8) / 2.0f, Z7 - BALL_RADIUS};
    m_ball_z_limit = Z8;
    m_strip1 = new StraightStrip(90.0, {X8, Y1 / 2.0f, (Z7 + Z4) / 2.0f}, Z7 - Z4, Y1, WOOD_COLOR, 0.2);
    m_strip2 = new StraightStrip(-90.0, {X7, Y1 / 2.0f, (Z3 + Z7) / 2.0f}, Z7 - Z3, Y1, WOOD_COLOR, 0.2);
    m_strip3 = new StraightStrip(90.0, {X6, Y1 / 2.0f, (Z3 + Z5) / 2.0f}, Z5 - Z3, Y1, WOOD_COLOR, 0.2);
    m_strip4 = new StraightStrip(0.0, {X6 + T1 / 2.0f, Y1 / 2.0f, Z3}, T1, Y1, WOOD_COLOR, 0.2);
    m_strip5 = new StraightStrip(ANGLE3, {(float) (X5 + X6) / 2.0f, (float) Y1 / 2.0f, (float) (Z5 + Z6) / 2.0f}, (float) R2, (float) Y1, WOOD_COLOR, (float) 0.2);
    m_strip6 = new StraightStrip(-ANGLE3, {(X1 + X3) / 2.0f, Y1 / 2.0f, (Z5 + Z6) / 2.0f}, R2, Y1, WOOD_COLOR, 0.2);
    m_strip7 = new StraightStrip(-90.0, {X1, Y1 / 2.0f, (ZA + Z5) / 2.0f}, (Z5 - ZA), Y1, WOOD_COLOR, 0.2);
    m_strip8 = new StraightStrip(ANGLE4 - 180.0, {(X1 + X2) / 2.0f, Y1 / 2.0f, (ZA + Z2) / 2.0f}, R4, Y1, WOOD_COLOR, 0.2);
    m_strip9 = new ConcaveStrip(ANGLE1, ANGLE2, {X4, Y1 / 2.0f, Z4}, R1, Y1, WOOD_COLOR, 0.2, TOP_PANEL_STEPS);
    m_strip10 = new StraightStrip(0.0, {(X7 + X8) / 2.0f, Y1 / 2.0f, Z7}, X8 - X7, Y1, WOOD_COLOR, 0.0);
    m_strip11 = new StraightDiodeStrip(ANGLE6, {XC, Y1 / 2.0f, ZC}, TB, Y1, METAL_COLOR, RING_MAJOR_REFLECTIVITY);
    m_ring1 = new Ring(ANGLE5, {XB, YB / 2.0f, ZB}, YB / 2.0f - TB / 4.0f, YB / 8.0f, TB / 2.0f, RUBBER_COLOR, RING_MAJOR_REFLECTIVITY, RING_MINOR_REFLECTIVITY, RING_SEGMENTS);

    m_wire_guide1 = new StraightWireGuide({0.028, 0.411}, {0.02775, 0.4765}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide2 = new StraightWireGuide({0.262, 0.426}, {0.262, 0.4755}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide3 = new StraightWireGuide({0.02775, 0.479}, {0.029, 0.483}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide35 = new StraightWireGuide({0.029, 0.483}, {0.0865, 0.5195}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide4 = new StraightWireGuide({0.2035, 0.519}, {0.26075, 0.482}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide45 = new StraightWireGuide({0.26075, 0.482}, {0.262, 0.478}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide5 = new StraightWireGuide({0.0485, 0.4135}, {0.0485, 0.463}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide6 = new StraightWireGuide({0.241, 0.4405}, {0.241, 0.4625}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide7 = new StraightWireGuide({0.0835, 0.542}, {0.1255, 0.566}, WIRE_GUIDE_RADIUS, WIRE_GUIDE_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide8 = new StraightWireGuide({0.16475, 0.566}, {0.20725, 0.54125}, WIRE_GUIDE_RADIUS, WIRE_GUIDE_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_lane_guide1 = new PyramidLaneGuide(90.0, {0.185, 0.0, 0.105}, 0.032, BALL_RADIUS, PYRAMID_LANE_GUIDE_WIDTH, PYRAMID_LANE_GUIDE_COLOR, PYRAMID_LANE_GUIDE_MAJOR_REFLECTIVITY, PYRAMID_LANE_GUIDE_MINOR_REFLECTIVITY, PYRAMID_LANE_GUIDE_SEGMENTS);
    m_lane_guide2 = new PyramidLaneGuide(90.0, {0.2115, 0.0, 0.105}, 0.032, BALL_RADIUS, PYRAMID_LANE_GUIDE_WIDTH, PYRAMID_LANE_GUIDE_COLOR, PYRAMID_LANE_GUIDE_MAJOR_REFLECTIVITY, PYRAMID_LANE_GUIDE_MINOR_REFLECTIVITY, PYRAMID_LANE_GUIDE_SEGMENTS);
    m_lane_guide3 = new LaneGuide(90.0, {0.15525, 0.0, 0.10525}, 0.0335, BALL_RADIUS, LANE_GUIDE_WIDTH, LANE_GUIDE_COLOR, LANE_GUIDE_COLOR, LANE_GUIDE_REFLECTIVITY, LANE_GUIDE_SEGMENTS);
    m_lane_guide4 = new LaneGuide(90.0, {0.241, 0.0, 0.1055}, 0.034, BALL_RADIUS, LANE_GUIDE_WIDTH, LANE_GUIDE_COLOR, LANE_GUIDE_COLOR, LANE_GUIDE_REFLECTIVITY, LANE_GUIDE_SEGMENTS);
    m_lane_guide5 = new LaneGuide(90.0, {0.2745, 0.0, 0.1605}, 0.0395, BALL_RADIUS, LANE_GUIDE_WIDTH, LANE_GUIDE_COLOR, LANE_GUIDE_COLOR, LANE_GUIDE_REFLECTIVITY, LANE_GUIDE_SEGMENTS);
    m_lane_guide6 = new LaneGuide(90.0, {0.256, 0.0, 0.249}, 0.039, BALL_RADIUS, LANE_GUIDE_WIDTH, LANE_GUIDE_COLOR, RED_LANE_GUIDE_COLOR, LANE_GUIDE_REFLECTIVITY, LANE_GUIDE_SEGMENTS);
    m_three_post1 = new ThreePost({0.27425, 0.296}, {0.275, 0.39475}, {0.25625, 0.318}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS);
    m_three_post2 = new ThreePost({0.233, 0.435}, {0.2335, 0.469}, {0.2095, 0.48175}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS);
    m_three_post3 = new ThreePost({0.0555, 0.3985}, {0.080, 0.48175}, {0.056, 0.46875}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS);
    m_three_post4 = new ThreePost({0.1715, 0.2135}, {0.1915, 0.22825}, {0.153, 0.246}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS);
    m_three_post5 = new ThreePost({0.078, 0.071}, {0.0945, 0.09075}, {0.017, 0.131}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS);
    m_three_post6 = new ThreePost({0.015, 0.3145}, {0.0265, 0.3605}, {0.015, 0.372}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS);
    m_two_post1 = new TwoPost({0.078, 0.280}, {0.102, 0.26875}, TWO_POST_RADIUS, BALL_RADIUS, TWO_POST_COLOR, TWO_POST_COLOR, TWO_POST_REFLECTIVITY, TWO_POST_SEGMENTS);
    m_two_post2 = new TwoPost({0.015, 0.248}, {0.0255, 0.303}, TWO_POST_RADIUS, BALL_RADIUS, TWO_POST_COLOR, TWO_POST_COLOR, TWO_POST_REFLECTIVITY, TWO_POST_SEGMENTS);
    m_two_post3 = new TwoPost({0.01425, 0.147}, {0.015, 0.2335}, TWO_POST_RADIUS, BALL_RADIUS, TWO_POST_COLOR, TWO_POST_COLOR, TWO_POST_REFLECTIVITY, TWO_POST_SEGMENTS);
}

Table::~Table()
{
    delete m_strip1;
    delete m_strip2;
    delete m_strip3;
    delete m_strip4;
    delete m_strip5;
    delete m_strip6;
    delete m_strip7;
    delete m_strip8;
    delete m_strip9;
    delete m_strip10;
    delete m_strip11;
    delete m_ring1;
    delete m_wire_guide1;
    delete m_wire_guide2;
    delete m_wire_guide3;
    delete m_wire_guide35;
    delete m_wire_guide4;
    delete m_wire_guide45;
    delete m_wire_guide5;
    delete m_wire_guide6;
    delete m_wire_guide7;
    delete m_wire_guide8;
    delete m_lane_guide1;
    delete m_lane_guide2;
    delete m_lane_guide3;
    delete m_lane_guide4;
    delete m_lane_guide5;
    delete m_lane_guide6;
    delete m_three_post1;
    delete m_three_post2;
    delete m_three_post3;
    delete m_three_post4;
    delete m_three_post5;
    delete m_three_post6;
    delete m_two_post1;
    delete m_two_post2;
    delete m_two_post3;
}

float Table::ball_z_limit() const
{
return m_ball_z_limit;
}

Float2 Table::ball_home_position() const
{
    return m_ball_home_position;
}

void Table::collide(Ball* ball) const
{
    m_strip1->collide(ball);
    m_strip2->collide(ball);
    m_strip3->collide(ball);
    m_strip4->collide(ball);
    m_strip5->collide(ball);
    m_strip6->collide(ball);
    m_strip7->collide(ball);
    m_strip8->collide(ball);
    m_strip9->collide(ball);
    m_strip10->collide(ball);
    m_strip11->collide(ball);
    m_ring1->collide(ball);
    m_wire_guide1->collide(ball);
    m_wire_guide2->collide(ball);
    m_wire_guide3->collide(ball);
    m_wire_guide35->collide(ball);
    m_wire_guide4->collide(ball);
    m_wire_guide45->collide(ball);
    m_wire_guide5->collide(ball);
    m_wire_guide6->collide(ball);
    m_wire_guide7->collide(ball);
    m_wire_guide8->collide(ball);
    m_lane_guide1->collide(ball);
    m_lane_guide2->collide(ball);
    m_lane_guide3->collide(ball);
    m_lane_guide4->collide(ball);
    m_lane_guide5->collide(ball);
    m_lane_guide6->collide(ball);
    m_three_post1->collide(ball);
    m_three_post2->collide(ball);
    m_three_post3->collide(ball);
    m_three_post4->collide(ball);
    m_three_post5->collide(ball);
    m_three_post6->collide(ball);
    m_two_post1->collide(ball);
    m_two_post2->collide(ball);
    m_two_post3->collide(ball);
}

CadModel Table::model() const
{
    CadModel mm;
    CadModel top_playfield(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, 1.0), PaintCan(1.0, 1.0, 1.0), 99.0);
    CadModel backlight(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, 0.0), PaintCan(0.0, 0.0, 0.0), 1.0);
    mm.add(backlight, PLAYFIELD_X / 2.0, -PLAYFIELD_Y * 5.0 / 6.0, PLAYFIELD_Z / 2.0);
    mm.add(m_strip1->model(0.0));
    mm.add(m_strip2->model(0.0));
    mm.add(m_strip3->model(0.0));
    mm.add(m_strip4->model(0.0));
    mm.add(m_strip5->model(0.0));
    mm.add(m_strip6->model(0.0));
    mm.add(m_strip7->model(0.0));
    mm.add(m_strip8->model(0.0));
    mm.add(m_strip9->model(0.0));
    mm.add(m_strip10->model(0.0));
    mm.add(m_strip11->model(0.0));
    mm.add(m_ring1->model(0.0));
    CadModel diode(CubeShape(TB, Y1, TC), METAL_COLOR, 0.0);
    CadModel wall(CubeShape(TC, Y1, TB), METAL_COLOR, 0.0);
    diode.translate(0.0, -Y1 / 2.0f, TC / 2.0f);
    diode.rotate_ax(-90.0);
    diode.translate(0.0, Y1 / 2.0, 0.0);
    diode.add(wall, -TB / 2.0f + TC / 2.0f, 0.0, TB / 2.0);
    diode.rotate_ay(ANGLE6);
    mm.add(diode, XC, Y1 / 2.0f, ZC);
    CadModel cap(CylinderShape(T1 / 2.0f, Y1, 50), WOOD_COLOR, 0.0);
    CadModel barrier1(CubeShape(T1, Y1, PLAYFIELD_Z - Z3), WOOD_COLOR, 0.0);
    mm.add(barrier1, X6 + T1 / 2.0f, Y1 / 2.0f, (Z3 + PLAYFIELD_Z) / 2.0f);
    mm.add(cap, X6 + T1 / 2.0f, Y1 / 2.0f, Z3);
    CadModel barrier2(CubeShape(T1, Y1 + PLAYFIELD_Y, PLAYFIELD_Z), WOOD_COLOR, 0.0);
    mm.add(barrier2, X8 + T1 / 2.0, Y1 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z / 2.0);
    mm.add(barrier2, X1 - T1 / 2.0, Y1 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z / 2.0);
    CadModel barrier3(CubeShape(PLAYFIELD_X, Y1 + PLAYFIELD_Y, T1), WOOD_COLOR, 0.0);
    mm.add(barrier3, PLAYFIELD_X / 2.0, Y1 / 2.0 - PLAYFIELD_Y / 2.0, T1 / 2.0);
    mm.add(barrier3, PLAYFIELD_X / 2.0, Y1 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z - T1 / 2.0);
    CadModel under_panel(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z), WOOD_COLOR, 0.0);
    under_panel.rotate_ax(180.0);
    mm.add(under_panel, PLAYFIELD_X / 2.0, -PLAYFIELD_Y, PLAYFIELD_Z / 2.0);
    CadModel top_panel(TopPanelShape(PLAYFIELD_X, R1, ANGLE1, ANGLE2, {X4, Z4}, X1, ZA, TOP_PANEL_STEPS), WOOD_COLOR, 0.0);
    mm.add(top_panel, 0.0, Y1, 0.0);
    CadModel bottom_panel(BottomPanelShape(X1, X3, X5, X6, Z5, Z6, Z9), FACE_PLATE_COLOR, 0.0);
    mm.add(bottom_panel, 0.0, Y1, 0.0);

    Float3 position1 = {0.17275, 0.0, 0.09125};
    Float3 position2 = {0.19825, 0.0, 0.09125};
    Float3 position3 = {0.22475, 0.0, 0.09125};
    Float3 position4 = {0.2725, 0.0, 0.2295};
    Float3 position5 = {0.01675, 0.0, 0.45588};
    Float3 position6 = {0.03825, 0.0, 0.45125};
    Float3 position7 = {0.25125, 0.0, 0.451375};
    Float3 position8 = {0.27275, 0.0, 0.45525};
    float type1_length = 0.0305;
    float type2_length = 0.02125;
    float width = 0.0025;

    Rollover rollover1(90.0, position1, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS);
    Rollover rollover2(90.0, position2, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS);
    Rollover rollover3(90.0, position3, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS);
    Rollover rollover4(90.0, position4, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS);
    Rollover rollover5(90.0, position5, type2_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS);
    Rollover rollover6(90.0, position6, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS);
    Rollover rollover7(90.0, position7, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS);
    Rollover rollover8(90.0, position8, type2_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS);
    mm.add(rollover1.model(0.0), 0.0, 0.0, 0.0);
    mm.add(rollover2.model(0.0), 0.0, 0.0, 0.0);
    mm.add(rollover3.model(0.0), 0.0, 0.0, 0.0);
    mm.add(rollover4.model(0.0), 0.0, 0.0, 0.0);
    mm.add(rollover5.model(0.0), 0.0, 0.0, 0.0);
    mm.add(rollover6.model(0.0), 0.0, 0.0, 0.0);
    mm.add(rollover7.model(0.0), 0.0, 0.0, 0.0);
    mm.add(rollover8.model(0.0), 0.0, 0.0, 0.0);

    mm.add(m_wire_guide1->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_wire_guide2->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_wire_guide3->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_wire_guide35->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_wire_guide4->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_wire_guide45->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_wire_guide5->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_wire_guide6->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_wire_guide7->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_wire_guide8->model(0.0), 0.0, 0.0, 0.0);

    mm.add(m_lane_guide1->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_lane_guide2->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_lane_guide3->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_lane_guide4->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_lane_guide5->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_lane_guide6->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_three_post1->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_three_post2->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_three_post3->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_three_post4->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_three_post5->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_three_post6->model(0.0), 0.0, 0.0, 0.0);

    mm.add(m_two_post1->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_two_post2->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_two_post3->model(0.0), 0.0, 0.0, 0.0);

    mm.add(top_playfield, PLAYFIELD_X / 2.0, 0.0, PLAYFIELD_Z / 2.0);
    return mm;
}

