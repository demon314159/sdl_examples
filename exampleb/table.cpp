//
// table.cpp
//



#include "gate.h"

#include "rounded_cube_shape.h"
#include "plastic_guide.h"
#include "table.h"
#include "plane_shape.h"
#include "cube_shape.h"
#include "cylinder_shape.h"
#include "ring_shape.h"
#include "top_panel_shape.h"
#include "bottom_panel_shape.h"

#include "straight_wire_guide.h"


#include <stdio.h>

Table::Table()
    : m_ball_z_limit(0.0)
    , m_ball_home_position({0.0, 0.0})
    , m_strip1(NULL)
    , m_strip2a(NULL)
    , m_strip2b(NULL)
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
    , m_bumper1(NULL)
    , m_bumper2(NULL)
    , m_disc_target(NULL)
    , m_one_post1(NULL)
    , m_one_post2(NULL)
    , m_flat_rail(NULL)
    , m_rollover1(NULL)
    , m_rollover2(NULL)
    , m_rollover3(NULL)
    , m_rollover4(NULL)
    , m_rollover5(NULL)
    , m_rollover6(NULL)
    , m_rollover7(NULL)
    , m_rollover8(NULL)
{
    m_ball_home_position = {(X7 + X8) / 2.0f, Z7 - BALL_RADIUS};
    m_ball_z_limit = Z8;
    m_strip1 = new StraightStrip(90.0, {X8, Y1 / 2.0f, (Z7 + Z4) / 2.0f}, Z7 - Z4, Y1, WOOD_COLOR, 0.2);
    m_strip2a = new StraightStrip(-90.0, {X7, Y1 / 2.0f, (Z3 + ZOH1) / 2.0f}, ZOH1 - Z3, Y1, WOOD_COLOR, 0.2);
    m_strip2b = new StraightStrip(-90.0, {X7, Y1 / 2.0f, (ZOH2 + Z7) / 2.0f}, Z7 - ZOH2, Y1, WOOD_COLOR, 0.2);
    m_strip3 = new StraightStrip(90.0, {X6, Y1 / 2.0f, (Z3 + Z5) / 2.0f}, Z5 - Z3, Y1, WOOD_COLOR, 0.2);
    m_strip4 = new ConvexStrip(0.0, 180.0, {X6 + T1 / 2.0f, Y1 / 2.0f, Z3}, T1 / 2.0, Y1, WOOD_COLOR, 0.2, RING_SEGMENTS);
    m_strip5 = new StraightStrip(ANGLE3, {(float) (X5 + X6) / 2.0f, (float) Y2 / 2.0f, (float) (Z5 + Z6) / 2.0f}, (float) R2, (float) Y2, WOOD_COLOR, (float) 0.2);
    m_strip6 = new StraightStrip(-ANGLE3, {(X1 + X3) / 2.0f, Y2 / 2.0f, (Z5 + Z6) / 2.0f}, R2, Y2, WOOD_COLOR, 0.2);
    m_strip7 = new StraightStrip(-90.0, {X1, Y1 / 2.0f, (ZA + Z5) / 2.0f}, (Z5 - ZA), Y1, WOOD_COLOR, 0.2);
    m_strip8 = new StraightStrip({X2, Z2}, {X1, ZA}, Y1, WOOD_COLOR, 0.2);
    m_strip9 = new ConcaveStrip(ANGLE1, ANGLE2, {X4, Y1 / 2.0f, Z4}, R1, Y1, WOOD_COLOR, 0.2, TOP_PANEL_STEPS);
    m_strip10 = new StraightStrip(0.0, {(X7 + X8) / 2.0f, Y1 / 2.0f, Z7}, X8 - X7, Y1, WOOD_COLOR, 0.0);
    m_strip11 = new StraightDiodeStrip(ANGLE6, {XC, Y1 / 2.0f, ZC}, TDIODE, Y1, METAL_COLOR, RING_MAJOR_REFLECTIVITY);
    m_ring1 = new Ring(ANGLE5, {XB, YB / 2.0f, ZB}, YB / 2.0f - TB / 4.0f, YB / 8.0f, TB / 2.0f, RING_COLOR, RING_MAJOR_REFLECTIVITY, RING_MINOR_REFLECTIVITY, RING_SEGMENTS);

    m_wire_guide1 = new StraightWireGuide({0.028, 0.411}, {0.02775, 0.4765}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide2 = new StraightWireGuide({0.262, 0.426}, {0.262, 0.4755}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide3 = new StraightWireGuide({0.02775, 0.479}, {0.029, 0.483}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide35 = new StraightWireGuide({0.029, 0.483}, {0.0865, 0.5195}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);

    m_wire_guide4 = new StraightWireGuide({0.2035, 0.519}, {0.26075, 0.483}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide45 = new StraightWireGuide({0.26075, 0.483}, {0.262, 0.478}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);

    m_wire_guide5 = new StraightWireGuide({0.0485, 0.4135}, {0.0485, 0.463}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide6 = new StraightWireGuide({0.241, 0.4405}, {0.241, 0.4625}, WIRE_GUIDE_RADIUS, BALL_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide7 = new StraightWireGuide({0.0835, 0.542}, {0.1255, 0.566}, WIRE_GUIDE_RADIUS, WIRE_GUIDE_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_wire_guide8 = new StraightWireGuide({0.16475, 0.566}, {0.20725, 0.54125}, WIRE_GUIDE_RADIUS, WIRE_GUIDE_RADIUS, WIRE_GUIDE_COLOR, WIRE_GUIDE_REFLECTIVITY, WIRE_GUIDE_SEGMENTS);
    m_lane_guide1 = new PyramidLaneGuide(90.0, {0.185, 0.0, 0.105}, 0.032, BALL_RADIUS, PYRAMID_LANE_GUIDE_WIDTH, PYRAMID_LANE_GUIDE_COLOR, PYRAMID_LANE_GUIDE_MAJOR_REFLECTIVITY, PYRAMID_LANE_GUIDE_MINOR_REFLECTIVITY, PYRAMID_LANE_GUIDE_SEGMENTS);
    m_lane_guide2 = new PyramidLaneGuide(90.0, {0.2115, 0.0, 0.105}, 0.032, BALL_RADIUS, PYRAMID_LANE_GUIDE_WIDTH, PYRAMID_LANE_GUIDE_COLOR, PYRAMID_LANE_GUIDE_MAJOR_REFLECTIVITY, PYRAMID_LANE_GUIDE_MINOR_REFLECTIVITY, PYRAMID_LANE_GUIDE_SEGMENTS);
    m_lane_guide3 = new LaneGuide(90.0, {0.15525, 0.0, 0.10525}, 0.0335, BALL_RADIUS, LANE_GUIDE_WIDTH, LANE_GUIDE_COLOR, LANE_GUIDE_COLOR, LANE_GUIDE_REFLECTIVITY, LANE_GUIDE_SEGMENTS, 0, 0);
    m_lane_guide4 = new LaneGuide(90.0, {0.241, 0.0, 0.1055}, 0.034, BALL_RADIUS, LANE_GUIDE_WIDTH, LANE_GUIDE_COLOR, LANE_GUIDE_COLOR, LANE_GUIDE_REFLECTIVITY, LANE_GUIDE_SEGMENTS, 0, 0, true);

    // 11 objects that all hit SENSOR_ID_TEN_POINT
    m_lane_guide5 = new LaneGuide(90.0, {0.2745, 0.0, 0.1605}, 0.0395, BALL_RADIUS, LANE_GUIDE_WIDTH, LANE_GUIDE_COLOR, LANE_GUIDE_COLOR, LANE_GUIDE_REFLECTIVITY, LANE_GUIDE_SEGMENTS, SENSOR_ID_TEN_POINT, 1, true, false, true);
    m_lane_guide6 = new LaneGuide(90.0, {0.256, 0.0, 0.249}, 0.039, BALL_RADIUS, LANE_GUIDE_WIDTH, LANE_GUIDE_COLOR, RED_LANE_GUIDE_COLOR, LANE_GUIDE_REFLECTIVITY, LANE_GUIDE_SEGMENTS, SENSOR_ID_TEN_POINT, 1);
    m_three_post1 = new ThreePost({0.27425, 0.296}, {0.275, 0.39475}, {0.25625, 0.318}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS, SENSOR_ID_TEN_POINT, 2);
    m_three_post2 = new ThreePost({0.233, 0.435}, {0.2335, 0.469}, {0.2095, 0.48175}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS, SENSOR_ID_TEN_POINT, 3, false, true, false);
    m_three_post3 = new ThreePostKicker({0.0555, 0.3985}, {0.080, 0.48175}, {0.05625, 0.46875}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_KICKER_VELOCITY, THREE_POST_SEGMENTS, SENSOR_ID_TEN_POINT, 1, false, false, true);
    m_three_post4 = new ThreePost({0.1715, 0.2135}, {0.1915, 0.22825}, {0.153, 0.246}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS, SENSOR_ID_TEN_POINT, 2);
    m_three_post5 = new ThreePost({0.078, 0.071}, {0.0945, 0.09075}, {0.017, 0.131}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS, SENSOR_ID_TEN_POINT, 2);
    m_three_post6 = new ThreePost({0.015, 0.3145}, {0.0265, 0.3605}, {0.015, 0.372}, THREE_POST_RADIUS, BALL_RADIUS, THREE_POST_COLOR, THREE_POST_COLOR, THREE_POST_REFLECTIVITY, THREE_POST_SEGMENTS, SENSOR_ID_TEN_POINT, 1, true, false, true);

    m_two_post1 = new TwoPost({0.078, 0.280}, {0.102, 0.26875}, TWO_POST_RADIUS, BALL_RADIUS, TWO_POST_COLOR, TWO_POST_COLOR, TWO_POST_REFLECTIVITY, TWO_POST_SEGMENTS, SENSOR_ID_TEN_POINT, 2);
    m_two_post2 = new TwoPost({0.015, 0.248}, {0.0255, 0.303}, TWO_POST_RADIUS, BALL_RADIUS, TWO_POST_COLOR, TWO_POST_COLOR, TWO_POST_REFLECTIVITY, TWO_POST_SEGMENTS, SENSOR_ID_TEN_POINT, 1, true, false);
    m_two_post3 = new TwoPost({0.01425, 0.147}, {0.015, 0.2335}, TWO_POST_RADIUS, BALL_RADIUS, TWO_POST_COLOR, TWO_POST_COLOR, TWO_POST_REFLECTIVITY, TWO_POST_SEGMENTS, SENSOR_ID_TEN_POINT, 1);

    m_bumper1 = new Bumper({0.208, 0.166}, BUMPER_RADIUS, BUMPER_KICKER_RADIUS, BUMPER_KICKER_VELOCITY, BALL_RADIUS, BUMPER_COLOR, BUMPER_MAJOR_SEGMENTS, BUMPER_MINOR_SEGMENTS, SENSOR_ID_BUMPER);
    m_bumper2 = new Bumper({0.0735, 0.215}, BUMPER_RADIUS, BUMPER_KICKER_RADIUS, BUMPER_KICKER_VELOCITY, BALL_RADIUS, BUMPER_COLOR, BUMPER_MAJOR_SEGMENTS, BUMPER_MINOR_SEGMENTS, SENSOR_ID_BUMPER);
    m_disc_target = new DiscTarget({0.2565, 0.116}, 160.0, DISC_TARGET_RADIUS, DISC_TARGET_WIDTH, DISC_TARGET_COLOR1, DISC_TARGET_COLOR2, DISC_TARGET_COLOR3, DISC_TARGET_REFLECTIVITY, DISC_TARGET_SEGMENTS, SENSOR_ID_EXTRA_BALL);
    m_one_post1 = new OnePost({0.0105, 0.3965}, ONE_POST_RADIUS, BALL_RADIUS, ONE_POST_COLOR, ONE_POST_REFLECTIVITY, ONE_POST_SEGMENTS);
    m_one_post2 = new OnePost({0.27875, 0.409125}, ONE_POST_RADIUS, BALL_RADIUS, ONE_POST_COLOR, ONE_POST_REFLECTIVITY, ONE_POST_SEGMENTS);
    m_flat_rail = new FlatRail({X6, 0.22885}, FLAT_RAIL_LENGTH, FLAT_RAIL_WIDTH, FLAT_RAIL_THICKNESS, FLAT_RAIL_BEND_RADIUS, Y1, FLAT_RAIL_COLOR, FLAT_RAIL_REFLECTIVITY, FLAT_RAIL_SEGMENTS);

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

    m_rollover1 = new Rollover(90.0, position1, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS, SENSOR_ID_ROLLOVER_A);
    m_rollover2 = new Rollover(90.0, position2, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS, SENSOR_ID_ROLLOVER_B);
    m_rollover3 = new Rollover(90.0, position3, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS, SENSOR_ID_ROLLOVER_C);
    m_rollover4 = new Rollover(90.0, position4, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS, SENSOR_ID_SPECIAL);
    m_rollover5 = new Rollover(90.0, position5, type2_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS, SENSOR_ID_ROLLOVER_A);
    m_rollover6 = new Rollover(90.0, position6, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS, SENSOR_ID_ROLLOVER_B);
    m_rollover7 = new Rollover(90.0, position7, type1_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS, SENSOR_ID_ROLLOVER_B);
    m_rollover8 = new Rollover(90.0, position8, type2_length, width, ROLLOVER_WIRE_DIAMETER, ROLLOVER_COLOR, ROLLOVER_SEGMENTS, SENSOR_ID_ROLLOVER_C);
}

Table::~Table()
{
    delete m_strip1;
    delete m_strip2a;
    delete m_strip2b;
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
    delete m_bumper1;
    delete m_bumper2;
    delete m_disc_target;
    delete m_one_post1;
    delete m_one_post2;
    delete m_flat_rail;
    delete m_rollover1;
    delete m_rollover2;
    delete m_rollover3;
    delete m_rollover4;
    delete m_rollover5;
    delete m_rollover6;
    delete m_rollover7;
    delete m_rollover8;
}

float Table::ball_z_limit() const
{
return m_ball_z_limit;
}

Float2 Table::ball_home_position() const
{
    return m_ball_home_position;
}

Float2 Table::out_hole_position() const
{
    return {X4, Z8};
}

void Table::collide(Ball* ball, Sensor* sensor) const
{
    m_strip1->collide(ball);
    m_strip2a->collide(ball);
    m_strip2b->collide(ball);
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
    m_lane_guide3->collide(ball, sensor);
    m_lane_guide4->collide(ball, sensor);
    m_lane_guide5->collide(ball, sensor);
    m_lane_guide6->collide(ball, sensor);
    m_three_post1->collide(ball, sensor);
    m_three_post2->collide(ball, sensor);
    m_three_post3->collide(ball, sensor);
    m_three_post4->collide(ball, sensor);
    m_three_post5->collide(ball, sensor);
    m_three_post6->collide(ball, sensor);
    m_two_post1->collide(ball, sensor);
    m_two_post2->collide(ball, sensor);
    m_two_post3->collide(ball, sensor);
    m_bumper1->collide(ball, sensor);
    m_bumper2->collide(ball, sensor);
    m_disc_target->collide(ball, sensor);
    m_one_post1->collide(ball);
    m_one_post2->collide(ball);
    m_flat_rail->collide(ball);
    m_rollover1->collide(ball, sensor);
    m_rollover2->collide(ball, sensor);
    m_rollover3->collide(ball, sensor);
    m_rollover4->collide(ball, sensor);
    m_rollover5->collide(ball, sensor);
    m_rollover6->collide(ball, sensor);
    m_rollover7->collide(ball, sensor);
    m_rollover8->collide(ball, sensor);
}

CadModel Table::model() const
{
    CadModel mm;
    CadModel top_playfield(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, TEXTURE_ID_PLAYFIELD), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    CadModel backlight(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, 0.0), PaintCan(0.0, 0.0, 0.0), 1.0);
    mm.add(backlight, PLAYFIELD_X / 2.0, -PLAYFIELD_Y * 9.0 / 10.0, PLAYFIELD_Z / 2.0);
    mm.add(m_strip1->model(0.0));
    mm.add(m_strip2a->model(0.0));
    mm.add(m_strip2b->model(0.0));
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
    CadModel diode(CubeShape(TDIODE, Y1, TC), METAL_COLOR, 0.0);
    CadModel wall(CubeShape(TC, Y1, TDIODE), METAL_COLOR, 0.0);
    diode.translate(0.0, -Y1 / 2.0f, TC / 2.0f);
    diode.rotate_ax(-90.0);
    diode.translate(0.0, Y1 / 2.0, 0.0);
//    diode.add(wall, -TDIODE / 2.0f + TC / 2.0f, 0.0, TDIODE / 2.0);
    diode.rotate_ay(ANGLE6);
//    mm.add(diode, XC, Y1 / 2.0f, ZC);

    CadModel barrier1a(CubeShape(T1, Y4, ZOH1 - Z3), WOOD_COLOR, 0.0);
    CadModel barrier1b(CubeShape(T1, Y4, PLAYFIELD_Z - ZOH2), WOOD_COLOR, 0.0);
    mm.add(barrier1a, X6 + T1 / 2.0f, Y4 / 2.0f, (Z3 + ZOH1) / 2.0f);
    mm.add(barrier1b, X6 + T1 / 2.0f, Y4 / 2.0f, (ZOH2 + PLAYFIELD_Z) / 2.0f);

    CadModel cap(CylinderShape(T1 / 2.0f, Y4, 50), WOOD_COLOR, 0.0);
    mm.add(cap, X6 + T1 / 2.0f, Y4 / 2.0f, Z3);

    CadModel barrier2(CubeShape(T1, Y3 + PLAYFIELD_Y, PLAYFIELD_Z), WOOD_COLOR, 0.0);
    mm.add(barrier2, X8 + T1 / 2.0, Y3 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z / 2.0);
    mm.add(barrier2, X1 - T1 / 2.0, Y3 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z / 2.0);
    CadModel barrier3(CubeShape(PLAYFIELD_X, Y3 + PLAYFIELD_Y, T1), WOOD_COLOR, 0.0);
    mm.add(barrier3, PLAYFIELD_X / 2.0, Y3 / 2.0 - PLAYFIELD_Y / 2.0, T1 / 2.0);
    mm.add(barrier3, PLAYFIELD_X / 2.0, Y3 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z - T1 / 2.0);

    CadModel under_panel(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z), WOOD_COLOR, 0.0);
    under_panel.rotate_ax(180.0);
    mm.add(under_panel, PLAYFIELD_X / 2.0, -PLAYFIELD_Y + 0.002, PLAYFIELD_Z / 2.0);
    CadModel top_panel(TopPanelShape(PLAYFIELD_X, R1, ANGLE1, ANGLE2, {X4, Z4}, X1, ZA, TOP_PANEL_STEPS), WOOD_COLOR, 0.0);
    mm.add(top_panel, 0.0, Y1, 0.0);
    CadModel bottom_panel(BottomPanelShape(X1, X3, X5, X6, X7, Z5, Z6, Z9), FACE_PLATE_COLOR, 0.0);
    mm.add(bottom_panel, 0.0, Y2, 0.0);


    mm.add(m_rollover1->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_rollover2->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_rollover3->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_rollover4->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_rollover5->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_rollover6->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_rollover7->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_rollover8->model(0.0), 0.0, 0.0, 0.0);

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

    mm.add(m_bumper1->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_bumper2->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_disc_target->model(0.0), 0.0, 0.0, 0.0);

    mm.add(m_one_post1->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_one_post2->model(0.0), 0.0, 0.0, 0.0);
    mm.add(m_flat_rail->model(0.0), 0.0, 0.0, 0.0);

    mm.add(top_playfield, PLAYFIELD_X / 2.0, 0.0, PLAYFIELD_Z / 2.0);
    //
    PlasticGuide pg({0.141125, 0.105875},
                    {0.0835, 0.030}, {0.106, 0.06525}, {0.03475, 0.06725},
                    {0.1715, 0.21375}, {0.1915, 0.22825}, {0.153, 0.246});
    CadModel plastic1(PlaneShape(pg.blank_size().v1, pg.blank_size().v2, TEXTURE_ID_PLASTIC1), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    plastic1.rotate_ay(pg.blank_angle());
    mm.add(plastic1, pg.blank_position().v1, 1.5 * BALL_RADIUS, pg.blank_position().v2);
    //
    pg = PlasticGuide({0.479, 0.3765},
                      {0.047, 0.0435}, {0.4085, 0.323}, {0.1295, 0.1785},
                      {0.24075, 0.07133}, {0.27425, 0.1605}, {0.24125, 0.10525});
    CadModel plastic2(PlaneShape(pg.blank_size().v1, pg.blank_size().v2, TEXTURE_ID_PLASTIC2), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    plastic2.rotate_ay(pg.blank_angle());
    mm.add(plastic2, pg.blank_position().v1, 1.6 * BALL_RADIUS, pg.blank_position().v2);
    //

    pg = PlasticGuide({0.22575, 0.34675},
                      {0.048, 0.3015}, {0.1785, 0.0465},
                      {0.2095, 0.48175}, {0.233, 0.43475});
    CadModel plastic3(PlaneShape(pg.blank_size().v1, pg.blank_size().v2, TEXTURE_ID_PLASTIC3), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    plastic3.rotate_ay(pg.blank_angle());
    mm.add(plastic3, pg.blank_position().v1, 1.6 * BALL_RADIUS, pg.blank_position().v2);
    //

    pg = PlasticGuide({0.16375, 0.3662},
                      {0.1335, 0.330}, {0.036, 0.032},
                      {0.080, 0.48175}, {0.0555, 0.3985});
    CadModel plastic4(PlaneShape(pg.blank_size().v1, pg.blank_size().v2, TEXTURE_ID_PLASTIC4), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    plastic4.rotate_ay(pg.blank_angle());
    mm.add(plastic4, pg.blank_position().v1, 1.6 * BALL_RADIUS, pg.blank_position().v2);
    //

    pg = PlasticGuide({0.3115, 0.09025},
                      {0.2605, 0.0655}, {0.0235, 0.069}, {0.2105, 0.022},
                      {0.2745, 0.296}, {0.2745, 0.3945}, {0.25625, 0.31775});
    CadModel plastic5(PlaneShape(pg.blank_size().v1, pg.blank_size().v2, TEXTURE_ID_PLASTIC5), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    plastic5.rotate_ay(pg.blank_angle());
    mm.add(plastic5, pg.blank_position().v1, 1.6 * BALL_RADIUS, pg.blank_position().v2);
    //

    pg = PlasticGuide({0.25075, 0.16575},
                      {0.2035, 0.036}, {0.23125, 0.086}, {0.0365, 0.14325},
                      {0.078, 0.071}, {0.0945, 0.091}, {0.01725, 0.13125});
    CadModel plastic7(PlaneShape(pg.blank_size().v1, pg.blank_size().v2, TEXTURE_ID_PLASTIC7), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    plastic7.rotate_ay(pg.blank_angle());
    mm.add(plastic7, pg.blank_position().v1, 1.6 * BALL_RADIUS, pg.blank_position().v2);
    //

    pg = PlasticGuide({0.3245, 0.12625},
                      {0.060, 0.0585}, {0.266, 0.0585},
                      {0.078, 0.27975}, {0.102, 0.26875});
    CadModel plastic8(PlaneShape(pg.blank_size().v1, pg.blank_size().v2, TEXTURE_ID_PLASTIC8), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    plastic8.rotate_ay(pg.blank_angle());
    mm.add(plastic8, pg.blank_position().v1, 1.6 * BALL_RADIUS - 0.0005, pg.blank_position().v2);

    // Plastic 6 is a large piece that obscures other, it goes a little higher and last

    pg = PlasticGuide({0.496, 0.39625},
                      {0.473, 0.021}, {0.075, 0.369},
                      {0.01425, 0.147}, {0.0265, 0.3605});
    CadModel plastic6(PlaneShape(pg.blank_size().v1, pg.blank_size().v2, TEXTURE_ID_PLASTIC6), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    plastic6.rotate_ay(pg.blank_angle());
    mm.add(plastic6, pg.blank_position().v1, 1.6 * BALL_RADIUS + 0.0005, pg.blank_position().v2);

    return mm;
}

Float2 Table::trim() const
{
    return {T1, Y4};
}

PaintCan Table::trim_color() const
{
    return WOOD_COLOR;
}
