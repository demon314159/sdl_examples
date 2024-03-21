//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "cad_model.h"
#include "matrix4x4.h"
#include "lamp.h"
#include "ball.h"
#include "flipper.h"
#include "table.h"

class Toy
{
public:
    #define ANIMATION_0_ID 2.0
    #define ANIMATION_1_ID 3.0
    #define ANIMATION_2_ID 4.0
    #define ANIMATION_3_ID 5.0

    Toy();
    ~Toy();

    CadModel* get_model() const;
    int animation_matrices() const;
    Matrix4x4 get_animation_matrix(int i) const;

    void left_action_button(bool on);
    void right_action_button(bool on);
    void launch_action_button(bool on);

    void advance(int nanoseconds);

    const Lamp* get_lamp() const;

private:
    Ball* m_ball;
    Lamp* m_lamp;
    Table* m_table;
    Flipper* m_left_flipper;
    Flipper* m_right_flipper;
    Flipper* m_top_flipper;
    CadModel* m_model;
    bool m_last_launch_action_button;
    double m_ns_count;
    void build_model();
};

#endif // _TOY_H_
