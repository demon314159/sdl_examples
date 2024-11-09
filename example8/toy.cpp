//
// toy.cpp
//

#include "toy.h"

#define TRACK_LANES 4

Toy::Toy()
    : m_track(new Track(TRACK_LANES))
    , m_model(new CadModel())
    , m_animation_0_angle(0.0)
    , m_animation_1_angle(0.0)
    , m_animation_2_angle(0.0)
    , m_animation_3_angle(0.0)
    , m_seconds(0.0)
    , m_log(new Log())
{
    build_model();
}

Toy::~Toy()
{
    delete m_model;
    delete m_log;
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
    m_log->render(nanoseconds);
    m_seconds += (1.0e-9 * (float) nanoseconds);
    float seconds = 1.0e-3;
    while (m_seconds > seconds) {
        m_seconds -= seconds;
        m_track->advance(1000000);
    }
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
    Double3 cp = m_track->car_position(i);
    mm.translate(cp.v1, cp.v2, cp.v3);
    mm.rotate_ay(m_track->car_yaw(i));
    mm.rotate_az(m_track->car_pitch(i));
    return mm;
}

