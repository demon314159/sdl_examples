//
// well.h
//

#ifndef _WELL_H_
#define _WELL_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class Well
{
public:
    Well(Float2 p1, float radius, float depth);
    ~Well();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;

private:
    Float2 m_p1;
    float m_radius;
    float m_depth;
};

#endif // _WELL_H_
