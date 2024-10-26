//
// toy.cpp
//

#include "toy.h"
#include "pi.h"
#include <math.h>
#include "look.h"

#define INITIAL_HEIGHT 512
#define INITIAL_WIDTH ((INITIAL_HEIGHT * 1920) / 1080)

//#define INITIAL_XOFF  0.050
//#define INITIAL_YOFF  0.0
//#define INITIAL_XROT 50.0
//#define INITIAL_YROT 10.0
//#define INITIAL_MAG  2.55

#define INITIAL_XOFF  0.0
#define INITIAL_YOFF  0.004f
#define INITIAL_XROT 90.0
#define INITIAL_YROT 0.0
#define INITIAL_MAG  1.6
#define BALL_ACCELERATION 0.00

Toy::Toy()
    : m_seconds(0.0)
    , m_ball(NULL)
    , m_table(NULL)
{
    m_camera->reconstruct(INITIAL_WIDTH, INITIAL_HEIGHT, INITIAL_MAG, {INITIAL_XOFF, INITIAL_YOFF}, {INITIAL_XROT, INITIAL_YROT});
    m_ball = new Ball(BALL_RADIUS, BALL_TOP_COLOR, BALL_MIDDLE_COLOR, BALL_BOTTOM_COLOR, BALL_SEGMENTS);
    m_table = new Table();
    m_texture->add("playfield.png", "texture1");

    build_model();
    m_camera->frame(m_model);
    build_uniform();
    m_ball->set_position(m_table->out_hole_position());
    m_ball->set_velocity({0.0, 0.0});
    m_ball->set_acceleration({0.0, BALL_ACCELERATION});
}

Toy::~Toy()
{
    delete m_ball;
    delete m_table;
}

void Toy::resize(int w, int h)
{
    AnimatedToy::resize(w, h);
}

void Toy::initialize()
{
    AnimatedToy::initialize();
}

void Toy::update_uniform()
{
    // Update all uniform data sources
    m_ball->data();
}

void Toy::build_uniform()
{
    for (int i = 0; i < m_texture->textures(); i++) {
        m_uniform->add(m_texture->uniform_name(i), UNIFORM_TYPE_1_INTEGER_VECTOR, 1, m_texture->data(i));
    }
    m_uniform->add("animation_3_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_ball->data());
}

void Toy::advance(int nanoseconds)
{
    AnimatedToy::advance(nanoseconds);
    m_seconds += (1.0e-9 * (float) nanoseconds);
    float seconds = 1.0e-3;
    while (m_seconds > seconds) {
        m_seconds -= seconds;
        m_ball->advance(seconds);
        m_ball->advance_orientation();
    }
    update_uniform();
}

void Toy::build_model()
{
    m_model->clear();
    m_model->add(m_ball->model(ANIMATION_ID_BALL));
    m_model->add(m_table->model());
}

bool Toy::button(int code, bool shifted, bool on)
{
    bool ret_val = AnimatedToy::button(code, shifted, on);
    if (!ret_val)
        return false;
    switch (code) {
        case SDL_SCANCODE_LSHIFT:  // Left flipper
            break;
        case SDL_SCANCODE_RSHIFT:  // Right flipper
            break;
        case SDL_SCANCODE_L:  // Launch button
        case SDL_SCANCODE_SPACE:  // Spacebar button
            break;
        case SDL_SCANCODE_C:  // Credit button
            break;
        case SDL_SCANCODE_X:  // Show camera data
            if (on) {
                m_camera->show();
            }
            break;
        case SDL_SCANCODE_UP:
            break;
        case SDL_SCANCODE_DOWN:
            break;
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_RIGHT:
            break;
        default:
            break;
    }
    return ret_val;
}

bool Toy::mouse(SDL_Event* e, bool on)
{
    bool ret_val = AnimatedToy::mouse(e, on);
    if (!ret_val)
        return false;

    return true;
}

