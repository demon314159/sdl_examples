//
// wall.h
//

#ifndef _WALL_H_
#define _WALL_H_

#include "float3.h"

class Wall
{
public:
    Wall(float angle, Float3 position);
    ~Wall();

    float angle() const;
    Float3 position() const;

private:
    float m_angle;
    Float3 m_position;
};

#endif // _WALL_H_
