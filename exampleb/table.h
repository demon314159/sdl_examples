//
// table.h
//

#ifndef _TABLE_H_
#define _TABLE_H_

#include "straight_strip.h"
#include "concave_strip.h"
#include "cad_model.h"
#include "float3.h"
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
    float ball_z_limit() const;
    Float2 ball_home_position() const;

private:
    float m_ball_z_limit;
    Float2 m_ball_home_position;
    StraightStrip* m_strip1;
    StraightStrip* m_strip2;
    StraightStrip* m_strip3;
    StraightStrip* m_strip4;
    StraightStrip* m_strip5;
    StraightStrip* m_strip6;
    StraightStrip* m_strip7;
    StraightStrip* m_strip8;
    ConcaveStrip* m_strip9;
    StraightStrip* m_strip10;

    float R1 = 0.148;
    float R2 = 0.145;
    float ANGLE1 = 0.0;
    float ANGLE2 = 145.452;
    float ANGLE3 = 30.12;
    float ANGLE4 = 59.7693;
    float T1 = 0.008;
    float Y1 = 0.018;
    float X1 =  0.003;
    float X3 = X1 + R2 * cos(ANGLE3 * PI / 180.0);
    float X6 = 0.288;
    float X5 = X6 - R2 * cos(ANGLE3 * PI / 180.0);
    float X8 = 0.314;
    float X0 = X1 - T1;
    float X7 = X6 + T1;
    float X9 = X8 + T1;
    float X4 = X8 - R1;
    float X2 = X4 + R1 * cos(ANGLE2 * PI / 180.0);
    float ZA = 0.1476;
    float Z3 = 0.150;
    float Z4 = 0.161;
    float Z5 = 0.520;
    float Z6 = Z5 + R2 * sin(ANGLE3 * PI / 180.0);
    float Z9 = PLAYFIELD_Z - T1;
    float Z0 = 0.0;
    float Z1 = T1;
    float Z7 = 0.57725;
    float Z8 = 0.610;
    float Z10 = PLAYFIELD_Z;
    float Z2 = Z4 - R1 * sin(ANGLE2 * PI / 180.0);
    int TOP_PANEL_STEPS = 200;
    float R4 = sqrt((X2 - X1) * (X2 - X1) + (ZA - Z2) * (ZA - Z2));
};

#endif // _TABLE_H_