//
// toy.cpp
//

#include "toy.h"
#include "pi.h"
#include <math.h>
#include "look.h"
#include "plane_shape.h"
#include "open_box_shape.h"
#include "cube_shape.h"

#define ANIMATION_0_SPEED 0.0
#define ANIMATION_1_SPEED 0.0
#define ANIMATION_2_SPEED 15.0
#define ANIMATION_3_SPEED 30.0

#define ANIMATION_ID_0 2.0
#define ANIMATION_ID_1 3.0
#define ANIMATION_ID_2 4.0
#define ANIMATION_ID_3 5.0

Toy::Toy()
    : m_lamp28(LAMP28_ID, LAMP28_POSITION, LAMP_SIZE, LAMP28_ON_COLOR, LAMP28_OFF_COLOR)
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
    float seconds = 1.0e-9 * (float) nanoseconds;
    m_animation_0_angle += (ANIMATION_0_SPEED * seconds);
    m_animation_1_angle += (ANIMATION_1_SPEED * seconds);
    m_animation_2_angle += (ANIMATION_2_SPEED * seconds);
    m_animation_3_angle += (ANIMATION_3_SPEED * seconds);
}

void Toy::build_model()
{

    float k = 1.0;

    CadModel cube(CubeShape(8.0, 8.0, 8.0), PaintCan(1.0, 0.0, 0.0), 0.0);
    CadModel top_playfield(PlaneShape(PLAYFIELD_X, PLAYFIELD_Z, 1.0), PaintCan(0.0, 1.0, 0.0), 99.0);
    CadModel board(OpenBoxShape(PLAYFIELD_X, PLAYFIELD_Y, PLAYFIELD_Z), PaintCan(0.0, 1.0, 0.0), 0.0);

    m_model->add(cube, 0.0, 0.0, 0.0);
    m_model->add(m_lamp28.model(), 0.0, 0.0, 0.0);
    m_model->add(top_playfield, PLAYFIELD_X / 2.0, 0.0, PLAYFIELD_Z / 2.0);
    m_model->add(board, PLAYFIELD_X / 2.0, -PLAYFIELD_Y / 2.0, PLAYFIELD_Z / 2.0);
}

Matrix4x4 Toy::get_animation_matrix(int i) const
{
    Matrix4x4 mm;

    mm.unity();
    if (i == 0) {
    } else if (i == 1) {
    } else if (i == 2) {
    } else if (i == 3) {
        mm.rotate_ay(-m_animation_3_angle);
    }
    return mm;
}

void Toy::left_action_button(bool on)
{
}

void Toy::right_action_button(bool on)
{
}

