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

class Flipper
{
public:
    Flipper(float angle, Float3 position);
    ~Flipper();

    CadModel model(float animation_id) const;
//    void advance(float seconds);
    float angle() const;
    Float3 position() const;
//    Matrix4x4 animation_matrix() const;
    void collide(Ball& ball) const;

private:
    float m_angle;
    Float3 m_position;
};

#endif // _FLIPPER_H_
