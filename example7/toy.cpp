//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"

Toy::Toy()
    : m_model_changed(false)
    , m_model(new CadModel())
{
    build_model();
}

Toy::~Toy()
{
    delete m_model;
}

bool Toy::model_changed() const
{
    return m_model_changed;
}

void Toy::clear_model_changed()
{
    m_model_changed = false;
}

CadModel* Toy::get_model() const
{
    return m_model;
}

int Toy::get_matrix_uniforms() const
{
    return 3;
}

void Toy::advance(int nanoseconds)
{
}

void Toy::build_model()
{
    float ANI_ID_NONE = 0.0;
    float ANI_ID_TOY0 = 2.0;
    float ANI_ID_TOY1 = 3.0;
    float ANI_ID_TOY2 = 4.0;
    CadModel rcm = CadModel(CubeShape(1.0, 1.0, 1.0), PaintCan(1.0, 0.0, 0.0), ANI_ID_TOY0);
    CadModel gcm = CadModel(CubeShape(1.0, 1.0, 1.0), PaintCan(0.0, 1.0, 0.0), ANI_ID_TOY1);
    CadModel bcm = CadModel(CubeShape(1.0, 1.0, 1.0), PaintCan(0.0, 0.0, 1.0), ANI_ID_TOY2);
    m_model->add(rcm, -2.0, 0.0, 0.0);
    m_model->add(gcm, 2.0, 0.0, 0.0);
    m_model->add(bcm, 0.0, 0.0, -2.0);
}

