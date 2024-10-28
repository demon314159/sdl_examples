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
#include "trap.h"

#include <math.h>

class Table
{
public:
    Table();
    ~Table();
    CadModel model() const;
    void collide(Ball* ball) const;
    void trap(Ball* ball) const;
    Float2 ball_home_position() const;

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
    Wall* m_wall16a;
    Wall* m_wall16b;
    Wall* m_wall17;
    Wall* m_wall18;
    Wall* m_wall19;
    Wall* m_wall20;
    Wall* m_wall21a;
    Wall* m_wall21b;
    Wall* m_wall22;
    Wall* m_wall23;
    Wall* m_wall24;
    Wall* m_wall25;
    Wall* m_wall26;
    Wall* m_wall27;
    Wall* m_wall28;
    Wall* m_wall29;
    Wall* m_wall30;
    Wall* m_wall31;
    Wall* m_wall32;
    Wall* m_wall33;
    Trap* m_trap1;
    Trap* m_trap2;
    Trap* m_trap3;
    Trap* m_trap4;
    Trap* m_trap5;
    Trap* m_trap6;
    Trap* m_trap7;
    Trap* m_trap8;
    Trap* m_trap9;
    Trap* m_trap10;
    Trap* m_trap11;
    Trap* m_trap12;
    Trap* m_trap13;
    Trap* m_trap14;
    Trap* m_trap15;
    Trap* m_trap16;
    Trap* m_trap17;
    Trap* m_trap18;
    Trap* m_trap19;
    Trap* m_trap20;
    Trap* m_trap21;
    Trap* m_trap22;
    Trap* m_trap23;
    Trap* m_trap24;
    Trap* m_trap25;
};

#endif // _TABLE_H_
