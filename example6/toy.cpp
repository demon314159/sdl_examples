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

void Toy::build_model()
{
}


