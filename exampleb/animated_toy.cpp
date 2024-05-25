//
// animated_toy.cpp
//

#include "animated_toy.h"
#include "cube_shape.h"

AnimatedToy::AnimatedToy()
    : m_uniform(new Uniform(1))
    , m_texture(new Texture(1))
    , m_model(new CadModel(CubeShape(0.1, 0.1, 0.1), PaintCan(1.0, 0.0, 0.0), 0.0))
{
}

AnimatedToy::~AnimatedToy()
{
    delete m_uniform;
    delete m_model;
}

void AnimatedToy::initialize()
{
}

void AnimatedToy::button(int code, bool shifted, bool on)
{
}

void AnimatedToy::advance(int nanoseconds)
{
}

Uniform* AnimatedToy::uniform()
{
    return m_uniform;
}

Texture* AnimatedToy::texture()
{
    return m_texture;
}

CadModel* AnimatedToy::model() const
{
    return m_model;
}
