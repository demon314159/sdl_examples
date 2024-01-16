//
// toy.cpp
//

#include "toy.h"
#include "flipper_model.h"
#include "pi.h"
#include <math.h>

#define ANIMATION_0_SPEED 30.0
#define ANIMATION_1_SPEED 180.0
#define ANIMATION_2_SPEED 15.0
#define ANIMATION_3_SPEED 30.0

#define ANIMATION_ID_0 2.0
#define ANIMATION_ID_1 3.0
#define ANIMATION_ID_2 4.0
#define ANIMATION_ID_3 5.0

#define BODY_COLOR PaintCan(1.0, 1.0, 0.0)
#define BUMPER_COLOR PaintCan(1.0, 0.0, 0.0)

#define BALL_RADIUS 1.0
#define BALL_TOP_COLOR PaintCan(1.0, 0.0, 0.0)
#define BALL_MIDDLE_COLOR PaintCan(1.0, 1.0, 1.0)
#define BALL_BOTTOM_COLOR PaintCan(0.0, 0.0, 1.0)

#define FLIPPER_MAJOR_RADIUS 1.0
#define FLIPPER_MINOR_RADIUS 0.4
#define FLIPPER_LENGTH 5.0
#define FLIPPER_HEIGHT 2.0

#define BUMPER_THICKNESS 0.2
#define BUMPER_HEIGHT 1.6

#define WALL_RADIUS 0.2
#define WALL_LENGTH 56.5685425
#define WALL_HEIGHT 2.0
#define WALL_SPACING ( (float) (WALL_LENGTH / (2.0 * sqrt(2.0))))

Toy::Toy()
    : m_model(new CadModel())
    , m_animation_0_angle(0.0)
    , m_animation_1_angle(0.0)
    , m_animation_2_angle(0.0)
    , m_animation_3_angle(0.0)
    , m_ball(BALL_RADIUS, BALL_TOP_COLOR, BALL_MIDDLE_COLOR, BALL_BOTTOM_COLOR)
    , m_wall(-45.0, {-WALL_SPACING, 0.0, WALL_SPACING})
{
    build_model();
    m_ball.set_velocity({-1.0, 1.0});
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

void collision_test(const Wall& wall)
{
    // translate wall to (0, 0) and bring ball position and velocity
    // rotate wall by -angle() and bring ball position and velocity
    // test for ball z position to be mode than -radius
    //    ( plus ball xposition within +/- WALL_LENGTH / 2.0 )
    //     ball z + radius < 0 ? return with no change to anything
    //     ball z + radius > 0 {
    //         translate wall by WALL_RADIUS + BUMPER_THICKNESS and bring ball position and velocity
    //         negate ball z velocity
    //         ball z pos -= (ball_z + radius)
    //         translate wall by -WALL_RADIUS - BUMPER_THICKNESS and bring ball position and velocity
    //         rotate wall by angle() and bring ball position and velocity
    //         translate wall to position() and bring ball position and velocity
    //     }


}

void Toy::advance(int nanoseconds)
{
    float seconds = 1.0e-9 * (float) nanoseconds;
    m_animation_0_angle += (ANIMATION_0_SPEED * seconds);
    m_animation_1_angle += (ANIMATION_1_SPEED * seconds);
    m_animation_2_angle += (ANIMATION_2_SPEED * seconds);
    m_animation_3_angle += (ANIMATION_3_SPEED * seconds);
    m_ball.advance(seconds);
    collision_test(m_wall);
}

void Toy::build_model()
{
    CadModel ball = m_ball.model(ANIMATION_ID_1);
    FlipperModel flipper(ANIMATION_ID_0, BODY_COLOR, BUMPER_COLOR, FLIPPER_MAJOR_RADIUS, FLIPPER_MINOR_RADIUS, FLIPPER_LENGTH, FLIPPER_HEIGHT, BUMPER_THICKNESS, BUMPER_HEIGHT);
    FlipperModel wall(0.0, BODY_COLOR, BUMPER_COLOR, WALL_RADIUS, WALL_RADIUS, WALL_LENGTH, WALL_HEIGHT, BUMPER_THICKNESS, BUMPER_HEIGHT);
    wall.translate(-WALL_LENGTH / 2.0, 0.0, 0.0);
    m_model->add(ball, 0.0, 0.0, 0.0);
    m_model->add(flipper, 0.0, 0.0, 0.0);

    wall.rotate_ay(m_wall.angle());
    Float3 pos = m_wall.position();
    m_model->add(wall, pos.v1, pos.v2, pos.v3);
    wall.rotate_ay(-m_wall.angle());


//    m_model->add(wall, -D, 0.0, -D);
//    m_model->add(wall, D, 0.0, D);
    wall.rotate_ay(-90.0);
//    m_model->add(wall, D, 0.0, -D);
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
        Float2 bp = m_ball.position();
        mm.translate(bp.v1, 0.0, bp.v2);
        mm.rotate(m_animation_1_angle, {f, 0.0, f});
    } else if (i == 2) {
        mm.rotate_ay(m_animation_2_angle);
    } else if (i == 3) {
        mm.rotate_ay(-m_animation_3_angle);
    }
    return mm;
}
