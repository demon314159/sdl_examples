//
// flat_rail.h
//

#ifndef _FLAT_RAIL_H_
#define _FLAT_RAIL_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
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
    ConcaveReflector m_reflector1;
    ConcaveReflector m_reflector2;
    StraightReflector m_reflector3;
};

#endif // _FLAT_RAIL_H_
