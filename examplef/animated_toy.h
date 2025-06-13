//
// animated_toy.h
//

#ifndef _ANIMATED_TOY_H_
#define _ANIMATED_TOY_H_

#include "options.h"
#include "uniform.h"
#include "texture.h"
#include "camera.h"
#include "cad_model.h"
#include <SDL_scancode.h>
#include <SDL_events.h>

class AnimatedToy
{
public:
    AnimatedToy(Options* options);
    virtual ~AnimatedToy();

    virtual void resize(int w, int h);
    virtual void initialize();
    virtual bool button(int code, bool shifted, bool on);
    virtual bool mouse(SDL_Event* e, bool on);
    virtual void advance(int nanoseconds);

    Options* m_options;
    Uniform* uniform();
    Texture* texture();
    Camera* camera();
    CadModel* model() const;

protected:
    Uniform* m_uniform;
    Texture* m_texture;
    Camera* m_camera;
    CadModel* m_model;
};

#endif // _ANIMATED_TOY_H_
