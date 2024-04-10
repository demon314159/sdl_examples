//
// flat_rail.h
//

#ifndef _FLAT_RAIL_H_
#define _FLAT_RAIL_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "convex_reflector.h"
#include "concave_reflector.h"
#include "straight_reflector.h"

class FlatRail
{
public:
    FlatRail(Float2 p, float length, float width, float thickness, float bend_radius, float height,
             const PaintCan& color, float reflectivity, int steps);
    ~FlatRail();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;

private:
    Float2 m_p;
    float m_length;
    float m_width;
    float m_thickness;
    float m_bend_radius;
    float m_height;
    PaintCan m_color;
    int m_steps;
//    ConvexReflector m_reflector1;
//    ConvexReflector m_reflector2;
//    ConcaveReflector m_reflector3;
//    StraightReflector m_reflector4;
//    StraightReflector m_reflector5;
//    ConvexReflector m_reflector6;
//    ConcaveReflector m_reflector7;
//    ConvexReflector m_reflector8;
};

#endif // _FLAT_RAIL_H_
