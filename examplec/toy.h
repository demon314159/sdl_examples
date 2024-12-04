//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "animated_toy.h"
#include "tray.h"
#include "token_set.h"
#include "puzzle_book.h"
#include "dock.h"
#include "hover.h"
#include "mouse_vector.h"
#include "push_button.h"
#include "message_panel.h"
#include "count.h"

class Toy: public AnimatedToy
{
public:
    Toy();
    ~Toy();

    void advance(int nanoseconds) override;
    bool quit_signal() const override;
    bool button(int code, bool shifted, bool on) override;
    bool mouse(SDL_Event* e, bool on) override;
    bool mouse_wheel(SDL_Event* e) override;
    bool mouse_move(SDL_Event* e) override;

private:
    bool m_quit_flag;
    Tray* m_tray;
    TokenSet* m_token_set;
    char** m_token_names;
    float m_seconds;
    PuzzleBook* m_puzzle_book;
    Dock* m_dock;
    Hover* m_hover;
    PushButton* m_pb_clear;
    PushButton* m_pb_next;
    PushButton* m_pb_quit;
    PushButton* m_pb_help;
    PushButton* m_pb_about;
    MessagePanel* m_msg_no_next;
    MessagePanel* m_msg_help;
    MessagePanel* m_msg_about;
    MessagePanel* m_msg_solved;
    MessagePanel* m_msg_no_more;
    MessagePanel* m_msg_game_over;
    MessagePanel* m_msg_status;
    Count* m_count;

    void build_model();
    void build_uniform();
    void update_uniform();
    void put_away_tokens();
    void set_up_current_challenge();
    Float2 mouse_selection(int sx, int sy) const;
    int selected_piece(float x, float y) const;
    int loosely_selected_piece(float x, float y) const;
    void lift_piece(int mx, int my);
    void drop_piece(int mx, int my);
    bool too_far_away(int mx, int my) const;
    void clear_board();
};

#endif // _TOY_H_
