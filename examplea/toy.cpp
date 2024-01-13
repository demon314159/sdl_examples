//
// toy.cpp
//

#include "toy.h"
#include "flipper_model.h"

#define ANIMATION_0_SPEED 30.0
#define ANIMATION_1_SPEED 90.0
#define ANIMATION_2_SPEED 15.0
#define ANIMATION_3_SPEED 30.0

Toy::Toy()
    : m_model( new FlipperModel(2.0, PaintCan(1.0, 1.0, 0.0), PaintCan(1.0, 0.0, 0.0), 1.0, 0.4, 5.0, 2.0, 0.2, 1.6))
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
//    CadModel flipper = FlipperModel(1.0, PaintCan(1.0, 1.0, 0.0), PaintCan(1.0, 0.0, 0.0), 1.0, 0.6, 5.0, 2.0, 0.2, 0.5, 0.0, 0.0);

//    m_model->add(flipper, 0.0, 0.0, 0.0);
    m_model->magnify(0.5);
}

Matrix4x4 Toy::get_animation_matrix(int i) const
{
    Matrix4x4 mm;

    mm.unity();
    if (i == 0) {
        mm.rotate_ay(m_animation_0_angle);
    } else if (i == 1) {
        mm.translate(2.0, 0.0, -2.0);
        mm.rotate_ax(m_animation_1_angle);
    } else if (i == 2) {
        mm.translate(0.0, -1.0, 0.0);
        mm.rotate_ay(m_animation_2_angle);
    } else if (i == 3) {
        mm.translate(0.0, 1.0, 0.0);
        mm.rotate_ay(-m_animation_3_angle);
        mm.rotate_az(m_animation_3_angle * 3.0);
    }
    return mm;
}