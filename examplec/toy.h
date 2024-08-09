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
#include "mouse_vector.h"

class Toy: public AnimatedToy
{
public:
    Toy();
    ~Toy();

    void advance(int nanoseconds) override;
    bool button(int code, bool shifted, bool on) override;
    bool mouse(SDL_Event* e, bool on) override;
    bool mouse_wheel(SDL_Event* e) override;

private:
    Tray* m_tray;
    TokenSet* m_token_set;
    char** m_token_names;
    float m_seconds;
    PuzzleBook* m_puzzle_book;
    Dock* m_dock;

    void build_model();
    void build_uniform();
    void update_uniform();
    void put_away_tokens();
    void set_up_current_challenge();
    Float2 mouse_selection(int sx, int sy) const;
    int selected_piece(float x, float y) const;
    int loosely_selected_piece(float x, float y) const;
};

#endif // _TOY_H_
