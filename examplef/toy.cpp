//
// toy.cpp
//

#include "toy.h"
#include "pi.h"
#include <math.h>
#include "look.h"

#define INITIAL_HEIGHT 512
#define INITIAL_WIDTH ((INITIAL_HEIGHT * 1920) / 1080)

#define INITIAL_XOFF  -0.0175
#define INITIAL_YOFF  0.020
#define INITIAL_XROT 90.0
#define INITIAL_YROT 0.0
#define INITIAL_MAG  1.0
#define BALL_MAX_ACCELERATION 2.05

Toy::Toy(Options* options)
    : AnimatedToy(options)
    , m_seconds(0.0)
{
    m_camera->reconstruct(INITIAL_WIDTH, INITIAL_HEIGHT, INITIAL_MAG, {INITIAL_XOFF, INITIAL_YOFF}, {INITIAL_XROT, INITIAL_YROT});
    build_model();
    m_camera->frame(m_model);
    build_uniform();
}

Toy::~Toy()
{
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
}

void Toy::build_uniform()
{
    for (int i = 0; i < m_texture->textures(); i++) {
        m_uniform->add(m_texture->uniform_name(i), UNIFORM_TYPE_1_INTEGER_VECTOR, 1, m_texture->data(i));
    }
}

void Toy::advance(int nanoseconds)
{
    AnimatedToy::advance(nanoseconds);
    m_seconds += (1.0e-9 * (float) nanoseconds);
    float seconds = 1.0e-3;
    while (m_seconds > seconds) {
        m_seconds -= seconds;
    }
    update_uniform();
}

void Toy::build_model()
{
    m_model->clear();
    m_model->add(m_options->file_name(), PaintCan(1.0, 1.0, 0.25), 0.0);
    m_model->rotate_ay(180.0);
    m_model->rotate_az(180.0);
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

