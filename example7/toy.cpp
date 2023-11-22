//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"

#define ANIMATION_0_SPEED 5.0
#define ANIMATION_1_SPEED 10.0
#define ANIMATION_2_SPEED 15.0

Toy::Toy()
    : m_model(new CadModel())
    , m_animation_0_angle(0.0)
    , m_animation_1_angle(0.0)
    , m_animation_2_angle(0.0)
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
    return 3;
}

void Toy::advance(int nanoseconds)
{
    float ns = 1.0e-9 * (float) nanoseconds;
    m_animation_0_angle += (ANIMATION_0_SPEED * ns);
    m_animation_1_angle += (ANIMATION_1_SPEED * ns);
    m_animation_2_angle += (ANIMATION_2_SPEED * ns);
}

void Toy::build_model()
{
    CadModel rcm = CadModel(CubeShape(1.0, 1.0, 1.0), PaintCan(1.0, 0.0, 0.0), ANIMATION_0_ID);
    CadModel gcm = CadModel(CubeShape(1.0, 1.0, 1.0), PaintCan(0.0, 1.0, 0.0), ANIMATION_1_ID);
    CadModel bcm = CadModel(CubeShape(1.0, 1.0, 1.0), PaintCan(0.0, 0.0, 1.0), ANIMATION_2_ID);
    m_model->add(rcm, -2.0, 0.0, 0.0);
    m_model->add(gcm, 2.0, 0.0, 0.0);
    m_model->add(bcm, 0.0, 0.0, -2.0);
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
    }
    return mm;
//        Matrix4x4 car_matrix;
//        Double3 cp = m_track->car_position(car_id);
//        car_matrix.unity();
//        car_matrix.translate(cp.v1, cp.v2, cp.v3);
//        car_matrix.rotate_ay(m_track->car_yaw(car_id));
//        car_matrix.rotate_az(m_track->car_pitch(car_id));
}
