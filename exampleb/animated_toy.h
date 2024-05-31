//
// animated_toy.h
//

#ifndef _ANIMATED_TOY_H_
#define _ANIMATED_TOY_H_

#include "uniform.h"
#include "texture.h"
#include "camera.h"
#include "cad_model.h"
#include <SDL_scancode.h>

#define INITIAL_XROT 50.0
#define INITIAL_YROT 10.0
#define INITIAL_XOFF  0.055
#define INITIAL_YOFF  0.065

class AnimatedToy
{
public:
    AnimatedToy();
    virtual ~AnimatedToy();

    virtual void initialize();
    virtual void button(int code, bool shifted, bool on);
    virtual void advance(int nanoseconds);
    virtual CadModel* model() const;

    Uniform* uniform();
    Texture* texture();
    Camera* camera();

protected:
    Uniform* m_uniform;
    Texture* m_texture;
    Camera* m_camera;
    CadModel* m_model;
};

#endif // _ANIMATED_TOY_H_
