//
// wall.h
//

#ifndef _WALL_H_
#define _WALL_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "convex_reflector.h"
#include "straight_reflector.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class Wall
{
public:
    Wall(float angle, Float3 position, float length, float reflectivity);
    ~Wall();

    CadModel model(float animation_id) const;
    float angle() const;
    Float3 position() const;
    float length() const;
    void collide(Ball& ball) const;

private:
    float m_angle;
    Float3 m_position;
    float m_length;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    StraightReflector m_reflector3;
    StraightReflector m_reflector4;
};

#endif // _WALL_H_
