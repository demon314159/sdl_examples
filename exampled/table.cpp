//
// table.cpp
//

#include "table.h"
#include "plane_shape.h"
#include "cube_shape.h"
#include "ring_shape.h"

#define PERIMETER_RADIUS 0.1755f
#define PERIMETER_STEPS 100
#define WALL_THICKNESS 0.0025f
#define WALL_HEIGHT 0.005f
#define WALL_STEPS 10
#define TRAP_RADIUS 0.011f

Table::Table()
    : m_ball_home_position({0.230, 0.049})
    , m_strip1(NULL)
    , m_strip2(NULL)
    , m_wall1(NULL)
    , m_wall2(NULL)
    , m_wall3(NULL)
    , m_wall4(NULL)
    , m_wall5(NULL)
    , m_wall6(NULL)
    , m_wall7(NULL)
    , m_wall8(NULL)
    , m_wall9(NULL)
    , m_wall10(NULL)
    , m_wall11(NULL)
    , m_wall12(NULL)
    , m_wall13(NULL)
    , m_wall14(NULL)
    , m_wall15(NULL)
    , m_wall16a(NULL)
    , m_wall16b(NULL)
    , m_wall17(NULL)
    , m_wall18(NULL)
    , m_wall19(NULL)
    , m_wall20(NULL)
    , m_wall21a(NULL)
    , m_wall21b(NULL)
    , m_wall22(NULL)
    , m_wall23(NULL)
    , m_wall24(NULL)
    , m_wall25(NULL)
    , m_wall26(NULL)
    , m_wall27(NULL)
    , m_wall28(NULL)
    , m_wall29(NULL)
    , m_wall30(NULL)
    , m_wall31(NULL)
    , m_wall32(NULL)
    , m_wall33(NULL)
    , m_trap1(NULL)
    , m_trap2(NULL)
    , m_trap3(NULL)
    , m_trap4(NULL)
    , m_trap5(NULL)
    , m_trap6(NULL)
    , m_trap7(NULL)
    , m_trap8(NULL)
    , m_trap9(NULL)
    , m_trap10(NULL)
    , m_trap11(NULL)
    , m_trap12(NULL)
    , m_trap13(NULL)
    , m_trap14(NULL)
    , m_trap15(NULL)
    , m_trap16(NULL)
    , m_trap17(NULL)
    , m_trap18(NULL)
    , m_trap19(NULL)
    , m_trap20(NULL)
    , m_trap21(NULL)
    , m_trap22(NULL)
    , m_trap23(NULL)
    , m_trap24(NULL)
    , m_trap25(NULL)
{
    float px = PLAYFIELD_X / 2.0;
    float pz = PLAYFIELD_Z / 2.0;
    m_strip1 = new ConcaveStrip(180.0, 360.0, {px, WALL_HEIGHT / 2.0f, pz}, PERIMETER_RADIUS, WALL_HEIGHT, WHITE_COLOR, 0.2, PERIMETER_STEPS / 2.0f);
    m_strip2 = new ConcaveStrip(0.0, 180.0, {px, WALL_HEIGHT / 2.0f, pz}, PERIMETER_RADIUS, WALL_HEIGHT, WHITE_COLOR, 0.2, PERIMETER_STEPS / 2.0f);
    float wr = WALL_THICKNESS / 2.0f;
    float ws = WALL_STEPS;
    m_wall1 = new Wall({0.24125, 0.039}, {0.24125, 0.065}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall2 = new Wall({0.24125, 0.065}, {0.164, 0.0675}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall3 = new Wall({0.164, 0.0675}, {0.164, 0.106}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall4 = new Wall({0.164, 0.106}, {0.114, 0.1075}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall5 = new Wall({0.134, 0.0495}, {0.134, 0.066}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall6 = new Wall({0.1935, 0.0925}, {0.1935, 0.115}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall7 = new Wall({0.2305, 0.092}, {0.2305, 0.114}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall8 = new Wall({0.083, 0.1345}, {0.173, 0.134}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall9 = new Wall({0.13475, 0.1345}, {0.13475, 0.1785}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall10 = new Wall({0.203, 0.140}, {0.258, 0.139}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall11 = new Wall({0.258, 0.139}, {0.258, 0.103}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall12 = new Wall({0.258, 0.103}, {0.291, 0.103}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall13 = new Wall({0.3285, 0.132}, {0.360, 0.132}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall14 = new Wall({0.292, 0.1355}, {0.292, 0.1625}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall15 = new Wall({0.292, 0.1625}, {0.333, 0.1625}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall16a = new Wall({0.267, 0.196}, {0.344, 0.196}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall16b = new Wall({0.3725, 0.194}, {0.3775, 0.194}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall17 = new Wall({0.063, 0.169}, {0.081, 0.169}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall18 = new Wall({0.031, 0.196}, {0.055, 0.196}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall19 = new Wall({0.094, 0.200}, {0.094, 0.229}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall20 = new Wall({0.094, 0.229}, {0.127, 0.229}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall21a = new Wall({0.0435, 0.2755}, {0.046, 0.2755}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall21b = new Wall({0.071, 0.2755}, {0.1085, 0.2755}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall22 = new Wall({0.1085, 0.2755}, {0.1085, 0.263}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall23 = new Wall({0.139, 0.280}, {0.2435, 0.280}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall24 = new Wall({0.261, 0.248}, {0.261, 0.227}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall25 = new Wall({0.261, 0.227}, {0.3345, 0.227}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall26 = new Wall({0.301, 0.256}, {0.3715, 0.256}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall27 = new Wall({0.260, 0.3015}, {0.3135, 0.3015}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall28 = new Wall({0.260, 0.3015}, {0.260, 0.334}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall29 = new Wall({0.1915, 0.3025}, {0.1915, 0.327}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall30 = new Wall({0.101, 0.308}, {0.162, 0.308}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall31 = new Wall({0.162, 0.308}, {0.162, 0.358}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall32 = new Wall({0.162, 0.358}, {0.223, 0.358}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    m_wall33 = new Wall({0.223, 0.319}, {0.223, 0.381}, wr, BALL_RADIUS, WHITE_COLOR, 0.2, ws);
    float rr = TRAP_RADIUS;
    m_trap1 = new Trap({0.118, 0.074}, rr);
    m_trap2 = new Trap({0.0665, 0.1235}, rr);
    m_trap3 = new Trap({0.1885, 0.1315}, rr);
    m_trap4 = new Trap({0.22875, 0.079}, rr);
    m_trap5 = new Trap({0.2595, 0.0615}, rr);
    m_trap6 = new Trap({0.3305, 0.118}, rr);
    m_trap7 = new Trap({0.2805, 0.1215}, rr);
    m_trap8 = new Trap({0.3585, 0.1945}, rr);
    m_trap9 = new Trap({0.246, 0.1825}, rr);
    m_trap10 = new Trap({0.1485, 0.1485}, rr);
    m_trap11 = new Trap({0.142, 0.227}, rr);
    m_trap12 = new Trap({0.0905, 0.182}, rr);
    m_trap13 = new Trap({0.120, 0.14925}, rr);
    m_trap14 = new Trap({0.0835, 0.2325}, rr);
    m_trap15 = new Trap({0.042, 0.209}, rr);
    m_trap16 = new Trap({0.058, 0.276}, rr);
    m_trap17 = new Trap({0.126, 0.2755}, rr);
    m_trap18 = new Trap({0.2585, 0.264}, rr);
    m_trap19 = new Trap({0.2585, 0.2885}, rr);
    m_trap20 = new Trap({0.3485, 0.2685}, rr);
    m_trap21 = new Trap({0.2955, 0.3375}, rr);
    m_trap22 = new Trap({0.237, 0.363}, rr);
    m_trap23 = new Trap({0.19175, 0.2905}, rr);
    m_trap24 = new Trap({0.1195, 0.3445}, rr);
    m_trap25 = new Trap({0.151, 0.321}, rr);
}

Table::~Table()
{
    delete m_trap25;
    delete m_trap24;
    delete m_trap23;
    delete m_trap22;
    delete m_trap21;
    delete m_trap20;
    delete m_trap19;
    delete m_trap18;
    delete m_trap17;
    delete m_trap16;
    delete m_trap15;
    delete m_trap14;
    delete m_trap13;
    delete m_trap12;
    delete m_trap11;
    delete m_trap10;
    delete m_trap9;
    delete m_trap8;
    delete m_trap7;
    delete m_trap6;
    delete m_trap5;
    delete m_trap4;
    delete m_trap3;
    delete m_trap2;
    delete m_trap1;
    delete m_wall33;
    delete m_wall32;
    delete m_wall31;
    delete m_wall30;
    delete m_wall29;
    delete m_wall28;
    delete m_wall27;
    delete m_wall26;
    delete m_wall25;
    delete m_wall24;
    delete m_wall23;
    delete m_wall22;
    delete m_wall21b;
    delete m_wall21a;
    delete m_wall20;
    delete m_wall19;
    delete m_wall18;
    delete m_wall17;
    delete m_wall16b;
    delete m_wall16a;
    delete m_wall15;
    delete m_wall14;
    delete m_wall13;
    delete m_wall12;
    delete m_wall11;
    delete m_wall10;
    delete m_wall9;
    delete m_wall8;
    delete m_wall7;
    delete m_wall6;
    delete m_wall5;
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

void Table::collide(Ball* ball) const
{
    m_strip1->collide(ball);
    m_strip2->collide(ball);
    m_wall1->collide(ball);
    m_wall2->collide(ball);
    m_wall3->collide(ball);
    m_wall4->collide(ball);
    m_wall5->collide(ball);
    m_wall6->collide(ball);
    m_wall7->collide(ball);
    m_wall8->collide(ball);
    m_wall9->collide(ball);
    m_wall10->collide(ball);
    m_wall11->collide(ball);
    m_wall12->collide(ball);
    m_wall13->collide(ball);
    m_wall14->collide(ball);
    m_wall15->collide(ball);
    m_wall16a->collide(ball);
    m_wall16b->collide(ball);
    m_wall17->collide(ball);
    m_wall18->collide(ball);
    m_wall19->collide(ball);
    m_wall20->collide(ball);
    m_wall21a->collide(ball);
    m_wall21b->collide(ball);
    m_wall22->collide(ball);
    m_wall23->collide(ball);
    m_wall24->collide(ball);
    m_wall25->collide(ball);
    m_wall26->collide(ball);
    m_wall27->collide(ball);
    m_wall28->collide(ball);
    m_wall29->collide(ball);
    m_wall30->collide(ball);
    m_wall31->collide(ball);
    m_wall32->collide(ball);
    m_wall33->collide(ball);
}

void Table::trap(Ball* ball) const
{
    m_trap1->collide(ball);
    m_trap2->collide(ball);
    m_trap3->collide(ball);
    m_trap4->collide(ball);
    m_trap5->collide(ball);
    m_trap6->collide(ball);
    m_trap7->collide(ball);
    m_trap8->collide(ball);
    m_trap9->collide(ball);
    m_trap10->collide(ball);
    m_trap11->collide(ball);
    m_trap12->collide(ball);
    m_trap13->collide(ball);
    m_trap14->collide(ball);
    m_trap15->collide(ball);
    m_trap16->collide(ball);
    m_trap17->collide(ball);
    m_trap18->collide(ball);
    m_trap19->collide(ball);
    m_trap20->collide(ball);
    m_trap21->collide(ball);
    m_trap22->collide(ball);
    m_trap23->collide(ball);
    m_trap24->collide(ball);
    m_trap25->collide(ball);
}

CadModel Table::model() const
{
    CadModel mm;
    CadModel top_playfield(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, TEXTURE_ID_PLAYFIELD), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    CadModel backlight(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, 0.0), PaintCan(0.0, 0.0, 0.0), 1.0);
    float ri = PERIMETER_RADIUS;
    float ro = ri + WALL_THICKNESS;
    float px = PLAYFIELD_X / 2.0;
    float pz = PLAYFIELD_Z / 2.0;
    CadModel ring(RingShape(ro, ri, WALL_HEIGHT, PERIMETER_STEPS), WHITE_COLOR, 0.0);
    mm.add(ring,px, WALL_HEIGHT / 2.0f, pz);
    mm.add(backlight, PLAYFIELD_X / 2.0, -0.002f, PLAYFIELD_Z / 2.0);
    mm.add(top_playfield, PLAYFIELD_X / 2.0, 0.0, PLAYFIELD_Z / 2.0);
    mm.add(m_strip1->model(0.0));
    mm.add(m_strip2->model(0.0));
    mm.add(m_wall1->model(0.0));
    mm.add(m_wall2->model(0.0));
    mm.add(m_wall3->model(0.0));
    mm.add(m_wall4->model(0.0));
    mm.add(m_wall5->model(0.0));
    mm.add(m_wall6->model(0.0));
    mm.add(m_wall7->model(0.0));
    mm.add(m_wall8->model(0.0));
    mm.add(m_wall9->model(0.0));
    mm.add(m_wall10->model(0.0));
    mm.add(m_wall11->model(0.0));
    mm.add(m_wall12->model(0.0));
    mm.add(m_wall13->model(0.0));
    mm.add(m_wall14->model(0.0));
    mm.add(m_wall15->model(0.0));
    mm.add(m_wall16a->model(0.0));
    mm.add(m_wall16b->model(0.0));
    mm.add(m_wall17->model(0.0));
    mm.add(m_wall18->model(0.0));
    mm.add(m_wall19->model(0.0));
    mm.add(m_wall20->model(0.0));
    mm.add(m_wall21a->model(0.0));
    mm.add(m_wall21b->model(0.0));
    mm.add(m_wall22->model(0.0));
    mm.add(m_wall23->model(0.0));
    mm.add(m_wall24->model(0.0));
    mm.add(m_wall25->model(0.0));
    mm.add(m_wall26->model(0.0));
    mm.add(m_wall27->model(0.0));
    mm.add(m_wall28->model(0.0));
    mm.add(m_wall29->model(0.0));
    mm.add(m_wall30->model(0.0));
    mm.add(m_wall31->model(0.0));
    mm.add(m_wall32->model(0.0));
    mm.add(m_wall33->model(0.0));
    return mm;
}

