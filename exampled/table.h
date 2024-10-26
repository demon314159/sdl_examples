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
};

#endif // _TABLE_H_
