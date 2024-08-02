//
// toy.cpp
//

#include "toy.h"
#include <math.h>
#include <stdio.h>

#define ANIMATION_ID_FIRST_TOKEN 2.0
#define ANIMATION_NAME_LENGTH 32
#define TRAY_ROWS 6
#define TRAY_COLS 10

#define PITCH 0.010

Toy::Toy()
    : m_tray(new Tray(TRAY_ROWS, TRAY_COLS))
    , m_token_set(new TokenSet())
    , m_token_names(new char*[m_token_set->tokens()])
    , m_seconds(0.0)
    , m_puzzle_book(new PuzzleBook(PUZZLE_BOOK_FILE_NAME))
    , m_dock(new Dock(PITCH))
{
    for (int i = 0; i < m_token_set->tokens(); i++) {
        m_token_names[i] = new char[ANIMATION_NAME_LENGTH];
        sprintf(m_token_names[i], "animation_%d_matrix", i);
    }
    put_away_tokens();
    build_model();
    build_uniform();
    set_up_current_challenge();
}

Toy::~Toy()
{
    delete m_dock;
//    m_puzzle_book->save(PUZZLE_BOOK_FILE_NAME);

    delete m_puzzle_book;
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
    m_model->clear();
    for (int i = 0; i < m_token_set->tokens(); i++) {
        m_model->add(m_token_set->model(i, ANIMATION_ID_FIRST_TOKEN + (float) i));
    }
    m_model->add(m_tray->model(0.0), 0.0, -0.001, 0.0);
}

void Toy::put_away_tokens()
{
    for (int i = 0; i < m_token_set->tokens(); i++) {
        m_token_set->set_position(i, PITCH * (float) 4.0, -0.002, 0.0);
        m_token_set->set_orientation(i, 0);
    }
}

void Toy::set_up_current_challenge()
{
    m_dock->clear();
    put_away_tokens();
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        if (!m_puzzle_book->locked(i)) {
            m_dock->assign_slot(i);
        }
    }
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        if (m_puzzle_book->locked(i)) {
            m_dock->assign_slot(i);
        }
    }
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        m_token_set->set_orientation(m_puzzle_book->token_id(i), m_puzzle_book->orientation(i), 0.0);
        if (m_puzzle_book->on_board(i)) {
            m_token_set->set_board_position(m_puzzle_book->token_id(i), m_puzzle_book->posh(i), m_puzzle_book->posv(i), m_puzzle_book->orientation(i), m_dock);
        } else {
            m_token_set->set_dock_position(m_puzzle_book->token_id(i), m_dock->dock_id(i), m_dock);
        }
    }
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

bool Toy::button(int code, bool shifted, bool on)
{
    bool ret_val = AnimatedToy::button(code, shifted, on);
    if (!ret_val)
        return false;
    switch (code) {
        case SDL_SCANCODE_LEFT:
            if (on) {
                m_puzzle_book->go_to_previous_challenge();
                set_up_current_challenge();
            }
            ret_val = false;
            break;
        case SDL_SCANCODE_RIGHT:
            if (on) {
                m_puzzle_book->go_to_next_challenge();
                set_up_current_challenge();
            }
            ret_val = false;
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
    if (e->button.button == SDL_BUTTON_MIDDLE) {
        if (on) {
            printf("middle button on (%d, %d)\n", e->button.x, e->button.y);
        } else {
            printf("middle button off (%d, %d)\n", e->button.x, e->button.y);
        }
    } else if (e->button.button == SDL_BUTTON_LEFT) {
        if (on) {
            printf("left button on (%d, %d)\n", e->button.x, e->button.y);
            Float2 sel = mouse_selection(e->button.x, e->button.y);
            printf("    mouse_selection = (%5.3f, %5.3f)\n", sel.v1, sel.v2);
            int sp = selected_piece(sel.v1, sel.v2);
            printf("    selected piece = %d\n", sp);
        } else {
            printf("left button off (%d, %d)\n", e->button.x, e->button.y);
        }
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
        if (on) {
            printf("right button on (%d, %d)\n", e->button.x, e->button.y);
        } else {
            printf("right button off (%d, %d)\n", e->button.x, e->button.y);
        }
    }

    return false;
}

int Toy::selected_piece(float x, float y) const
{
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
       int token_id = m_puzzle_book->token_id(i);
       int orientation = m_puzzle_book->orientation(i);
       Float3 position = m_token_set->position(token_id);
       for (int j = 0; j < m_token_set->tiles(token_id); j++) {
           int posh = m_token_set->posh(token_id, j, orientation);
           int posv = m_token_set->posv(token_id, j, orientation);
           float px = PITCH * (float) posh + position.v1;
           float pz = PITCH * (float) posv - position.v3;
           if ( (fabs(x - px) < (PITCH / 2.0f)) && (fabs(y - pz) < (PITCH / 2.0f)) ) {
               return i;
           }
       }
    }
    return -1;
}

Float2 Toy::mouse_selection(int sx, int sy) const
{
    MouseVector mv = m_camera->new_mouse_vector(sx, sy);
    Float3 ip = mv.intersection_point(mv.origin().v2);
    return {ip.v1, -ip.v3};
}
