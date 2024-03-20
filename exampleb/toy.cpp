//
// toy.cpp
//

#include "toy.h"
#include "pi.h"
#include <math.h>
#include "look.h"
#include "plane_shape.h"
#include "cube_shape.h"
#include "cylinder_shape.h"
#include "top_panel_shape.h"
#include "bottom_panel_shape.h"

#define ANIMATION_0_SPEED 0.0
#define ANIMATION_1_SPEED 0.0
#define ANIMATION_2_SPEED 15.0
#define ANIMATION_3_SPEED 30.0

#define ANIMATION_ID_0 2.0
#define ANIMATION_ID_1 3.0
#define ANIMATION_ID_2 4.0
#define ANIMATION_ID_3 5.0

#define R1 0.148
#define T1 0.008
#define Y1 0.018

#define ANGLE1 0.0
#define ANGLE2 145.452
#define WOOD_COLOR PaintCan(0.9137, 0.7566, 0.4823)
#define FACE_PLATE_COLOR PaintCan(1.0, 1.0, 1.0)

#define TOP_PANEL_STEPS 200
#define FOCUS_X (0.314 - R1)
#define FOCUS_Z 0.161

#define BALL_Z_LIMIT 0.610
#define BALL_HOME_X ((0.288 + T1 + 0.314) / 2.0)
#define BALL_HOME_Z (0.57725 - BALL_RADIUS)
//#define BALL_HOME_Z (0.2)
#define BALL_LAUNCH_SPEED 0.5
#define BALL_ACCELERATION 0.100

Toy::Toy()
    : m_ball(BALL_RADIUS, BALL_TOP_COLOR, BALL_MIDDLE_COLOR, BALL_BOTTOM_COLOR, BALL_SEGMENTS)
    , m_strip1(90.0, {0.314, Y1 / 2.0, 0.369}, 0.416, Y1, WOOD_COLOR, 0.2)
    , m_strip2(-90.0, {0.288 + T1, Y1 / 2.0, 0.3635}, 0.427, Y1, WOOD_COLOR, 0.2)
    , m_strip3(90.0, {0.288, Y1 / 2.0, 0.335}, 0.370, Y1, WOOD_COLOR, 0.2)
    , m_strip4(0.0, {0.288 + T1 / 2.0, Y1 / 2.0, 0.150}, T1, Y1, WOOD_COLOR, 0.2)
    , m_strip5(30.12, {0.22529, Y1 / 2.0, 0.55638}, 0.145, Y1, WOOD_COLOR, 0.2)
    , m_strip6(-30.12, {0.065711, Y1 / 2.0, 0.55638}, 0.145, Y1, WOOD_COLOR, 0.2)
    , m_strip7(-90.0, {0.003, Y1 / 2.0, 0.3338}, 0.3724, Y1, WOOD_COLOR, 0.2)
    , m_strip8(59.7693 - 180.0, {0.02355, Y1 / 2.0, 0.112335}, 0.08163, Y1, WOOD_COLOR, 0.2)
    , m_strip9(ANGLE1, ANGLE2, {FOCUS_X, Y1 / 2.0, FOCUS_Z}, R1, Y1, WOOD_COLOR, 0.2, TOP_PANEL_STEPS)
    , m_strip10(0.0, {(0.288 + T1 + 0.314) / 2.0, Y1 / 2.0, 0.57725}, 0.314 - 0.288 - T1, Y1, WOOD_COLOR, 0.0)
    , m_lamp()
    , m_left_flipper(LEFT_FLIPPER_ANGLE, LEFT_FLIPPER_POSITION, BOTTOM_FLIPPER_LENGTH,
                     BOTTOM_FLIPPER_MAJOR_RADIUS, BOTTOM_FLIPPER_MINOR_RADIUS,
                     BOTTOM_FLIPPER_HEIGHT, RUBBER_THICKNESS, RUBBER_HEIGHT,
                     BOTTOM_FLIPPER_COLOR, RUBBER_COLOR, BOTTOM_FLIPPER_TRAVEL,
                     BOTTOM_FLIPPER_SPEED, BOTTOM_FLIPPER_REFLECTIVITY, BOTTOM_FLIPPER_SEGMENTS)
    , m_right_flipper(RIGHT_FLIPPER_ANGLE, RIGHT_FLIPPER_POSITION, BOTTOM_FLIPPER_LENGTH,
                     BOTTOM_FLIPPER_MAJOR_RADIUS, BOTTOM_FLIPPER_MINOR_RADIUS,
                     BOTTOM_FLIPPER_HEIGHT, RUBBER_THICKNESS, RUBBER_HEIGHT,
                     BOTTOM_FLIPPER_COLOR, RUBBER_COLOR, -BOTTOM_FLIPPER_TRAVEL,
                     BOTTOM_FLIPPER_SPEED, BOTTOM_FLIPPER_REFLECTIVITY, BOTTOM_FLIPPER_SEGMENTS)
    , m_top_flipper( TOP_FLIPPER_ANGLE, TOP_FLIPPER_POSITION, TOP_FLIPPER_LENGTH,
                     TOP_FLIPPER_MAJOR_RADIUS, TOP_FLIPPER_MINOR_RADIUS,
                     TOP_FLIPPER_HEIGHT, RUBBER_THICKNESS, RUBBER_HEIGHT,
                     TOP_FLIPPER_COLOR, RUBBER_COLOR, -TOP_FLIPPER_TRAVEL,
                     TOP_FLIPPER_SPEED, TOP_FLIPPER_REFLECTIVITY, TOP_FLIPPER_SEGMENTS)
    , m_model(new CadModel())
    , m_lamp_count(0.0)
    , m_last_launch_action_button(false)
{
    m_lamp.add(LAMP28_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp.add(LAMP8_POSITION,  LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp.add(LAMP10_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp.add(LAMP9_POSITION,  LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp.add(LAMP11_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp.add(LAMP12_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp.add(LAMP14_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp.add(LAMP13_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp.add(LAMP15_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp.add(LAMP16_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp.add(LAMP18_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp.add(LAMP23_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp.add(LAMP21_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp.add(LAMP22_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp.add(LAMP27_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp.add(LAMP25_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp.add(LAMP26_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp.add(LAMP24_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp.add(LAMP4_POSITION, LAMP_SIZE, TYPE4_ON_COLOR, TYPE4_OFF_COLOR);
    m_lamp.add(LAMP20_POSITION, LAMP_SIZE, TYPE4_ON_COLOR, TYPE4_OFF_COLOR);
    m_lamp.add(LAMP19_POSITION, LAMP_SIZE, TYPE5_ON_COLOR, TYPE5_OFF_COLOR);

    m_lamp.set(LAMP28_IX, true);
    m_lamp.set(LAMP21_IX, true);
    m_lamp.set(LAMP25_IX, true);
    m_lamp.set(LAMP26_IX, true);
    m_lamp.set(LAMP15_IX, true);
    m_lamp.set(LAMP19_IX, true);
    m_lamp.set(LAMP4_IX, true);
    m_lamp.set(LAMP20_IX, true);

    build_model();

    m_ball.set_position({BALL_HOME_X, BALL_HOME_Z});
    m_ball.set_velocity({0.0, 0.0});
    m_ball.set_acceleration({0.0, BALL_ACCELERATION});
}

Toy::~Toy()
{
    delete m_model;
}

CadModel* Toy::get_model() const
{
    return m_model;
}

int Toy::animation_matrices() const
{
    return 4;
}

void Toy::advance(int nanoseconds)
{
    float seconds = 1.0e-9 * (float) nanoseconds;
    m_left_flipper.advance(seconds);
    m_right_flipper.advance(seconds);
    m_top_flipper.advance(seconds);
    m_ball.advance(seconds);
    if (m_ball.position().v2 > BALL_Z_LIMIT) {
        m_ball.set_position({BALL_HOME_X, BALL_HOME_Z});
        m_ball.set_velocity({0.0, 0.0});
    }
    m_strip1.collide(m_ball);
    m_strip2.collide(m_ball);
    m_strip3.collide(m_ball);
    m_strip4.collide(m_ball);
    m_strip5.collide(m_ball);
    m_strip6.collide(m_ball);
    m_strip7.collide(m_ball);
    m_strip8.collide(m_ball);
    m_strip9.collide(m_ball);
    m_strip10.collide(m_ball);
    m_left_flipper.collide(m_ball);
    m_right_flipper.collide(m_ball);
    m_top_flipper.collide(m_ball);
    m_lamp_count += nanoseconds;
    if (m_lamp_count > 500000000.0) {
        m_lamp_count = 0.0;
        for (int i = 0; i < m_lamp.lamps(); i++) {
            m_lamp.toggle(i);
        }
    }
}

const Lamp* Toy::get_lamp() const
{
    return &m_lamp;
}

void Toy::build_model()
{

    float k = 1.0;

    m_model->add(m_ball.model(ANIMATION_ID_3));
    CadModel top_playfield(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, 1.0), PaintCan(1.0, 1.0, 1.0), 99.0);
    m_model->add(m_lamp.model(), 0.0, 0.0, 0.0);
    m_model->add(top_playfield, PLAYFIELD_X / 2.0, 0.0, PLAYFIELD_Z / 2.0);

    m_model->add(m_left_flipper.model(ANIMATION_ID_0));
    m_model->add(m_right_flipper.model(ANIMATION_ID_1));
    m_model->add(m_top_flipper.model(ANIMATION_ID_2));
    m_model->add(m_strip1.model(0.0));
    m_model->add(m_strip2.model(0.0));
    m_model->add(m_strip3.model(0.0));
    m_model->add(m_strip4.model(0.0));
    m_model->add(m_strip5.model(0.0));
    m_model->add(m_strip6.model(0.0));
    m_model->add(m_strip7.model(0.0));
    m_model->add(m_strip8.model(0.0));
    m_model->add(m_strip9.model(0.0));
    m_model->add(m_strip10.model(0.0));

    CadModel cap(CylinderShape(T1 / 2.0, Y1, 50), WOOD_COLOR, 0.0);
    CadModel barrier1(CubeShape(T1, Y1, PLAYFIELD_Z - 0.150), WOOD_COLOR, 0.0);
    m_model->add(barrier1, 0.288 + T1 / 2.0, Y1 / 2.0, (0.150 + PLAYFIELD_Z) / 2.0);
    m_model->add(cap, 0.288 + T1 / 2.0, Y1 / 2.0, 0.150);

    CadModel barrier2(CubeShape(T1, Y1 + PLAYFIELD_Y, PLAYFIELD_Z), WOOD_COLOR, 0.0);
    m_model->add(barrier2, 0.314 + T1 / 2.0, Y1 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z / 2.0);
    m_model->add(barrier2, 0.003 - T1 / 2.0, Y1 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z / 2.0);

    CadModel barrier3(CubeShape(PLAYFIELD_X, Y1 + PLAYFIELD_Y, T1), WOOD_COLOR, 0.0);
    m_model->add(barrier3, PLAYFIELD_X / 2.0, Y1 / 2.0 - PLAYFIELD_Y / 2.0, T1 / 2.0);
    m_model->add(barrier3, PLAYFIELD_X / 2.0, Y1 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z - T1 / 2.0);

    CadModel under_panel(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z), WOOD_COLOR, 0.0);
    under_panel.rotate_ax(180.0);
    m_model->add(under_panel, PLAYFIELD_X / 2.0, -PLAYFIELD_Y, PLAYFIELD_Z / 2.0);

    CadModel top_panel(TopPanelShape(PLAYFIELD_X, R1, ANGLE1, ANGLE2, {FOCUS_X, FOCUS_Z}, 0.003, 0.1476, TOP_PANEL_STEPS), WOOD_COLOR, 0.0);
    m_model->add(top_panel, 0.0, Y1, 0.0);

    float r = 0.130;
    float a = 30.12 * PI / 180.0;
    float z1 = 0.520;
    float z2 = z1 + r * sin(a);
    float z3 = PLAYFIELD_Z - T1;
    float x1 = 0.003;
    float x4 = 0.288;
    float x2 = x1 + r * cos(a);
    float x3 = x4 - r * cos(a);
    CadModel bottom_panel(BottomPanelShape(x1, x2, x3, x4, z1, z2, z3), FACE_PLATE_COLOR, 0.0);
    m_model->add(bottom_panel, 0.0, Y1, 0.0);
}

Matrix4x4 Toy::get_animation_matrix(int i) const
{
    Matrix4x4 mm;

    mm.unity();
    if (i == 0) {
        mm.translate(m_left_flipper.position().v1, m_left_flipper.position().v2, m_left_flipper.position().v3);
        mm.rotate_ay(m_left_flipper.active_angle());
        mm.translate(-m_left_flipper.position().v1, -m_left_flipper.position().v2, -m_left_flipper.position().v3);
    } else if (i == 1) {
        mm.translate(m_right_flipper.position().v1, m_right_flipper.position().v2, m_right_flipper.position().v3);
        mm.rotate_ay(m_right_flipper.active_angle());
        mm.translate(-m_right_flipper.position().v1, -m_right_flipper.position().v2, -m_right_flipper.position().v3);
    } else if (i == 2) {
        mm.translate(m_top_flipper.position().v1, m_top_flipper.position().v2, m_top_flipper.position().v3);
        mm.rotate_ay(m_top_flipper.active_angle());
        mm.translate(-m_top_flipper.position().v1, -m_top_flipper.position().v2, -m_top_flipper.position().v3);
    } else if (i == 3) {
        mm = m_ball.animation_matrix();
    }
    return mm;
}

void Toy::left_action_button(bool on)
{
    m_left_flipper.action_button(on);
}

void Toy::right_action_button(bool on)
{
    m_right_flipper.action_button(on);
    m_top_flipper.action_button(on);
}
void Toy::launch_action_button(bool on)
{
    if (on && !m_last_launch_action_button) {
        if (m_ball.position().v2 > (BALL_HOME_Z - BALL_RADIUS)) {
            m_ball.set_velocity({0.0, -BALL_LAUNCH_SPEED});
        }
    }
    m_last_launch_action_button = on;
}

