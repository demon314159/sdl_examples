//
// toy.cpp
//

#include "toy.h"
#include "pi.h"
#include <math.h>
#include "look.h"
#include "layout_guide.h"
#include "backglass_guide.h"
#include <stdio.h>

#define SCORE_DELAY 150 // milliseconds
#define BALL_OUT_HOLE_SPEED 0.3
#define BALL_LAUNCH_SPEED 0.9
#define BALL_ACCELERATION 0.25

Toy::Toy()
    : m_seconds(0.0)
    , m_player(1)
    , m_ball(NULL)
    , m_lamp(NULL)
    , m_target(NULL)
    , m_sensor(NULL)
    , m_sound(NULL)
    , m_scoreboard(NULL)
    , m_score(NULL)
    , m_queue(NULL)
    , m_execute(NULL)
    , m_table(NULL)
    , m_left_flipper(NULL)
    , m_right_flipper(NULL)
    , m_top_flipper(NULL)
    , m_model(NULL)
    , m_last_launch_action_button(false)
{
    m_ball = new Ball(BALL_RADIUS, BALL_TOP_COLOR, BALL_MIDDLE_COLOR, BALL_BOTTOM_COLOR, BALL_SEGMENTS);
    m_lamp = new Lamp(ANIMATION_ID_FIXED_LAMP1);
    m_target = new Target(DROP_TARGET_HEIGHT);
    m_sensor = new Sensor(MAX_SENSORS);
    m_sound = new Sound();
    m_table = new Table();
    m_scoreboard = new Scoreboard({SCOREBOARD_POSITION_X, SCOREBOARD_POSITION_Y, SCOREBOARD_POSITION_Z}, {BACKGLASS_SIZE_X, BACKGLASS_SIZE_Z},
                                  {BACKGLASS_IMAGE_SIZE_X, BACKGLASS_IMAGE_SIZE_Z},
                                   m_table->trim(), m_table->trim_color(), TEXTURE_ID_BACKGLASS, TEXTURE_ID_SCORE);
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
    m_lamp->add(LAMP_5X_BONUS_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP_ACES_POSITION,  LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP_KINGS_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP_QUEENS_POSITION,  LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP_JACKS_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP_TENS_POSITION, LAMP_SIZE, TYPE1_ON_COLOR, TYPE1_OFF_COLOR);
    m_lamp->add(LAMP_5000_BONUS_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp->add(LAMP_4000_BONUS_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);

    m_lamp->add(LAMP_3000_BONUS_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp->add(LAMP_2000_BONUS_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp->add(LAMP_1000_BONUS_POSITION, LAMP_SIZE, TYPE2_ON_COLOR, TYPE2_OFF_COLOR);
    m_lamp->add(LAMP_TOP_ROLLOVER_A_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP_TOP_ROLLOVER_B_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP_TOP_ROLLOVER_C_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP_BOTTOM_ROLLOVER_A_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP_BOTTOM_LEFT_ROLLOVER_B_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP_BOTTOM_RIGHT_ROLLOVER_B_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP_BOTTOM_ROLLOVER_C_POSITION, LAMP_SIZE, TYPE3_ON_COLOR, TYPE3_OFF_COLOR);
    m_lamp->add(LAMP_SHOOT_AGAIN_POSITION, LAMP_SIZE, TYPE4_ON_COLOR, TYPE4_OFF_COLOR);
    m_lamp->add(LAMP_EXTRA_BALL_POSITION, LAMP_SIZE, TYPE4_ON_COLOR, TYPE4_OFF_COLOR);
    m_lamp->add(LAMP_SPECIAL_POSITION, LAMP_SIZE, TYPE5_ON_COLOR, TYPE5_OFF_COLOR);

    BackglassGuide bg({SCOREBOARD_POSITION_X, SCOREBOARD_POSITION_Y, SCOREBOARD_POSITION_Z},{BACKGLASS_SIZE_X, BACKGLASS_SIZE_Z}, {BACKGLASS_IMAGE_SIZE_X, BACKGLASS_IMAGE_SIZE_Z});
    m_lamp->add(bg.position(FIXED_LAMP_BALL_IN_PLAY_POSITION), bg.size({0.022, 0.026}), TYPE10_ON_COLOR, TYPE10_OFF_COLOR);
    m_lamp->add(bg.position(FIXED_LAMP_NUMBER_TO_MATCH_POSITION), bg.size({0.032, 0.017}), TYPE11_ON_COLOR, TYPE11_OFF_COLOR);
    m_lamp->add(bg.position(FIXED_LAMP_HIGH_GAME_TO_DATE_POSITION), bg.size({0.027, 0.020}), TYPE8_ON_COLOR, TYPE8_OFF_COLOR);
    m_lamp->add(bg.position(FIXED_LAMP_GAME_OVER_POSITION), bg.size({0.022, 0.014}), TYPE7_ON_COLOR, TYPE7_OFF_COLOR);
    m_lamp->add(bg.position(FIXED_LAMP_SHOOT_AGAIN_POSITION), bg.size({0.023, 0.012}), TYPE9_ON_COLOR, TYPE9_OFF_COLOR);
    m_lamp->add(bg.position(FIXED_LAMP_PLAYER1_POSITION), bg.size({0.020, 0.017}), TYPE6_ON_COLOR, TYPE6_OFF_COLOR);
    m_lamp->add(bg.position(FIXED_LAMP_PLAYER2_POSITION), bg.size({0.020, 0.017}), TYPE6_ON_COLOR, TYPE6_OFF_COLOR);
    m_lamp->add(bg.position(FIXED_LAMP_PLAYER3_POSITION), bg.size({0.0195, 0.0155}), TYPE6_ON_COLOR, TYPE6_OFF_COLOR);
    m_lamp->add(bg.position(FIXED_LAMP_PLAYER4_POSITION), bg.size({0.020, 0.016}), TYPE6_ON_COLOR, TYPE6_OFF_COLOR);

    m_lamp->set(LAMP_ID_TOP_ROLLOVER_A, true);
    m_lamp->set(LAMP_ID_TOP_ROLLOVER_B, true);
    m_lamp->set(LAMP_ID_TOP_ROLLOVER_C, true);
    m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_A, true);
    m_lamp->set(LAMP_ID_BOTTOM_LEFT_ROLLOVER_B, true);
    m_lamp->set(LAMP_ID_BOTTOM_RIGHT_ROLLOVER_B, true);
    m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_C, true);

    LayoutGuide lg({0.0385, 0.3075}, {0.0215, 0.315}, DROP_TARGET_WIDTH, 1);
    m_target->add(new DropTarget(lg.position(1), lg.angle() , DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 5, SENSOR_ID_DROP_10));

    lg = LayoutGuide({0.111, 0.275}, {0.076, 0.291}, DROP_TARGET_WIDTH, 2);
    m_target->add(new DropTarget(lg.position(2), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 1, SENSOR_ID_DROP_J1));
    m_target->add(new DropTarget(lg.position(1), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 6, SENSOR_ID_DROP_J2));

    lg = LayoutGuide({0.2015, 0.2345}, {0.1485, 0.258}, DROP_TARGET_WIDTH, 3);
    m_target->add(new DropTarget(lg.position(3), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 7, SENSOR_ID_DROP_Q1));
    m_target->add(new DropTarget(lg.position(2), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 2, SENSOR_ID_DROP_Q2));
    m_target->add(new DropTarget(lg.position(1), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 7, SENSOR_ID_DROP_Q3));

    lg = LayoutGuide({0.2655, 0.39675}, {0.247, 0.32025}, DROP_TARGET_WIDTH, 4);
    m_target->add(new DropTarget(lg.position(4), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 3, SENSOR_ID_DROP_K1));
    m_target->add(new DropTarget(lg.position(3), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 8, SENSOR_ID_DROP_K2));
    m_target->add(new DropTarget(lg.position(2), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 3, SENSOR_ID_DROP_K3));
    m_target->add(new DropTarget(lg.position(1), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 8, SENSOR_ID_DROP_K4));

    lg = LayoutGuide({0.106, 0.096}, {0.019, 0.141}, DROP_TARGET_WIDTH, 5);
    m_target->add(new DropTarget(lg.position(5), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 9, SENSOR_ID_DROP_A1));
    m_target->add(new DropTarget(lg.position(4), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 4, SENSOR_ID_DROP_A2));
    m_target->add(new DropTarget(lg.position(3), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 0, SENSOR_ID_DROP_JOKER));
    m_target->add(new DropTarget(lg.position(2), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 4, SENSOR_ID_DROP_A3));
    m_target->add(new DropTarget(lg.position(1), lg.angle(), DROP_TARGET_WIDTH, DROP_TARGET_HEIGHT, DROP_TARGET_THICKNESS, DROP_TARGET_COLOR, DROP_TARGET_REFLECTIVITY, DROP_TARGET_SEGMENTS, TEXTURE_ID_DROP_TARGET, 9, SENSOR_ID_DROP_A4));

    build_model();
    m_queue = new Queue();
    m_score = new Score(m_scoreboard, m_lamp);

    m_score->set_high_game(120000);
    m_score->set_match(70);
    m_execute = new Execute(m_queue, m_score);

    m_ball->set_position(m_table->out_hole_position());
    m_ball->set_velocity({0.0, 0.0});
    m_ball->set_acceleration({0.0, BALL_ACCELERATION});
}

Toy::~Toy()
{
    delete m_ball;
    delete m_lamp;
    delete m_target;
    delete m_sensor;
    delete m_sound;
    delete m_score;
    delete m_queue;
    delete m_execute;
    delete m_scoreboard;
    delete m_table;
    delete m_left_flipper;
    delete m_right_flipper;
    delete m_top_flipper;
    delete m_model;
}

void Toy::initialize()
{
    m_sound->initialize();
}

CadModel* Toy::get_model() const
{
    return m_model;
}

int Toy::animation_matrices() const
{
    return ANIMATION_MATRICES;
}

void Toy::eject_from_out_hole()
{
    float vx = BALL_OUT_HOLE_SPEED * cos(20.0f * PI / 180.0f);
    float vz = -BALL_OUT_HOLE_SPEED * sin(20.0f * PI / 180.0f);
    m_ball->set_velocity({vx, vz});
    m_ball->set_position({0.266, 0.564});
}

void Toy::activate_solenoid(int solenoid_id)
{
    switch (solenoid_id) {
        case SOLENOID_ID_NONE:
            break;
        case SOLENOID_ID_OUT_HOLE:
            eject_from_out_hole();
            break;
        case SOLENOID_ID_KNOCKER:
            break;
        case SOLENOID_ID_TENS_CHIME:
            m_sound->play(SOUND_ID_TENS_CHIME);
            break;
        case SOLENOID_ID_HUNDREDS_CHIME:
            m_sound->play(SOUND_ID_HUNDREDS_CHIME);
            break;
        case SOLENOID_ID_THOUSANDS_CHIME:
            m_sound->play(SOUND_ID_THOUSANDS_CHIME);
            break;
        case SOLENOID_ID_DROP_TARGET_JACKS:
            m_target->set_dropped(DROP_TARGET_ID_10, false);
            m_target->set_dropped(DROP_TARGET_ID_J1, false);
            m_target->set_dropped(DROP_TARGET_ID_J2, false);
            break;
        case SOLENOID_ID_DROP_TARGET_QUEENS:
            m_target->set_dropped(DROP_TARGET_ID_Q1, false);
            m_target->set_dropped(DROP_TARGET_ID_Q2, false);
            m_target->set_dropped(DROP_TARGET_ID_Q3, false);
            break;
        case SOLENOID_ID_DROP_TARGET_KINGS:
            m_target->set_dropped(DROP_TARGET_ID_K1, false);
            m_target->set_dropped(DROP_TARGET_ID_K2, false);
            m_target->set_dropped(DROP_TARGET_ID_K3, false);
            m_target->set_dropped(DROP_TARGET_ID_K4, false);
            break;
        case SOLENOID_ID_DROP_TARGET_ACES:
            m_target->set_dropped(DROP_TARGET_ID_A1, false);
            m_target->set_dropped(DROP_TARGET_ID_A2, false);
            m_target->set_dropped(DROP_TARGET_ID_JOKER, false);
            m_target->set_dropped(DROP_TARGET_ID_A3, false);
            m_target->set_dropped(DROP_TARGET_ID_A4, false);
            break;
        case SOLENOID_ID_DROP_TARGET_ALL:
            m_target->set_dropped(DROP_TARGET_ID_10, false);
            m_target->set_dropped(DROP_TARGET_ID_J1, false);
            m_target->set_dropped(DROP_TARGET_ID_J2, false);
            m_target->set_dropped(DROP_TARGET_ID_Q1, false);
            m_target->set_dropped(DROP_TARGET_ID_Q2, false);
            m_target->set_dropped(DROP_TARGET_ID_Q3, false);
            m_target->set_dropped(DROP_TARGET_ID_K1, false);
            m_target->set_dropped(DROP_TARGET_ID_K2, false);
            m_target->set_dropped(DROP_TARGET_ID_K3, false);
            m_target->set_dropped(DROP_TARGET_ID_K4, false);
            m_target->set_dropped(DROP_TARGET_ID_A1, false);
            m_target->set_dropped(DROP_TARGET_ID_A2, false);
            m_target->set_dropped(DROP_TARGET_ID_JOKER, false);
            m_target->set_dropped(DROP_TARGET_ID_A3, false);
            m_target->set_dropped(DROP_TARGET_ID_A4, false);
            break;
        default:
            break;
    }
}

void Toy::advance(int nanoseconds)
{
    m_seconds += (1.0e-9 * (float) nanoseconds);
    float seconds = 1.0e-3;
    while (m_seconds > seconds) {
        m_seconds -= seconds;
        m_sensor->clear();
        m_left_flipper->advance(seconds);
        m_right_flipper->advance(seconds);
        m_top_flipper->advance(seconds);
        if (m_ball->position().v2 < m_table->ball_z_limit()) {
            m_ball->advance(seconds);
        } else {
            m_sensor->set(SENSOR_ID_OUTHOLE);
        }
        m_target->collide(m_ball, m_sensor);
        m_table->collide(m_ball, m_sensor);
        m_left_flipper->collide(m_ball);
        m_right_flipper->collide(m_ball);
        m_top_flipper->collide(m_ball);
        m_ball->advance_orientation();
        m_scoreboard->advance(seconds);
        apply_rules();
        m_score->advance(seconds);
        int solenoid_id = m_execute->advance(seconds);
        activate_solenoid(solenoid_id);
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

const Scoreboard* Toy::get_scoreboard() const
{
    return m_scoreboard;
}

void Toy::build_model()
{
    m_model->add(m_ball->model(ANIMATION_ID_BALL));
    m_model->add(m_lamp->model(ANIMATION_ID_LAMP1));
    m_model->add(m_target->model(ANIMATION_ID_DROP_TARGET1));
    m_model->add(m_left_flipper->model(ANIMATION_ID_LEFT_FLIPPER));
    m_model->add(m_right_flipper->model(ANIMATION_ID_RIGHT_FLIPPER));
    m_model->add(m_top_flipper->model(ANIMATION_ID_TOP_FLIPPER));
    m_model->add(m_scoreboard->model(ANIMATION_ID_SCORE11, ANIMATION_ID_SCOREBOARD));
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

void Toy::replay_action_button(bool on)
{
    m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_HUNDREDS_CHIME);
    m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_ALL);
    m_queue->put(QCOMMAND_DELAY, 0, SCORE_DELAY);
    m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_OUT_HOLE);
    m_queue->put(QCOMMAND_SET_BALL, 0, 1);
}



#ifdef NEVERMORE
#define SENSOR_ID_BUMPER       1
#define SENSOR_ID_ROLLOVER_A   2
#define SENSOR_ID_ROLLOVER_B   3
#define SENSOR_ID_ROLLOVER_C   4
#define SENSOR_ID_EXTRA_BALL   5
#define SENSOR_ID_DROP_10      6
#define SENSOR_ID_DROP_J1      7
#define SENSOR_ID_DROP_J2      8
#define SENSOR_ID_SPECIAL      9
#define SENSOR_ID_DROP_Q1      10
#define SENSOR_ID_DROP_Q2      11
#define SENSOR_ID_DROP_Q3      12
#define SENSOR_ID_TEN_POINT    13
#define SENSOR_ID_DROP_K1      14
#define SENSOR_ID_DROP_K2      15
#define SENSOR_ID_DROP_K3      14
#define SENSOR_ID_DROP_K4      17
#define SENSOR_ID_DROP_A1      18
#define SENSOR_ID_DROP_A2      19
#define SENSOR_ID_DROP_JOKER   20
#define SENSOR_ID_DROP_A3      21
#define SENSOR_ID_DROP_A4      22

#define LAMP_ID_5X_BONUS                 0
#define LAMP_ID_ACES_BONUS               1
#define LAMP_ID_KINGS_BONUS              2
#define LAMP_ID_QUEENS_BONUS             3
#define LAMP_ID_JACKS_BONUS              4
#define LAMP_ID_TENS_BONUS               5
#define LAMP_ID_5000_BONUS               6
#define LAMP_ID_4000_BONUS               7
#define LAMP_ID_3000_BONUS               8
#define LAMP_ID_2000_BONUS               9
#define LAMP_ID_1000_BONUS               10
#define LAMP_ID_TOP_ROLLOVER_A           11
#define LAMP_ID_TOP_ROLLOVER_B           12
#define LAMP_ID_TOP_ROLLOVER_C           13
#define LAMP_ID_BOTTOM_ROLLOVER_A        14
#define LAMP_ID_LEFT_BOTTOM_ROLLOVER_B   15
#define LAMP_ID_RIGHT_BOTTOM_ROLLOVER_B  16
#define LAMP_ID_BOTTOM_ROLLOVER_C        17
#define LAMP_ID_SHOOT_AGAIN              18
#define LAMP_ID_EXTRA_BALL               19
#define LAMP_ID_SPECIAL                  20
#endif

void Toy::multiscore(int n, int solenoid_id, int score)
{
    for (int i = 0; i < n; i++) {
        m_queue->put(QCOMMAND_SOLENOID, 0, solenoid_id);
        m_queue->put(QCOMMAND_ADD_SCORE, m_player, score);
        m_queue->put(QCOMMAND_DELAY, 0, SCORE_DELAY);
    }
}

void Toy::rollover_rules()
{
    if (m_sensor->rising(SENSOR_ID_ROLLOVER_A)) {
        if (m_lamp->lit(LAMP_ID_TOP_ROLLOVER_A)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        }
        m_lamp->set(LAMP_ID_TOP_ROLLOVER_A, false);
        m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_A, false);
    }
    if (m_sensor->rising(SENSOR_ID_ROLLOVER_B)) {
        if (m_lamp->lit(LAMP_ID_TOP_ROLLOVER_B)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        }
        m_lamp->set(LAMP_ID_TOP_ROLLOVER_B, false);
        m_lamp->set(LAMP_ID_BOTTOM_LEFT_ROLLOVER_B, false);
        m_lamp->set(LAMP_ID_BOTTOM_RIGHT_ROLLOVER_B, false);
    }
    if (m_sensor->rising(SENSOR_ID_ROLLOVER_C)) {
        if (m_lamp->lit(LAMP_ID_TOP_ROLLOVER_C)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        }
        m_lamp->set(LAMP_ID_TOP_ROLLOVER_C, false);
        m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_C, false);
    }
    if (m_sensor->rising(SENSOR_ID_SPECIAL)) {
        multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        if (m_lamp->lit(LAMP_ID_SPECIAL)) {
//            m_scoreboard->add_credit();
            m_lamp->set(LAMP_ID_SPECIAL, false);
        }
    }
}

void Toy::target_score(int lamp_id)
{
    if (m_lamp->lit(lamp_id)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
    } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
    }
}

void Toy::target_rules()
{
    if (m_sensor->rising(SENSOR_ID_DROP_10)) {
        target_score(LAMP_ID_TENS_BONUS);
        jacks_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_J1)) {
        target_score(LAMP_ID_JACKS_BONUS);
        jacks_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_J2)) {
        target_score(LAMP_ID_JACKS_BONUS);
        jacks_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_Q1)) {
        target_score(LAMP_ID_QUEENS_BONUS);
        queens_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_Q2)) {
        target_score(LAMP_ID_QUEENS_BONUS);
        queens_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_Q3)) {
        target_score(LAMP_ID_QUEENS_BONUS);
        queens_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K1)) {
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K2)) {
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K3)) {
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K4)) {
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A1)) {
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A2)) {
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A3)) {
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A4)) {
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_JOKER)) {
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
}

void Toy::apply_rules()
{
    rollover_rules();
    target_rules();
    if (m_sensor->rising(SENSOR_ID_BUMPER)) {
            multiscore(1, SOLENOID_ID_HUNDREDS_CHIME, 100);
    }
    if (m_sensor->rising(SENSOR_ID_TEN_POINT)) {
            multiscore(1, SOLENOID_ID_TENS_CHIME, 10);
    }
}

bool Toy::jacks_dropped() const
{
    if (!m_target->dropped(DROP_TARGET_ID_10))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_J1))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_J2))
        return false;
    return true;
}

bool Toy::queens_dropped() const
{
    if (!m_target->dropped(DROP_TARGET_ID_Q1))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_Q2))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_Q3))
        return false;
    return true;
}

bool Toy::kings_dropped() const
{
    if (!m_target->dropped(DROP_TARGET_ID_K1))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_K2))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_K3))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_K4))
        return false;
    return true;
}

bool Toy::aces_dropped() const
{
    if (!m_target->dropped(DROP_TARGET_ID_A1))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_A2))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_JOKER))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_A3))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_A4))
        return false;
    return true;
}

void Toy::jacks_test()
{
    if (jacks_dropped()) {
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_JACKS);
        multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
    }
}

void Toy::queens_test()
{
    if (queens_dropped()) {
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_QUEENS);
        multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
    }
}

void Toy::kings_test()
{
    if (kings_dropped()) {
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_KINGS);
        multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
    }
}

void Toy::aces_test()
{
    if (aces_dropped()) {
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_ACES);
        multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
    }
}





