//
// toy.cpp
//

#include "toy.h"

#define TRACK_LANES 4

#define ANIMATION_0_SPEED 180.0
#define ANIMATION_1_SPEED 90.0
#define ANIMATION_2_SPEED 15.0
#define ANIMATION_3_SPEED 30.0

Toy::Toy()
    : m_track(new Track(TRACK_LANES))
    , m_model(new CadModel())
    , m_animation_0_angle(0.0)
    , m_animation_1_angle(0.0)
    , m_animation_2_angle(0.0)
    , m_animation_3_angle(0.0)
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
}

void Toy::build_model()
{
    for (int i = 0; i < m_track->sections(); i++) {
        CadModel cm = m_track->section(i)->cad_model();
        m_model->add(cm, 0.0, 0.0, 0.0);
    }
    for (int i = 0; i < m_track->cars(); i++) {
        m_track->car(i)->set_lane(i);
        CadModel car = m_track->car(i)->cad_model(i);
        m_model->add(car, 0.0, 0.0, 0.0);
    }
}

Matrix4x4 Toy::get_animation_matrix(int i) const
{
    Matrix4x4 mm;

    mm.unity();
    if (i == 0) {
        mm.translate(-2.0, 0.0, 0.0);
        mm.rotate_ax(m_animation_0_angle);
        mm.translate(2.0, 0.0, 0.0);
    } else if (i == 1) {
        mm.translate(2.0, 0.0, 0.0);
        mm.rotate_ay(m_animation_1_angle);
        mm.translate(-2.0, 0.0, 0.0);
    } else if (i == 2) {
        mm.translate(0.0, 0.0, -2.0);
        mm.rotate_az(m_animation_2_angle);
        mm.translate(0.0, 0.0, 2.0);
    } else if (i == 3) {
        mm.translate(0.0, 2.0, -2.0);
        mm.rotate_az(m_animation_3_angle);
        mm.translate(0.0, -2.0, 2.0);
    }
    return mm;
//        Matrix4x4 car_matrix;
//        Double3 cp = m_track->car_position(car_id);
//        car_matrix.unity();
//        car_matrix.translate(cp.v1, cp.v2, cp.v3);
//        car_matrix.rotate_ay(m_track->car_yaw(car_id));
//        car_matrix.rotate_az(m_track->car_pitch(car_id));
}
