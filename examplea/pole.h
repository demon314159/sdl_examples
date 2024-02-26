//
// pole.h
//

#ifndef _POLE_H_
#define _POLE_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "convex_kicker.h"

class Pole
{
public:
    Pole(Float3 position, float radius, float height, float bumper_thickness, float bumper_height,
         const PaintCan& body_color, const PaintCan& bumper_color,
         float kicker_velocity, int steps);
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
    float m_bumper_thickness;
    float m_bumper_height;
    PaintCan m_body_color;
    PaintCan m_bumper_color;
    int m_steps;
    ConvexKicker m_kicker;
};

#endif // _POLE_H_
