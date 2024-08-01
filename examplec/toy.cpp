//
// toy.cpp
//

#include "toy.h"
#include <stdio.h>

#define ANIMATION_ID_FIRST_TOKEN 2.0
#define ANIMATION_NAME_LENGTH 32
#define TRAY_ROWS 6
#define TRAY_COLS 10

Toy::Toy()
    : m_tray(new Tray(TRAY_ROWS, TRAY_COLS))
    , m_token_set(new TokenSet())
    , m_token_names(new char*[m_token_set->tokens()])
    , m_seconds(0.0)
{
    for (int i = 0; i < m_token_set->tokens(); i++) {
        m_token_names[i] = new char[ANIMATION_NAME_LENGTH];
        sprintf(m_token_names[i], "animation_%d_matrix", i);
    }
    build_model();
    build_uniform();
}

Toy::~Toy()
{
    for (int i = 0; i < m_token_set->tokens(); i++) {
        delete [] m_token_names[i];
    }
    delete [] m_token_names;
    delete m_token_set;
    delete m_tray;
}

void Toy::build_model()
{
    float sep = 0.050;
    float pitch = 0.010;
    m_model->clear();
    for (int i = 0; i < m_token_set->tokens(); i++) {
        m_model->add(m_token_set->model(i, ANIMATION_ID_FIRST_TOKEN + (float) i));
        int xpos = i & 7;
        int zpos = (i >> 3) & 7;
          m_token_set->set_position(i, pitch * (float) 4.0, -0.002, 0.0);
    }
    m_token_set->set_position(1, 0.0, 0.0, 0.0);
    m_token_set->set_position(39, 9.0 * pitch, 0.0, -0.0);
    m_token_set->set_position(4, 1.0 * pitch, 0.0, -0.0 * pitch);
    m_token_set->set_position(13, 5.0 * pitch, 0.0, -2.0 * pitch);
    m_token_set->set_angle_az(13, 180.0);
    m_token_set->set_angle_ay(13, -90.0);

//    m_token_set->set_position(5, pitch * 0.0, 0.0, -pitch * 7.0);
//    m_token_set->set_position(7, pitch * 9.0, 0.0, -pitch * 7.0);
//    m_token_set->set_position(11, pitch * 0.0, 0.0, pitch * 5.0);
//    m_token_set->set_position(14, pitch * 9.0, 0.0, pitch * 5.0);
//    m_token_set->set_position(37, -pitch * 5.0, 0.0, -pitch * 1.0);
//    m_token_set->set_position(28, pitch * 13.0, 0.0, -pitch * 1.0);

    m_token_set->set_dock_position(5, 0, pitch);
    m_token_set->set_dock_position(7, 1, pitch);
    m_token_set->set_dock_position(11, 2, pitch);
    m_token_set->set_dock_position(14, 3, pitch);
    m_token_set->set_dock_position(37, 4, pitch);
    m_token_set->set_dock_position(28, 5, pitch);

    m_token_set->set_dock_position(29, 6, pitch);
    m_token_set->set_dock_position(30, 7, pitch);
    m_token_set->set_dock_position(31, 8, pitch);
    m_token_set->set_dock_position(32, 9, pitch);

    m_model->add(m_tray->model(0.0), 0.0, -0.001, 0.0);
}

void Toy::build_uniform()
{
    for (int i = 0; i < m_token_set->tokens(); i++) {
        m_uniform->add(m_token_names[i], UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_token_set->data(i));
    }
}

void Toy::update_uniform()
{
    // Update all uniform data sources
    for (int i = 0; i < m_token_set->tokens(); i++) {
        m_token_set->data(i);
    }
}

void Toy::advance(int nanoseconds)
{
    AnimatedToy::advance(nanoseconds);
    m_seconds += (1.0e-9 * (float) nanoseconds);
    float seconds = 1.0e-3;
    while (m_seconds > seconds) {
        m_seconds -= seconds;

        m_token_set->advance(seconds);

    }
    update_uniform();
}
