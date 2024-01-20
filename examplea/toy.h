//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "cad_model.h"
#include "matrix4x4.h"
#include "ball.h"
#include "wall.h"
#include "flipper.h"

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

    void advance(int nanoseconds);

private:
    CadModel* m_model;
    float m_animation_0_angle;
    float m_animation_1_angle;
    float m_animation_2_angle;
    float m_animation_3_angle;
    Wall m_wall1;
    Wall m_wall2;
    Wall m_wall3;
    Wall m_wall4;
    Wall m_wall5;
    Flipper m_flipper1;
    Flipper m_flipper2;
    Ball m_ball;

    void build_model();
    bool within_range(const Wall& wall, const Ball& ball) const;
    void collide(const Wall& wall, Ball& ball);
};

#endif // _TOY_H_
