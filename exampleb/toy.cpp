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
#define WOOD_COLOR PaintCan(0.9137, 0.7566, 0.4823)

Toy::Toy()
    : m_strip1(90.0, {0.314, 0.012 / 2.0, 0.369}, 0.416, 0.012, WOOD_COLOR, 0.2)
    , m_strip2(-90.0, {0.288 + T1, 0.012 / 2.0, 0.3635}, 0.427, 0.012, WOOD_COLOR, 0.2)
    , m_strip3(90.0, {0.288, 0.012 / 2.0, 0.335}, 0.370, 0.012, WOOD_COLOR, 0.2)
    , m_strip4(0.0, {0.288 + T1 / 2.0, 0.012 / 2.0, 0.150}, T1, 0.012, WOOD_COLOR, 0.2)
    , m_strip5(30.12, {0.22529, 0.012 / 2.0, 0.55638}, 0.145, 0.012, WOOD_COLOR, 0.2)
    , m_strip6(-30.12, {0.065711, 0.012 / 2.0, 0.55638}, 0.145, 0.012, WOOD_COLOR, 0.2)
    , m_strip7(-90.0, {0.003, 0.012 / 2.0, 0.3338}, 0.3724, 0.012, WOOD_COLOR, 0.2)
    , m_strip8(59.7693 - 180.0, {0.02355, 0.012 / 2.0, 0.112335}, 0.08163, 0.012, WOOD_COLOR, 0.2)
    , m_strip9(0.0, 145.452, {0.314 - R1, 0.012 / 2.0, 0.161}, R1, 0.012, WOOD_COLOR, 0.2, 200)
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

    CadModel cap(CylinderShape(T1 / 2.0, 0.012, 50), WOOD_COLOR, 0.0);
    CadModel barrier1(CubeShape(T1, 0.012, PLAYFIELD_Z - 0.150), WOOD_COLOR, 0.0);
    m_model->add(barrier1, 0.288 + T1 / 2.0, 0.012 / 2.0, (0.150 + PLAYFIELD_Z) / 2.0);
    m_model->add(cap, 0.288 + T1 / 2.0, 0.012 / 2.0, 0.150);

    CadModel barrier2(CubeShape(T1, 0.012 + PLAYFIELD_Y, PLAYFIELD_Z), WOOD_COLOR, 0.0);
    m_model->add(barrier2, 0.314 + T1 / 2.0, 0.012 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z / 2.0);
    m_model->add(barrier2, 0.003 - T1 / 2.0, 0.012 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z / 2.0);

    CadModel barrier3(CubeShape(PLAYFIELD_X, 0.012 + PLAYFIELD_Y, T1), WOOD_COLOR, 0.0);
    m_model->add(barrier3, PLAYFIELD_X / 2.0, 0.012 / 2.0 - PLAYFIELD_Y / 2.0, T1 / 2.0);
    m_model->add(barrier3, PLAYFIELD_X / 2.0, 0.012 / 2.0 - PLAYFIELD_Y / 2.0, PLAYFIELD_Z - T1 / 2.0);

    CadModel panel(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z), WOOD_COLOR, 0.0);
    panel.rotate_ax(180.0);
    m_model->add(panel, PLAYFIELD_X / 2.0, -PLAYFIELD_Y, PLAYFIELD_Z / 2.0);

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

