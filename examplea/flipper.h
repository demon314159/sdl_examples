//
// flipper.h
//

#ifndef _FLIPPER_H_
#define _FLIPPER_H_

#include "cad_model.h"
#include "float3.h"
#include "matrix4x4.h"
#include "quaternion.h"
#include "ball.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class Flipper
{
public:
    Flipper(float angle, Float3 position, float travel);
    ~Flipper();

    CadModel model(float animation_id) const;
//    void advance(float seconds);
    float angle() const;
    Float3 position() const;
    float travel() const;
    float active_angle() const;
    void set_active_angle(float angle);
//    Matrix4x4 animation_matrix() const;
    void collide(Ball& ball) const;

private:
    float m_angle;
    Float3 m_position;
    float m_travel;
    float m_active_angle;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    StraightReflector m_reflector3;
    StraightReflector m_reflector4;
};

#endif // _FLIPPER_H_
