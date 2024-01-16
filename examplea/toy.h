//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "cad_model.h"
#include "matrix4x4.h"
#include "ball.h"
#include "wall.h"

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
    Wall m_wall;
    Ball m_ball;

    void build_model();
};

#endif // _TOY_H_
