//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"

Toy::Toy()
    : m_model(new CadModel())
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
        mm.rotate_ax(45.0);
        mm.translate(2.0, 0.0, 0.0);
    } else if (i == 1) {
        mm.translate(2.0, 0.0, 0.0);
        mm.rotate_ay(45.0);
        mm.translate(-2.0, 0.0, 0.0);
    } else if (i == 2) {
        mm.translate(0.0, 0.0, -2.0);
        mm.rotate_az(45.0);
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
