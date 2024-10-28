//
// trap.h
//

#ifndef _TRAP_H_
#define _TRAP_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class Trap
{
public:
    Trap(Float2 p1, float radius);
    ~Trap();

    void collide(Ball* ball) const;

private:
    Float2 m_p1;
    float m_radius;
};

#endif // _TRAP_H_
