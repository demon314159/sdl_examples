//
// toy.cpp
//

#include "toy.h"
#include <math.h>
#include <stdio.h>

#define ANIMATION_ID_FIRST_TOKEN 2.0
#define ANIMATION_ID_PB_CLEAR 42.0
#define ANIMATION_ID_PB_NEXT 43.0
#define ANIMATION_ID_PB_BACK 44.0
#define ANIMATION_ID_PB_QUIT 45.0
#define ANIMATION_ID_PB_HELP 46.0

#define TEXTURE_ID_PB_CLEAR 1.0
#define TEXTURE_ID_PB_NEXT 2.0
#define TEXTURE_ID_PB_BACK 3.0
#define TEXTURE_ID_PB_QUIT 4.0
#define TEXTURE_ID_PB_HELP 5.0

#define ANIMATION_NAME_LENGTH 32
#define TRAY_ROWS 6
#define TRAY_COLS 10

#define ANIMATION_TIME 0.4

#define PUSH_BUTTON_RADIUS (TILE_PITCH)
#define PUSH_BUTTON_HEIGHT (TILE_PITCH / 4.0)

//#define CLEAR_BUTTON_POSITION {-10.0 * TILE_PITCH, -4.0 * TILE_PITCH}
//#define NEXT_BUTTON_POSITION {20.0 * TILE_PITCH, 10.0 * TILE_PITCH}
//#define BACK_BUTTON_POSITION {-10.0 * TILE_PITCH, 10.0 * TILE_PITCH}
//#define QUIT_BUTTON_POSITION {20.0 * TILE_PITCH, -4.0 * TILE_PITCH}
//#define HELP_BUTTON_POSITION {20.0 * TILE_PITCH, 5.0 * TILE_PITCH}

#define QUIT_BUTTON_POSITION {20.0 * TILE_PITCH, 10.0 * TILE_PITCH}
#define NEXT_BUTTON_POSITION {20.0 * TILE_PITCH, 6.5 * TILE_PITCH}
#define BACK_BUTTON_POSITION {20.0 * TILE_PITCH, 3.0 * TILE_PITCH}
#define CLEAR_BUTTON_POSITION {20.0 * TILE_PITCH, -0.5 * TILE_PITCH}
#define HELP_BUTTON_POSITION {20.0 * TILE_PITCH, -4.0 * TILE_PITCH}

Toy::Toy()
    : m_quit_flag(false)
    , m_tray(new Tray(TRAY_ROWS, TRAY_COLS))
    , m_token_set(new TokenSet())
    , m_token_names(new char*[m_token_set->tokens()])
    , m_seconds(0.0)
    , m_puzzle_book(new PuzzleBook(PUZZLE_BOOK_FILE_NAME))
    , m_dock(new Dock(TILE_PITCH))
    , m_hover(new Hover())
    , m_pb_clear(new PushButton(PUSH_BUTTON_RADIUS, PUSH_BUTTON_HEIGHT, CLEAR_BUTTON_POSITION))
    , m_pb_next(new PushButton(PUSH_BUTTON_RADIUS, PUSH_BUTTON_HEIGHT, NEXT_BUTTON_POSITION))
    , m_pb_back(new PushButton(PUSH_BUTTON_RADIUS, PUSH_BUTTON_HEIGHT, BACK_BUTTON_POSITION))
    , m_pb_quit(new PushButton(PUSH_BUTTON_RADIUS, PUSH_BUTTON_HEIGHT, QUIT_BUTTON_POSITION))
    , m_pb_help(new PushButton(PUSH_BUTTON_RADIUS, PUSH_BUTTON_HEIGHT, HELP_BUTTON_POSITION))
{
    m_texture->add("pb_clear.png", "texture1");
    m_texture->add("pb_next.png", "texture2");
    m_texture->add("pb_back.png", "texture3");
    m_texture->add("pb_quit.png", "texture4");
    m_texture->add("pb_help.png", "texture5");
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
    delete m_pb_help;
    delete m_pb_quit;
    delete m_pb_back;
    delete m_pb_next;
    delete m_pb_clear;
    delete m_hover;
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
    m_model->add(m_tray->model(0.0), 0.0, -TILE_HEIGHT, 0.0);
    m_model->add(m_pb_clear->model(ANIMATION_ID_PB_CLEAR, TEXTURE_ID_PB_CLEAR), 0.0, 0.0, 0.0);
    m_model->add(m_pb_next->model(ANIMATION_ID_PB_NEXT, TEXTURE_ID_PB_NEXT), 0.0, 0.0, 0.0);
    m_model->add(m_pb_back->model(ANIMATION_ID_PB_BACK, TEXTURE_ID_PB_BACK), 0.0, 0.0, 0.0);
    m_model->add(m_pb_quit->model(ANIMATION_ID_PB_QUIT, TEXTURE_ID_PB_QUIT), 0.0, 0.0, 0.0);
    m_model->add(m_pb_help->model(ANIMATION_ID_PB_HELP, TEXTURE_ID_PB_HELP), 0.0, 0.0, 0.0);
}

void Toy::put_away_tokens()
{
    for (int i = 0; i < m_token_set->tokens(); i++) {
        m_token_set->set_position(i, TILE_PITCH * (float) 4.0, -2.0f * TILE_HEIGHT, 0, 0.0);
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
        if (m_puzzle_book->on_board(i)) {
            m_token_set->set_board_position(m_puzzle_book->token_id(i), m_puzzle_book->posh(i), m_puzzle_book->posv(i), m_puzzle_book->orientation(i), m_dock);
        } else {
            m_token_set->set_dock_position(m_puzzle_book->token_id(i), m_dock->dock_id(i), m_puzzle_book->orientation(i), m_dock);
        }
    }
}

void Toy::clear_board()
{
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        if (m_puzzle_book->on_board(i) && !m_puzzle_book->locked(i)) {
            m_puzzle_book->lift_piece(i);
        }
        if (!m_puzzle_book->on_board(i)) {
            m_puzzle_book->set_orientation(i, 0);
        }
    }
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
        if (!m_puzzle_book->on_board(i)) {
            m_token_set->set_dock_position(m_puzzle_book->token_id(i), m_dock->dock_id(i), m_puzzle_book->orientation(i), m_dock, ANIMATION_TIME);
        }
    }
}

void Toy::build_uniform()
{
    for (int i = 0; i < m_texture->textures(); i++) {
        m_uniform->add(m_texture->uniform_name(i), UNIFORM_TYPE_1_INTEGER_VECTOR, 1, m_texture->data(i));
    }
    for (int i = 0; i < m_token_set->tokens(); i++) {
        m_uniform->add(m_token_names[i], UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_token_set->data(i));
    }
    m_uniform->add("animation_40_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_pb_clear->data());
    m_uniform->add("animation_41_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_pb_next->data());
    m_uniform->add("animation_42_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_pb_back->data());
    m_uniform->add("animation_43_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_pb_quit->data());
    m_uniform->add("animation_44_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_pb_help->data());
}

void Toy::update_uniform()
{
    // Update all uniform data sources
    for (int i = 0; i < m_token_set->tokens(); i++) {
        m_token_set->data(i);
    }
    m_pb_clear->data();
    m_pb_next->data();
    m_pb_back->data();
    m_pb_quit->data();
    m_pb_help->data();
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

bool Toy::quit_signal() const
{
    return m_quit_flag;
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
        case SDL_SCANCODE_C:
            clear_board();
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
        } else {
        }
    } else if (e->button.button == SDL_BUTTON_LEFT) {
        if (on) {
            Float2 sel = mouse_selection(e->button.x, e->button.y);
            if (m_pb_clear->mouse_hit(sel)) {
                clear_board();
            } else if (m_pb_next->mouse_hit(sel)) {
                m_puzzle_book->go_to_next_challenge();
                set_up_current_challenge();
            } else if (m_pb_back->mouse_hit(sel)) {
                m_puzzle_book->go_to_previous_challenge();
                set_up_current_challenge();
            } else if (m_pb_quit->mouse_hit(sel)) {
                m_quit_flag = true;
            } else if (m_pb_help->mouse_hit(sel)) {
            } else {
                lift_piece(e->button.x, e->button.y);
            }
        } else {
            m_pb_clear->release();
            m_pb_next->release();
            m_pb_back->release();
            m_pb_quit->release();
            m_pb_help->release();
            drop_piece(e->button.x, e->button.y);
        }
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
        if (on) {
            Float2 sel = mouse_selection(e->button.x, e->button.y);
            int lsp = loosely_selected_piece(sel.v1, sel.v2);
            if (lsp >= 0) {
                if (!m_puzzle_book->on_board(lsp)) {
                    int orientation = m_puzzle_book->orientation(lsp);
                    bool flipped = (orientation > 3);
                    int rot = orientation & 3;
                    int token_id = m_puzzle_book->token_id(lsp);
                    if (rot & 1) {
                        rot = rot ^ 2;
                    }
                    int new_rot = flipped ? rot : rot | 4;
                    if (m_token_set->set_dock_position(token_id, m_dock->dock_id(lsp), new_rot, m_dock, ANIMATION_TIME)) {
                        m_puzzle_book->set_orientation(lsp, new_rot);
                    }
                }
            }
        } else {
        }
    }
    return false;
}

bool Toy::mouse_wheel(SDL_Event* e)
{
    int angle = e->wheel.y;
    if (angle != 0) {
        Float2 sel = mouse_selection(e->wheel.mouseX, e->wheel.mouseY);
        int lsp = loosely_selected_piece(sel.v1, sel.v2);
        if (lsp >= 0) {
            if (!m_puzzle_book->on_board(lsp)) {
                int orientation = m_puzzle_book->orientation(lsp);
                bool flipped = (orientation > 3);
                int rot = orientation & 3;
                int token_id = m_puzzle_book->token_id(lsp);
                if (angle > 0) {
                    int new_rot = (rot - 1) & 3;
                    new_rot = flipped ? new_rot | 4 : new_rot;
                    if (m_token_set->set_dock_position(token_id, m_dock->dock_id(lsp), new_rot, m_dock, ANIMATION_TIME)) {
                        m_puzzle_book->set_orientation(lsp, new_rot);
                    }
                } else {
                    int new_rot = (rot + 1) & 3;
                    new_rot = flipped ? new_rot | 4 : new_rot;
                    if (m_token_set->set_dock_position(token_id, m_dock->dock_id(lsp), new_rot, m_dock, ANIMATION_TIME)) {
                        m_puzzle_book->set_orientation(lsp, new_rot);
                    }
                }
            }
        }
    }
    return false;
}

bool Toy::too_far_away(int mx, int my) const
{
    if (m_hover->on()) {
        int sp = m_hover->piece_id();
        if (m_puzzle_book->locked(sp)) {
            Float2 sel = mouse_selection(mx, my);
            Float3 offset = m_hover->offset();
            float ph = sel.v1 + offset.v1;
            float pv = sel.v2 - offset.v3;
            float posh = TILE_PITCH * m_puzzle_book->posh(sp);
            float posv = TILE_PITCH * m_puzzle_book->posv(sp);
            if (fabs(ph - posh) > TILE_PITCH) {
                return true;
            }
            if (fabs(pv - posv) > TILE_PITCH) {
                return true;
            }
        }
    }
    return false;
}

bool Toy::mouse_move(SDL_Event* e)
{
    if (m_hover->on()) {
        int sp = m_hover->piece_id();
        int token_id = m_puzzle_book->token_id(sp);
        int orientation = m_puzzle_book->orientation(sp);
        if (too_far_away(e->motion.x, e->motion.y)) {
            m_hover->stop();
            int posh = m_puzzle_book->posh(sp);
            int posv = m_puzzle_book->posv(sp);
            m_token_set->set_board_position(token_id, posh, posv, orientation, m_dock, ANIMATION_TIME / 2.0);

        } else {
            Float2 sel = mouse_selection(e->motion.x, e->motion.y);
            Float3 offset = m_hover->offset();
            m_token_set->set_position(token_id, sel.v1 + offset.v1, TILE_HEIGHT, -sel.v2 + offset.v3, orientation, 0.0);
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
           float px = TILE_PITCH * (float) posh + position.v1;
           float pz = TILE_PITCH * (float) posv - position.v3;
           if ( (fabs(x - px) < (TILE_PITCH / 2.0f)) && (fabs(y - pz) < (TILE_PITCH / 2.0f)) ) {
               return i;
           }
       }
    }
    return -1;
}

int Toy::loosely_selected_piece(float x, float y) const
{
    for (int i = 0; i < m_puzzle_book->pieces(); i++) {
       int token_id = m_puzzle_book->token_id(i);
       int orientation = m_puzzle_book->orientation(i);
       Float3 position = m_token_set->position(token_id);
       float horz_center = m_token_set->horz_center(token_id, orientation, TILE_PITCH);
       float vert_center = m_token_set->vert_center(token_id, orientation, TILE_PITCH);
       Float2 center = {position.v1 + horz_center, -position.v3 + vert_center};
       float dx = x - center.v1;
       float dz = y - center.v2;
       float distance = sqrt(dx * dx + dz * dz);
       float radius = 3.0 * TILE_PITCH;
       if (distance <= radius) {
           return i;
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

void Toy::lift_piece(int mx, int my)
{
    Float2 sel = mouse_selection(mx, my);
    int sp = selected_piece(sel.v1, sel.v2);
    if (sp >= 0) {
        int token_id = m_puzzle_book->token_id(sp);
        Float3 tpos = m_token_set->position(token_id);
        m_hover->start(sp, tpos.v1 - sel.v1, 0.0, tpos.v3 + sel.v2);
        if (m_puzzle_book->on_board(sp)) {
            m_puzzle_book->lift_piece(sp);
        }
    }
}

void Toy::drop_piece(int mx, int my)
{
    if (m_hover->on()) {
        int sp = m_hover->piece_id();
        int token_id = m_puzzle_book->token_id(sp);
        int orientation = m_puzzle_book->orientation(sp);
        Float3 offset = m_hover->offset();
        m_hover->stop();
        if (m_puzzle_book->locked(sp)) {
            int posh = m_puzzle_book->posh(sp);
            int posv = m_puzzle_book->posv(sp);
            m_token_set->set_board_position(token_id, posh, posv, orientation, m_dock, ANIMATION_TIME);
        } else {
            Float2 sel = mouse_selection(mx, my);
            float px = sel.v1 + offset.v1;
            float pz = sel.v2 - offset.v3;
            int ipx = round(px / TILE_PITCH);
            int ipz = round(pz / TILE_PITCH);
            if (m_puzzle_book->drop_piece(m_token_set, sp, orientation, ipx, ipz)) {
                m_token_set->set_board_position(token_id, ipx, ipz, orientation, m_dock, 0.0);
            } else {
                m_token_set->set_dock_position(token_id, m_dock->dock_id(sp), orientation, m_dock, ANIMATION_TIME);
            }
        }
    }
}

