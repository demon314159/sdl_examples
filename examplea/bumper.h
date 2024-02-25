//
// bumper.h
//

#ifndef _BUMPER_H_
#define _BUMPER_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "convex_reflector.h"

class Bumper
{
public:
    Bumper(Float3 position, float reflectivity);
    ~Bumper();

    CadModel model(float animation_id) const;
    Float3 position() const;
    void collide(Ball& ball) const;

private:
    Float3 m_position;
    ConvexReflector m_reflector;
};

#endif // _BUMPER_H_
