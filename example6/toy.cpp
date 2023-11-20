//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"

Toy::Toy()
    : m_static_model(new CadModel())
{
    build_static_model();
}

Toy::~Toy()
{
    delete m_static_model;
}

CadModel* Toy::get_static_model() const
{
    return m_static_model;
}

void Toy::advance_animation(int nanoseconds)
{
}

void Toy::build_static_model()
{
    float ANI_ID_NONE = 0.0;
    CadModel rcm = CadModel(CubeShape(1.0, 1.0, 1.0), PaintCan(1.0, 0.0, 0.0), ANI_ID_NONE);
    CadModel gcm = CadModel(CubeShape(1.0, 1.0, 1.0), PaintCan(0.0, 1.0, 0.0), ANI_ID_NONE);
    CadModel bcm = CadModel(CubeShape(1.0, 1.0, 1.0), PaintCan(0.0, 0.0, 1.0), ANI_ID_NONE);
    m_static_model->add(rcm, -1.0, 0.0, 0.0);
    m_static_model->add(gcm, 1.0, 0.0, 0.0);
    m_static_model->add(bcm, 1.0, 0.0, -1.0);
}

