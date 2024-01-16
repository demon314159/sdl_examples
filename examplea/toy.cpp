//
// toy.cpp
//

#include "toy.h"
#include "flipper_model.h"
#include "ball_model.h"
#include "pi.h"
#include <math.h>

#define ANIMATION_0_SPEED 30.0
#define ANIMATION_1_SPEED 180.0
#define ANIMATION_2_SPEED 15.0
#define ANIMATION_3_SPEED 30.0

Toy::Toy()
    : m_model(new CadModel())
    , m_animation_0_angle(0.0)
    , m_animation_1_angle(0.0)
    , m_animation_2_angle(0.0)
    , m_animation_3_angle(0.0)
    , m_ball_position({0.0, 0.0, 0.0})
    , m_ball_velocity({-1.0, 0.0, 1.0})
{
    build_model();
}

Toy::~Toy()
{
    delete m_model;
}

CadModel* Toy::get_model() const
{
    return m_model;
}

int Toy::animation_matrices() const
{
    return 4;
}

void Toy::advance(int nanoseconds)
{
    float ns = 1.0e-9 * (float) nanoseconds;
    m_animation_0_angle += (ANIMATION_0_SPEED * ns);
    m_animation_1_angle += (ANIMATION_1_SPEED * ns);
    m_animation_2_angle += (ANIMATION_2_SPEED * ns);
    m_animation_3_angle += (ANIMATION_3_SPEED * ns);
    m_ball_position.v1 += (m_ball_velocity.v1 * ns);
    m_ball_position.v3 += (m_ball_velocity.v3 * ns);
}

void Toy::build_model()
{
    float D = 20.0;
    float L = sqrt( 8.0 * D * D);
    BallModel ball(3.0, PaintCan(1.0, 0.0, 0.0), PaintCan(1.0, 1.0, 1.0), PaintCan(0.0, 0.0, 1.0), 1.0);
    FlipperModel flipper(2.0, PaintCan(1.0, 1.0, 0.0), PaintCan(1.0, 0.0, 0.0), 1.0, 0.4, 5.0, 2.0, 0.2, 1.6);
    FlipperModel wall(0.0, PaintCan(1.0, 1.0, 0.0), PaintCan(1.0, 0.0, 0.0), 0.2, 0.2, L, 2.0, 0.2, 1.6);
    wall.translate(-L / 2.0, 0.0, 0.0);
    m_model->add(ball, 0.0, 0.0, 0.0);
    m_model->add(flipper, 0.0, 0.0, 0.0);
    wall.rotate_ay(45.0);
    m_model->add(wall, -D, 0.0, -D);
    m_model->add(wall, D, 0.0, D);
    wall.rotate_ay(-90.0);
    m_model->add(wall, -D, 0.0, D);
    m_model->add(wall, D, 0.0, -D);
    m_model->magnify(0.5);
}

Matrix4x4 Toy::get_animation_matrix(int i) const
{
    Matrix4x4 mm;
    float f = 1.0 / sqrt(2.0);

    mm.unity();
    if (i == 0) {
        mm.translate(-2.0, 0.0, 0.0);
        mm.rotate_ay(m_animation_0_angle);
    } else if (i == 1) {
        mm.translate(m_ball_position.v1, 0.0, m_ball_position.v3);
        mm.rotate(m_animation_1_angle * PI / 180.0, {f, 0.0, f});
//        Quaternion q(m_animation_1_angle * PI / 180.0, {f, 0.0, f});
//        mm = mm * q.to_matrix();
//        mm.rotate_ax(m_animation_1_angle);
    } else if (i == 2) {
        mm.rotate_ay(m_animation_2_angle);
    } else if (i == 3) {
        mm.rotate_ay(-m_animation_3_angle);
    }
    return mm;
}
