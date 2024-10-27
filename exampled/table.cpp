//
// table.cpp
//

#include "table.h"
#include "plane_shape.h"
#include "cube_shape.h"
#include "ring_shape.h"

Table::Table()
    : m_ball_home_position({0.0, 0.0})
    , m_strip1(NULL)
    , m_strip2(NULL)
    , m_wall1(NULL)
    , m_wall2(NULL)
    , m_wall3(NULL)
    , m_wall4(NULL)
{
    m_ball_home_position = {0.0f, 0.0f};
    float ri = 0.1735;
    float px = PLAYFIELD_X / 2.0;
    float pz = PLAYFIELD_Z / 2.0;
    float h = 0.005;
    int steps = 50;
    m_strip1 = new ConcaveStrip(180.0, 360.0, {px, h / 2.0f, pz}, ri, h, PaintCan(0.0, 0.0, 1.0), 0.2, steps);
    m_strip2 = new ConcaveStrip(0.0, 180.0, {px, h / 2.0f, pz}, ri, h, PaintCan(0.0, 0.0, 1.0), 0.2, steps);
    m_wall1 = new Wall({0.24125, 0.039}, {0.24125, 0.065}, 0.001125, BALL_RADIUS, WHITE_COLOR, 0.2, 10);
    m_wall2 = new Wall({0.24125, 0.065}, {0.164, 0.0675}, 0.001125, BALL_RADIUS, WHITE_COLOR, 0.2, 10);
    m_wall3 = new Wall({0.164, 0.0675}, {0.164, 0.106}, 0.001125, BALL_RADIUS, WHITE_COLOR, 0.2, 10);
    m_wall4 = new Wall({0.164, 0.106}, {0.114, 0.1075}, 0.001125, BALL_RADIUS, WHITE_COLOR, 0.2, 10);
}

Table::~Table()
{
    delete m_wall4;
    delete m_wall3;
    delete m_wall2;
    delete m_wall1;
    delete m_strip2;
    delete m_strip1;
}

Float2 Table::ball_home_position() const
{
    return m_ball_home_position;
}

Float2 Table::out_hole_position() const
{
    return {0.144f, 0.11975f};
}

void Table::collide(Ball* ball) const
{
    m_strip1->collide(ball);
    m_strip2->collide(ball);
    m_wall1->collide(ball);
    m_wall2->collide(ball);
    m_wall3->collide(ball);
    m_wall4->collide(ball);
}

CadModel Table::model() const
{
    CadModel mm;
    CadModel top_playfield(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, TEXTURE_ID_PLAYFIELD), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    CadModel backlight(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, 0.0), PaintCan(0.0, 0.0, 0.0), 1.0);

    float ri = 0.1735 + 0.002;
    float ro = ri + 0.010;
    float h = 0.005;
    int steps = 100;

    CadModel ring(RingShape(ro, ri, h, steps), PaintCan(1.0, 0.0, 0.0), 0.0);


    mm.add(backlight, PLAYFIELD_X / 2.0, -0.002f, PLAYFIELD_Z / 2.0);
    mm.add(top_playfield, PLAYFIELD_X / 2.0, 0.0, PLAYFIELD_Z / 2.0);
    mm.add(ring, PLAYFIELD_X / 2.0, h / 2.0, PLAYFIELD_Z / 2.0);
    mm.add(m_strip1->model(0.0));
    mm.add(m_strip2->model(0.0));
    mm.add(m_wall1->model(0.0));
    mm.add(m_wall2->model(0.0));
    mm.add(m_wall3->model(0.0));
    mm.add(m_wall4->model(0.0));
    return mm;
}

