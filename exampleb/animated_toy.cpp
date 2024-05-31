//
// animated_toy.cpp
//

#include "animated_toy.h"
#include "cube_shape.h"

#define MAX_UNIFORMS 50
#define MAX_TEXTURES 50

AnimatedToy::AnimatedToy()
    : m_uniform(new Uniform(MAX_UNIFORMS))
    , m_texture(new Texture(MAX_TEXTURES))
    , m_camera(new Camera())
    , m_model(new CadModel(CubeShape(0.1, 0.1, 0.1), PaintCan(1.0, 0.0, 0.0), 0.0))
{
    m_uniform->add("mvp_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_camera->mvp_data());
    m_uniform->add("rot_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_camera->rot_data());
}

AnimatedToy::~AnimatedToy()
{
    delete m_uniform;
    delete m_texture;
    delete m_camera;
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

