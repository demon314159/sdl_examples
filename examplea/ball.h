//
// ball.h
//

#ifndef _BALL_H_
#define _BALL_H_

#include "cad_model.h"
#include "float3.h"
#include "matrix4x4.h"
#include "quaternion.h"

class Ball
{
public:
    Ball(float radius, const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color);
    ~Ball();

    CadModel model(float animation_id) const;
    void advance(float seconds);
    float radius() const;
    Float2 position() const;
    Float2 velocity() const;
    Float2 acceleration() const;
    void set_position(Float2 position);
    void set_velocity(Float2 velocity);
    void rotate_frame(float angle);
    void translate_velocity_frame(Float2 velocity);
    void translate_frame(Float2 distance);
    Matrix4x4 animation_matrix() const;

private:
    float m_radius;
    PaintCan m_top_color;
    PaintCan m_middle_color;
    PaintCan m_bottom_color;
    Float2 m_position;
    Float2 m_velocity;
    Quaternion m_orientation;
};

#endif // _BALL_H_
