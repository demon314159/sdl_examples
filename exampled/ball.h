//
// ball.h
//

#ifndef _BALL_H_
#define _BALL_H_

#include "perimeter.h"
#include "cad_model.h"
#include "float3.h"
#include "matrix4x4.h"
#include "quaternion.h"
#include "state.h"

class Ball
{
public:
    Ball(float radius, const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color, int steps);
    ~Ball();

    CadModel model(float animation_id) const;
    void advance(float seconds);
    void advance_orientation();
    float radius() const;
    Float2 position() const;
    Float2 velocity() const;
    Float2 acceleration() const;
    void set_position(Float2 position);
    void set_velocity(Float2 velocity);
    void set_acceleration(Float2 acceleration);
    void rotate_frame(float angle);
    void translate_velocity_frame(Float2 velocity);
    void translate_frame(Float2 distance);
    bool quick_test(const Perimeter& perimeter) const;

    const float* data();

private:
    float m_radius;
    PaintCan m_top_color;
    PaintCan m_middle_color;
    PaintCan m_bottom_color;
    int m_steps;
    Float2 m_acceleration;
    State m_state;
    State m_last_state;
    Quaternion m_orientation;
    Matrix4x4 m_animation;

    State rates(const State& state) const;
    State next_state(double dt) const;
    Quaternion next_orientation();
};

#endif // _BALL_H_
