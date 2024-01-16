//
// wall.cpp
//

#include "wall.h"

Wall::Wall(float angle, Float3 position)
    : m_angle(angle)
    , m_position(position)
{

}

Wall::~Wall()
{
}

float Wall::angle() const
{
    return m_angle;
}

Float3 Wall::position() const
{
    return m_position;
}
