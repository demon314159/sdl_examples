//
// animated_toy.h
//

#ifndef _ANIMATED_TOY_H_
#define _ANIMATED_TOY_H_

#include "uniform.h"
#include "cad_model.h"
#include <SDL_scancode.h>

class AnimatedToy
{
public:
    AnimatedToy();
    virtual ~AnimatedToy();

    virtual void initialize();
    virtual void button(int code, bool shifted, bool on);
    virtual void advance(int nanoseconds);
    virtual Uniform* uniform();
    virtual CadModel* model() const;


//    how about cad model
//    and initialize


protected:
    Uniform* m_uniform;
    CadModel* m_model;
};

#endif // _ANIMATED_TOY_H_
