//
// wall.h
//

#ifndef _WALL_H_
#define _WALL_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class Wall
{
public:
    Wall(Float2 p1, Float2 p2, float radius, float height,
         const PaintCan& color, int reflectivity, int steps);
    ~Wall();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;

private:
    Float2 m_p1;
    Float2 m_p2;
    float m_radius;
    float m_height;
    PaintCan m_color;
    int m_steps;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    StraightReflector m_reflector3;
    StraightReflector m_reflector4;
};

#endif // _WALL_H_
