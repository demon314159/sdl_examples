//
// toy.cpp
//

#include "toy.h"
#include "pi.h"
#include <math.h>
#include "look.h"
#include "layout_guide.h"
#include <stdio.h>



#define BALL_LAUNCH_SPEED 0.9
#define BALL_ACCELERATION 0.25

Toy::Toy()
    : m_lamp_test(0)
    , m_target_test(0)
    , m_ball(NULL)
    , m_lamp(NULL)
    , m_target(NULL)
    , m_switch(NULL)
    , m_table(NULL)
    , m_left_flipper(NULL)
    , m_right_flipper(NULL)
    , m_top_flipper(NULL)
    , m_model(NULL)
    , m_ns_count(0.0)
    , m_last_launch_action_button(false)
{
    m_ball = new Ball(BALL_RADIUS, BALL_TOP_COLOR, BALL_MIDDLE_COLOR, BALL_BOTTOM_COLOR, BALL_SEGMENTS);
    m_lamp = new Lamp();
    m_target = new Target(DROP_TARGET_HEIGHT);
    m_switch = new Switch();
    m_table = new Table();
    m_left_flipper = new Flipper(
        LEFT_FLIPPER_ANGLE, LEFT_FLIPPER_POSITION, BOTTOM_FLIPPER_LENGTH,
        BOTTOM_FLIPPER_MAJOR_RADIUS, BOTTOM_FLIPPER_MINOR_RADIUS,
        BOTTOM_FLIPPER_HEIGHT, RUBBER_THICKNESS, RUBBER_HEIGHT,
        BOTTOM_FLIPPER_COLOR, RUBBER_COLOR, BOTTOM_FLIPPER_TRAVEL,
        BOTTOM_FLIPPER_SPEED, BOTTOM_FLIPPER_REFLECTIVITY, BOTTOM_FLIPPER_SEGMENTS
    );
    m_right_flipper = new Flipper(
        RIGHT_FLIPPER_ANGLE, RIGHT_FLIPPER_POSITION, BOTTOM_FLIPPER_LENGTH,
        BOTTOM_FLIPPER_MAJOR_RADIUS, BOTTOM_FLIPPER_MINOR_RADIUS,
        BOTTOM_FLIPPER_HEIGHT, RUBBER_THICKNESS, RUBBER_HEIGHT,
        BOTTOM_FLIPPER_COLOR, RUBBER_COLOR, -BOTTOM_FLIPPER_TRAVEL,
        BOTTOM_FLIPPER_SPEED, BOTTOM_FLIPPER_REFLECTIVITY, BOTTOM_FLIPPER_SEGMENTS
    );
    m_top_flipper = new Flipper(
        TOP_FLIPPER_ANGLE, TOP_FLIPPER_POSITION, TOP_FLIPPER_LENGTH,
        TOP_FLIPPER_MAJOR_RADIUS, TOP_FLIPPER_MINOR_RADIUS,
        TOP_FLIPPER_HEIGHT, RUBBER_THICKNESS, RUBBER_HEIGHT,
        TOP_FLIPPER_COLOR, RUBBER_COLOR, -TOP_FLIPPER_TRAVEL,
        TOP_FLIPPER_SPEED, TOP_FLIPPER_REFLECTIVITY, TOP_FLIPPER_SEGMENTS,
        true
    );
    m_model = new CadModel();
    m_lamp->add(LAMP28_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP8_POSITION,  LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP10_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP9_POSITION,  LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP11_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP12_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP14_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp->add(LAMP13_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp->add(LAMP15_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp->add(LAMP16_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp->add(LAMP18_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp->add(LAMP23_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP21_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP22_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP27_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP25_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP26_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP24_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP4_POSITION, LAMP_SIZE, TYPE4_ON_COLOR, TYPE4_OFF_COLOR);
    m_lamp->add(LAMP20_POSITION, LAMP_SIZE, TYPE4_ON_COLOR, TYPE4_OFF_COLOR);
    m_lamp->add(LAMP19_POSITION, LAMP_SIZE, TYPE5_ON_COLOR, TYPE5_OFF_COLOR);

    m_lamp->set(LAMP28_IX, true);
    m_lamp->set(LAMP21_IX, true);
    m_lamp->set(LAMP25_IX, true);
    m_lamp->set(LAMP26_IX, true);
    m_lamp->set(LAMP15_IX, true);
    m_lamp->set(LAMP19_IX, true);
    m_lamp->set(LAMP4_IX, true);
    m_lamp->set(LAMP20_IX, true);

    LayoutGuide lg({0.0385, 0.3075}, {0.0215, 0.315}, DROP_TARGET_WIDTH, 1);
    m_target->add(new DropTarget(lg.position(1), lg.angle() , DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 5));

    lg = LayoutGuide({0.111, 0.275}, {0.076, 0.291}, DROP_TARGET_WIDTH, 2);
    m_target->add(new DropTarget(lg.position(2), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 1));
    m_target->add(new DropTarget(lg.position(1), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 6));

    lg = LayoutGuide({0.2015, 0.2345}, {0.1485, 0.258}, DROP_TARGET_WIDTH, 3);
    m_target->add(new DropTarget(lg.position(3), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 7));
    m_target->add(new DropTarget(lg.position(2), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 2));
    m_target->add(new DropTarget(lg.position(1), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 7));

    lg = LayoutGuide({0.2655, 0.39675}, {0.247, 0.32025}, DROP_TARGET_WIDTH, 4);
    m_target->add(new DropTarget(lg.position(4), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 3));
    m_target->add(new DropTarget(lg.position(3), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 8));
    m_target->add(new DropTarget(lg.position(2), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 3));
    m_target->add(new DropTarget(lg.position(1), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 8));

    lg = LayoutGuide({0.106, 0.096}, {0.019, 0.141}, DROP_TARGET_WIDTH, 5);
    m_target->add(new DropTarget(lg.position(5), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 9));
    m_target->add(new DropTarget(lg.position(4), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 4));
    m_target->add(new DropTarget(lg.position(3), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 0));
    m_target->add(new DropTarget(lg.position(2), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 4));
    m_target->add(new DropTarget(lg.position(1), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 9));

    build_model();

    m_ball->set_position(m_table->ball_home_position());
    m_ball->set_velocity({0.0, 0.0});
    m_ball->set_acceleration({0.0, BALL_ACCELERATION});
}

Toy::~Toy()
{
    delete m_ball;
    delete m_lamp;
    delete m_target;
    delete m_switch;
    delete m_table;
    delete m_left_flipper;
    delete m_right_flipper;
    delete m_top_flipper;
    delete m_model;
}

CadModel* Toy::get_model() const
{
    return m_model;
}

int Toy::animation_matrices() const
{
    return ANIMATION_MATRICES;
}

void Toy::advance(int nanoseconds)
{
    float seconds = 1.0e-9 * (float) nanoseconds;
    m_left_flipper->advance(seconds);
    m_right_flipper->advance(seconds);
    m_top_flipper->advance(seconds);
    m_ball->advance(seconds);
    if (m_ball->position().v2 > m_table->ball_z_limit()) {
        m_ball->set_position(m_table->ball_home_position());
        m_ball->set_velocity({0.0, 0.0});
    }
    m_target->collide(m_ball);
    m_table->collide(m_ball);
    m_left_flipper->collide(m_ball);
    m_right_flipper->collide(m_ball);
    m_top_flipper->collide(m_ball);
    m_ball->advance_orientation();
    m_ns_count += nanoseconds;
    if (m_ns_count > 500000000.0) {
        m_ns_count = 0.0;
//        if (m_lamp_test > (m_lamp->lamps() - 1)) {
//            m_lamp_test = 0;
//        }
//        for (int i = 0; i < m_lamp->lamps(); i++) {
//            m_lamp->set(i, i == m_lamp_test);
//        }
//        ++m_lamp_test;

//        if (m_target_test > (m_target->targets() - 1)) {
//            m_target_test = 0;
//        }
//        for (int i = 0; i < m_target->targets(); i++) {
//            m_target->set_dropped(i, i == m_target_test);
//        }
//        ++m_target_test;
    }
}

const Lamp* Toy::get_lamp() const
{
    return m_lamp;
}

const Target* Toy::get_target() const
{
    return m_target;
}

void Toy::build_model()
{
    m_model->add(m_ball->model(ANIMATION_ID_BALL));
    m_model->add(m_lamp->model(ANIMATION_ID_LAMP1));
    m_model->add(m_target->model(ANIMATION_ID_DROP_TARGET1));
    m_model->add(m_left_flipper->model(ANIMATION_ID_LEFT_FLIPPER));
    m_model->add(m_right_flipper->model(ANIMATION_ID_RIGHT_FLIPPER));
    m_model->add(m_top_flipper->model(ANIMATION_ID_TOP_FLIPPER));
    m_model->add(m_table->model());
}

Matrix4x4 Toy::get_animation_matrix(int i) const
{
    Matrix4x4 mm;

    mm.unity();
    if (i == 0) {
        mm.translate(m_left_flipper->position().v1, m_left_flipper->position().v2, m_left_flipper->position().v3);
        mm.rotate_ay(m_left_flipper->active_angle());
        mm.translate(-m_left_flipper->position().v1, -m_left_flipper->position().v2, -m_left_flipper->position().v3);
    } else if (i == 1) {
        mm.translate(m_right_flipper->position().v1, m_right_flipper->position().v2, m_right_flipper->position().v3);
        mm.rotate_ay(m_right_flipper->active_angle());
        mm.translate(-m_right_flipper->position().v1, -m_right_flipper->position().v2, -m_right_flipper->position().v3);
    } else if (i == 2) {
        mm.translate(m_top_flipper->position().v1, m_top_flipper->position().v2, m_top_flipper->position().v3);
        mm.rotate_ay(m_top_flipper->active_angle());
        mm.translate(-m_top_flipper->position().v1, -m_top_flipper->position().v2, -m_top_flipper->position().v3);
    } else if (i == 3) {
        mm = m_ball->animation_matrix();
    }
    return mm;
}

void Toy::left_action_button(bool on)
{
    m_left_flipper->action_button(on);
}

void Toy::right_action_button(bool on)
{
    m_right_flipper->action_button(on);
    m_top_flipper->action_button(on);
}
void Toy::launch_action_button(bool on)
{
    if (on && !m_last_launch_action_button) {
        if ((m_ball->position().v2 > (m_table->ball_home_position().v2 - BALL_RADIUS))
         && (m_ball->position().v1 > (m_table->ball_home_position().v1 - BALL_RADIUS))) {
            m_ball->set_velocity({0.0, -BALL_LAUNCH_SPEED});
        }
    }
    m_last_launch_action_button = on;
}

