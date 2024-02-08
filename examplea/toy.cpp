//
// toy.cpp
//

#include "toy.h"
#include "flipper_model.h"
#include "pi.h"
#include <math.h>
#include "look.h"

#define ANIMATION_0_SPEED 0.0
#define ANIMATION_1_SPEED 0.0
#define ANIMATION_2_SPEED 15.0
#define ANIMATION_3_SPEED 30.0

#define ANIMATION_ID_0 2.0
#define ANIMATION_ID_1 3.0
#define ANIMATION_ID_2 4.0
#define ANIMATION_ID_3 5.0

#define W1 40.0
#define W2 40.0
#define W3 13.0
#define W4 (W3 + 1.0)
#define L1 40.0
#define L2 20.0
#define L3 1.5
#define THETA4 (-(180.0 / PI) * (atan2(L2, (W2 - W3) / 2.0)))
#define THETA5 ((180.0 / PI) * (atan2(L2, (W2 - W3) / 2.0)))
#define THETA 50.0

#define WALL1_LENGTH W1
#define WALL2_LENGTH L1
#define WALL3_LENGTH L1
#define WALL4_LENGTH sqrt(((W2 - W3) / 2.0) * ((W2 - W3) / 2.0) + L2 * L2)
#define WALL5_LENGTH WALL4_LENGTH

#define FLIPPER_TRAVEL 70.0

Toy::Toy()
    : m_model(new CadModel())
    , m_animation_0_angle(0.0)
    , m_animation_1_angle(0.0)
    , m_animation_2_angle(0.0)
    , m_animation_3_angle(0.0)
    , m_ball(BALL_RADIUS, BALL_TOP_COLOR, BALL_MIDDLE_COLOR, BALL_BOTTOM_COLOR)
    , m_wall1(0.0, {0.0, 0.0, 0.0}, WALL1_LENGTH)
    , m_wall2(-90, {(-W1 / 2.0 - W2 / 2.0) / 2.0, 0.0, L1 / 2.0}, WALL2_LENGTH)
    , m_wall3(90.0, {(W1 / 2.0 + W2 / 2.0) / 2.0, 0.0, L1 / 2.0}, WALL3_LENGTH)
    , m_wall4(THETA4, {(-W2 / 2.0 - W3 / 2.0) / 2.0, 0.0, L1 + L2 / 2.0}, WALL4_LENGTH)
    , m_wall5(THETA5, {(W2 / 2.0 + W3 / 2.0) / 2.0, 0.0, L1 + L2 / 2.0}, WALL5_LENGTH)

    , m_flipper1(-THETA, {-W4 / 2.0, 0.0, L1 + L2 + L3}, FLIPPER_TRAVEL)
    , m_flipper2(180.0 + THETA, {W4 / 2.0, 0.0, L1 + L2 + L3}, -FLIPPER_TRAVEL)
{
    build_model();
    m_ball.set_position({-4.0, 10.0});
    m_ball.set_velocity({0.0, 5.0});
    m_ball.set_acceleration({0.0, 10.0});
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
    float seconds = 1.0e-9 * (float) nanoseconds;
    m_animation_0_angle += (ANIMATION_0_SPEED * seconds);
    m_animation_1_angle += (ANIMATION_1_SPEED * seconds);
    m_animation_2_angle += (ANIMATION_2_SPEED * seconds);
    m_animation_3_angle += (ANIMATION_3_SPEED * seconds);
    m_flipper1.advance(seconds);
    m_flipper2.advance(seconds);
    m_ball.advance(seconds);
    m_wall1.collide(m_ball);
    m_wall2.collide(m_ball);
    m_wall3.collide(m_ball);
    m_wall4.collide(m_ball);
    m_wall5.collide(m_ball);
    m_flipper1.collide(m_ball);
    m_flipper2.collide(m_ball);
}

void Toy::build_model()
{
    m_model->add(m_ball.model(ANIMATION_ID_2));
    m_model->add(m_flipper1.model(ANIMATION_ID_0));
    m_model->add(m_flipper2.model(ANIMATION_ID_1));
    m_model->add(m_wall1.model(0.0));
    m_model->add(m_wall2.model(0.0));
    m_model->add(m_wall3.model(0.0));
    m_model->add(m_wall4.model(0.0));
    m_model->add(m_wall5.model(0.0));
}

Matrix4x4 Toy::get_animation_matrix(int i) const
{
    Matrix4x4 mm;

    mm.unity();
    if (i == 0) {
        mm.translate(m_flipper1.position().v1, m_flipper1.position().v2, m_flipper1.position().v3);
        mm.rotate_ay(m_animation_0_angle + m_flipper1.active_angle());
        mm.translate(-m_flipper1.position().v1, -m_flipper1.position().v2, -m_flipper1.position().v3);
    } else if (i == 1) {
        mm.translate(m_flipper2.position().v1, m_flipper2.position().v2, m_flipper2.position().v3);
        mm.rotate_ay(m_animation_1_angle + m_flipper2.active_angle());
        mm.translate(-m_flipper2.position().v1, -m_flipper2.position().v2, -m_flipper2.position().v3);
    } else if (i == 2) {
        mm = m_ball.animation_matrix();
    } else if (i == 3) {
        mm.rotate_ay(-m_animation_3_angle);
    }
    return mm;
}

void Toy::left_action_button(bool on)
{
    m_flipper1.action_button(on);
}

void Toy::right_action_button(bool on)
{
    m_flipper2.action_button(on);
}

