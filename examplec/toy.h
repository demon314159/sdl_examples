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

class Toy: public AnimatedToy
{
public:
    Toy();
    ~Toy();

    void advance(int nanoseconds) override;

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
    void set_up_current_challenge();
};

#endif // _TOY_H_
