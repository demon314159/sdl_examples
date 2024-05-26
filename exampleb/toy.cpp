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

#define MAX_UNIFORMS 100
#define MAX_TEXTURES 20

#define INITIAL_CREDITS 8
#define MAX_BALLS 4

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
    , m_texture(NULL)
    , m_score(NULL)
    , m_queue(NULL)
    , m_game(NULL)
    , m_execute(NULL)
    , m_table(NULL)
    , m_left_flipper(NULL)
    , m_right_flipper(NULL)
    , m_top_flipper(NULL)
    , m_model(NULL)
    , m_uniform(NULL)
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
    m_texture = new Texture(MAX_TEXTURES);
    m_texture->add("playfield.png", "texture1");
    m_texture->add("plastic1.png", "texture2");
    m_texture->add("plastic2.png", "texture3");
    m_texture->add("plastic3.png", "texture4");
    m_texture->add("plastic4.png", "texture5");
    m_texture->add("plastic5.png", "texture6");
    m_texture->add("plastic6.png", "texture7");
    m_texture->add("plastic7.png", "texture8");
    m_texture->add("plastic8.png", "texture9");
    m_texture->add("plastic9.png", "texture10");
    m_texture->add("score.png", "texture11");
    m_texture->add("backglass.png", "texture12");

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
    m_uniform = new Uniform(MAX_UNIFORMS);
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
    build_uniform();
    m_queue = new Queue();
    m_score = new Score(m_scoreboard, m_lamp);

    m_score->set_high_game(120000);
    m_score->set_match(70);
    m_game = new Game(INITIAL_CREDITS, m_scoreboard->max_players(), MAX_BALLS, m_sensor, m_target, m_lamp, m_queue, m_score);
    m_execute = new Execute(m_queue, m_score, m_lamp);

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
    delete m_game;
    delete m_execute;
    delete m_scoreboard;
    delete m_texture;
    delete m_table;
    delete m_left_flipper;
    delete m_right_flipper;
    delete m_top_flipper;
    delete m_model;
    delete m_uniform;
}

void Toy::initialize()
{
    m_sound->initialize();
}

CadModel* Toy::model() const
{
    return m_model;
}

Uniform* Toy::uniform()
{
    // Update all uniform data sources
    m_lamp->data();
    m_scoreboard->data();
    m_target->data();
    // Return pointer to uniform object
    return m_uniform;
}

void Toy::build_uniform()
{
    m_uniform->add("lamp_color", UNIFORM_TYPE_3_FLOAT_VECTOR, m_lamp->lamps(), (void*) m_lamp->data());
    for (int i = 0; i < m_texture->textures(); i++) {
        m_uniform->add(m_texture->uniform_name(i), UNIFORM_TYPE_1_INTEGER_VECTOR, 1, m_texture->data(i));
    }
    m_uniform->add("score", UNIFORM_TYPE_1_FLOAT_VECTOR, m_scoreboard->digits(), m_scoreboard->data());
    m_uniform->add("target_height", UNIFORM_TYPE_1_FLOAT_VECTOR, m_target->targets(), m_target->data());
}

Texture* Toy::texture()
{
    return m_texture;
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
            m_sound->play(SOUND_ID_KNOCKER);
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
        m_game->apply_rules();
        m_score->advance(seconds);
        int solenoid_id = m_execute->advance(seconds);
        activate_solenoid(solenoid_id);
    }
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

void Toy::button(int code, bool shifted, bool on)
{
    switch (code) {
        case SDL_SCANCODE_LSHIFT:  // Left flipper
            m_left_flipper->action_button(on);
            break;
        case SDL_SCANCODE_RSHIFT:  // Right flipper
            m_right_flipper->action_button(on);
            m_top_flipper->action_button(on);
            break;
        case SDL_SCANCODE_L:  // Launch button
            if (on && !m_last_launch_action_button) {
                if ((m_ball->position().v2 > (m_table->ball_home_position().v2 - BALL_RADIUS))
                    && (m_ball->position().v1 > (m_table->ball_home_position().v1 - BALL_RADIUS))) {
                    m_ball->set_velocity({0.0, -BALL_LAUNCH_SPEED});
                }
            }
            m_last_launch_action_button = on;
            break;
        case SDL_SCANCODE_R:  // Add player
            if (on) {
                m_game->add_player();
            }
            break;
        default:
            break;
    }
}

