//
// bumper.cpp
//

#include "bumper.h"
#include "bumper_model.h"
#include "look.h"

Bumper::Bumper(Float3 position, float reflectivity)
    : m_position(position)
    , m_reflector(BUMPER_RADIUS + BUMPER_THICKNESS, reflectivity)
{
    m_reflector.translate({position.v1, position.v3});
}

Bumper::~Bumper()
{
}

Float3 Bumper::position() const
{
    return m_position;
}

void Bumper::collide(Ball& ball) const
{
    m_reflector.collide(ball);
}

CadModel Bumper::model(float animation_id) const
{
    BumperModel bumper(animation_id, BODY_COLOR, BUMPER_COLOR, BUMPER_RADIUS, WALL_HEIGHT, BUMPER_THICKNESS, BUMPER_HEIGHT);
    Float3 pos = m_position;
    CadModel mm;
    mm.add(bumper, pos.v1, pos.v2, pos.v3);
    return mm;
}
