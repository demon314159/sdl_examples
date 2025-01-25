//
// animated_toy.cpp
//

#include "animated_toy.h"
#include "cube_shape.h"

#define MAX_UNIFORMS 100
#define MAX_TEXTURES 100

#define INITIAL_HEIGHT 512
#define INITIAL_WIDTH ((INITIAL_HEIGHT * 1920) / 1080)
#define INITIAL_MAG  0.9
#define INITIAL_XOFF  0.0
#define INITIAL_YOFF  0.0
#define INITIAL_XROT 30.0
#define INITIAL_YROT 0.0

AnimatedToy::AnimatedToy()
    : m_uniform(new Uniform(MAX_UNIFORMS))
    , m_texture(new Texture(MAX_TEXTURES))
    , m_camera(new Camera(INITIAL_WIDTH, INITIAL_HEIGHT, INITIAL_MAG, {INITIAL_XOFF, INITIAL_YOFF}, {INITIAL_XROT, INITIAL_YROT}))
    , m_model(new CadModel(CubeShape(0.1, 0.1, 0.1), PaintCan(1.0, 0.0, 0.0), 0.0))
{
    m_uniform->add("fixed_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_camera->fixed_data());
    m_uniform->add("hide_left_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_camera->hide_left_data());
    m_uniform->add("mvp_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_camera->mvp_data());
    m_uniform->add("rot_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_camera->rot_data());
    m_camera->frame(m_model);
}

AnimatedToy::~AnimatedToy()
{
    delete m_uniform;
    delete m_texture;
    delete m_camera;
    delete m_model;
}

void AnimatedToy::resize(int w, int h)
{
    m_camera->resize(w, h);
}

void AnimatedToy::initialize()
{
}

bool AnimatedToy::button(int code, bool shifted, bool on)
{
  return true;
}

void AnimatedToy::advance(int nanoseconds)
{
}

bool AnimatedToy::quit_signal() const
{
    return false;
}

Uniform* AnimatedToy::uniform()
{
    return m_uniform;
}

Texture* AnimatedToy::texture()
{
    return m_texture;
}

Camera* AnimatedToy::camera()
{
    return m_camera;
}

CadModel* AnimatedToy::model() const
{
    return m_model;
}

bool AnimatedToy::mouse(SDL_Event* e, bool on)
{
    return true;
}

bool AnimatedToy::mouse_wheel(SDL_Event* e)
{
    return true;
}

bool AnimatedToy::mouse_move(SDL_Event* e)
{
    return true;
}



