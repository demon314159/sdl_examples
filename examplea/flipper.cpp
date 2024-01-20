//
// flipper.cpp
//

#include "flipper.h"
#include "flipper_model.h"
#include "look.h"

Flipper::Flipper(float angle, Float3 position)
    : m_angle(angle)
    , m_position(position)
{

}

Flipper::~Flipper()
{
}

float Flipper::angle() const
{
    return m_angle;
}

Float3 Flipper::position() const
{
    return m_position;
}

void Flipper::collide(Ball& ball) const
{
}

CadModel Flipper::model(float animation_id) const
{
    FlipperModel flipper(animation_id, BODY_COLOR, BUMPER_COLOR, FLIPPER_MAJOR_RADIUS, FLIPPER_MINOR_RADIUS, FLIPPER_LENGTH, FLIPPER_HEIGHT, BUMPER_THICKNESS, BUMPER_HEIGHT);
    flipper.rotate_ay(m_angle);
    CadModel mm;
    mm.add(flipper);
    return mm;
}
