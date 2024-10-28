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
#include "well.h"

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
    Well* m_well1;
    Well* m_well2;
    Well* m_well3;
    Well* m_well4;
    Well* m_well5;
    Well* m_well6;
    Well* m_well7;
    Well* m_well8;
    Well* m_well9;
    Well* m_well10;
    Well* m_well11;
    Well* m_well12;
    Well* m_well13;
    Well* m_well14;
    Well* m_well15;
    Well* m_well16;
    Well* m_well17;
    Well* m_well18;
    Well* m_well19;
    Well* m_well20;
    Well* m_well21;
    Well* m_well22;
    Well* m_well23;
    Well* m_well24;
    Well* m_well25;
};

#endif // _TABLE_H_
