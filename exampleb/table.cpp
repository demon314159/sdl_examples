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

#include "pipe.h"


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
    m_strip11 = new StraightStrip(ANGLE6, {XC, Y1 / 2.0f, ZC}, TB, Y1, RUBBER_COLOR, RING_REFLECTIVITY);
    m_ring1 = new Ring(ANGLE5, {XB, YB / 2.0f, ZB}, YB / 2.0f, YB / 8.0f, TB / 2.0f, RUBBER_COLOR, RING_REFLECTIVITY, RING_SEGMENTS);
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
}

CadModel Table::model() const
{
    CadModel mm;
    CadModel top_playfield(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, 1.0), PaintCan(1.0, 1.0, 1.0), 99.0);
    mm.add(top_playfield, PLAYFIELD_X / 2.0, 0.0, PLAYFIELD_Z / 2.0);
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
    CadModel diode(CubeShape(TB, Y1, TC), RUBBER_COLOR, 0.0);
    CadModel wall(CubeShape(TC, Y1, TB), RUBBER_COLOR, 0.0);
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

    float PIPE_RADIUS = 0.000625;
    PaintCan PIPE_COLOR(0.42, 0.42, 0.42);

    Pipe p1(0.0, {0.0, 0.0, 0.0}, PIPE_RADIUS, 0.0325, PIPE_COLOR, 10);
    mm.add(p1.model(0.0), 0.0, 4.0 * Y1, 0.0);
    return mm;
}

