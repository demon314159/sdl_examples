//
// table.h
//

#ifndef _TABLE_H_
#define _TABLE_H_

#include "ball.h"
#include "cad_model.h"
#include "float3.h"
#include "matrix4x4.h"
#include "pi.h"
#include "look.h"
#include "concave_strip.h"
#include "wall.h"

#include <math.h>

class Table
{
public:
    Table();
    ~Table();
    CadModel model() const;
    void collide(Ball* ball) const;
    Float2 ball_home_position() const;
    Float2 out_hole_position() const;

private:
    Float2 m_ball_home_position;
    ConcaveStrip* m_strip1;
    ConcaveStrip* m_strip2;
    Wall* m_wall1;
    Wall* m_wall2;
    Wall* m_wall3;
    Wall* m_wall4;
    Wall* m_wall5;
    Wall* m_wall6;
    Wall* m_wall7;
    Wall* m_wall8;
    Wall* m_wall9;
    Wall* m_wall10;
    Wall* m_wall11;
    Wall* m_wall12;
    Wall* m_wall13;
    Wall* m_wall14;
    Wall* m_wall15;
};

#endif // _TABLE_H_
