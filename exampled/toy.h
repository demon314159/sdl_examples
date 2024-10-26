//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "animated_toy.h"
#include "ball.h"
#include "table.h"
#include <SDL_scancode.h>

class Toy: public AnimatedToy
{
public:
    Toy();
    ~Toy();

    void resize(int w, int h) override;
    void initialize() override;
    bool button(int code, bool shifted, bool on) override;
    bool mouse(SDL_Event* e, bool on) override;
    void advance(int nanoseconds) override;

private:
    float m_seconds;
    Ball* m_ball;
    Table* m_table;

    bool m_last_launch_action_button;
    void build_model();
    void build_uniform();
    void update_uniform();
};

#endif // _TOY_H_
