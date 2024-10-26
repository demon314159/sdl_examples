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
    float ball_z_limit() const;
    Float2 ball_home_position() const;
    Float2 out_hole_position() const;
    Float2 trim() const;
    PaintCan trim_color() const;

private:
    float m_ball_z_limit;
    Float2 m_ball_home_position;

    float R1 = 0.148;
    float R2A = 0.138;
    float R2B = 0.135;

    float T1 = 0.010;
    float Y1 = 0.010;
    float Y2 = 0.017;
    float Y3 = 0.018;
    float Y4 = Y2 - 0.0005;
    float ANGLE1 = 0.0;
    float ANGLE2 = 145.452;

    float ANGLE3A = 29.75;
    float ANGLE3B = 30.5;

    float ANGLE4 = 59.7693;
    float ANGLE5 = ANGLE2 - 10.0;
    float ANGLE6 = 53.0;
    float X1 =  0.007;
    float X6 = 0.283;
    float X8 = 0.312;
    float Z0 = 0.0;
    float Z1 = T1;
    float ZA = 0.1476 - 0.017;
    float Z3 = 0.164;
    float Z4 = 0.161;
    float Z5 = 0.520;
    float Z7 = 0.57725;
    float Z8 = 0.640;
    float ZOH1 = 0.524;
    float ZOH2 = 0.542;
    int TOP_PANEL_STEPS = 200;
    float X0 = X1 - T1;
    float X3 = X1 + R2A * cos(ANGLE3A * PI / 180.0);
    float X5 = X6 - R2B * cos(ANGLE3B * PI / 180.0);
    float X7 = X6 + T1;
    float X9 = X8 + T1;
    float X4 = X8 - R1;
    float X2 = X4 + R1 * cos(ANGLE2 * PI / 180.0);
    float Z2 = Z4 - R1 * sin(ANGLE2 * PI / 180.0);
    float Z6 = Z5 + R2A * sin(ANGLE3A * PI / 180.0);
    float Z9 = PLAYFIELD_Z - T1 + 0.01;
    float Z10 = PLAYFIELD_Z + 0.01;
    float R4 = sqrt((X2 - X1) * (X2 - X1) + (ZA - Z2) * (ZA - Z2));
    float TB = (X8 - X7) * 0.7;
    float TDIODE = (X8 - X7) * 1.4;
    float YB = BALL_RADIUS * 2.0 * 1.414;
    float XB = X4 + (R1 - TB / 2.0) * cos(ANGLE5 * PI / 180.0);
    float ZB = Z4 - (R1 - TB / 2.0) * sin(ANGLE5 * PI / 180.0);
    float XC = X4 + (R1 - TB / 2.0) * cos(ANGLE6 * PI / 180.0);
    float ZC = Z4 - (R1 - TB / 2.0) * sin(ANGLE6 * PI / 180.0);
    float TC = TDIODE / 10.0;
};

#endif // _TABLE_H_
