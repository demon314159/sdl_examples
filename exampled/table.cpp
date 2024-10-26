//
// table.cpp
//

#include "table.h"
#include "plane_shape.h"
#include "cube_shape.h"

Table::Table()
    : m_ball_z_limit(0.0)
    , m_ball_home_position({0.0, 0.0})
{
    m_ball_home_position = {(X7 + X8) / 2.0f, ZOH2 + BALL_RADIUS / 2.0f - BALL_RADIUS};
    m_ball_z_limit = Z8;
}

Table::~Table()
{
}

float Table::ball_z_limit() const
{
return m_ball_z_limit;
}

Float2 Table::ball_home_position() const
{
    return m_ball_home_position;
}

Float2 Table::out_hole_position() const
{
    return {0.144f, 0.11975f};
}

void Table::collide(Ball* ball) const
{
}

CadModel Table::model() const
{
    CadModel mm;
    CadModel top_playfield(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, TEXTURE_ID_PLAYFIELD), PaintCan(1.0, 1.0, 1.0), ANIMATION_ID_TRANSPARENT);
    CadModel backlight(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, 0.0), PaintCan(0.0, 0.0, 0.0), 1.0);
    mm.add(backlight, PLAYFIELD_X / 2.0, -0.002f, PLAYFIELD_Z / 2.0);
    mm.add(top_playfield, PLAYFIELD_X / 2.0, 0.0, PLAYFIELD_Z / 2.0);
    return mm;
}

Float2 Table::trim() const
{
    return {T1, Y4};
}

PaintCan Table::trim_color() const
{
    return WOOD_COLOR;
}
