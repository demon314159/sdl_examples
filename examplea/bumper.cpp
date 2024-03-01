//
// bumper.cpp
//

#include "bumper.h"
#include "bumper_model.h"

Bumper::Bumper(Float3 position,
               float wall_radius, float stem_radius, float wall_height, float stem_height,
               const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color,
               float kicker_velocity, int steps)
    : m_position(position)
    , m_wall_radius(wall_radius)
    , m_stem_radius(stem_radius)
    , m_wall_height(wall_height)
    , m_stem_height(stem_height)
    , m_top_color(top_color)
    , m_middle_color(middle_color)
    , m_bottom_color(bottom_color)
    , m_steps(steps)
    , m_kicker(wall_radius, kicker_velocity)
{
    m_kicker.translate({position.v1, position.v3});
}

Bumper::~Bumper()
{
}

void Bumper::collide(Ball& ball) const
{
    m_kicker.collide(ball);
}

CadModel Bumper::model(float animation_id) const
{
    BumperModel bumper(animation_id, m_top_color, m_middle_color, m_bottom_color,
                       m_wall_radius, m_stem_radius, m_wall_height, m_stem_height, m_steps);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(bumper, pos.v1, pos.v2, pos.v3);
    return mm;
}
