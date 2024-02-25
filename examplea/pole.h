//
// pole.h
//

#ifndef _POLE_H_
#define _POLE_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "convex_reflector.h"

class Pole
{
public:
    Pole(Float3 position, float radius, float height, float reflectivity);
    ~Pole();

    CadModel model(float animation_id) const;
    Float3 position() const;
    float radius() const;
    float height() const;
    void collide(Ball& ball) const;

private:
    Float3 m_position;
    float m_radius;
    float m_height;
    ConvexReflector m_reflector;
};

#endif // _POLE_H_
