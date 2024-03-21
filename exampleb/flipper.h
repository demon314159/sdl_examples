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
    Flipper(float angle, Float3 position, float length, float major_radius, float minor_radius,
            float height, float rubber_thickness, float rubber_height,
            const PaintCan& body_color, const PaintCan& rubber_color,
            float travel, float velocity, float reflectivity, int steps);
    ~Flipper();

    CadModel model(float animation_id) const;
    void advance(float seconds);
    float angle() const;
    Float3 position() const;
    float angular_velocity() const;
    float travel() const;
    float active_angle() const;
    void set_active_angle(float angle);
    void collide(Ball* ball) const;
    void action_button(bool on);

private:
    bool m_action_button;
    float m_angle;
    Float3 m_position;
    float m_length;
    float m_major_radius;
    float m_minor_radius;
    float m_height;
    float m_rubber_thickness;
    float m_rubber_height;
    PaintCan m_body_color;
    PaintCan m_rubber_color;
    float m_travel;
    float m_velocity;
    int m_steps;
    float m_active_angle;
    float m_angular_velocity;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    StraightReflector m_reflector3;
    StraightReflector m_reflector4;
};

#endif // _FLIPPER_H_
