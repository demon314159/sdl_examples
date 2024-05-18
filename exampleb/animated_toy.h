//
// animated_toy.h
//

#ifndef _ANIMATED_TOY_H_
#define _ANIMATED_TOY_H_

#include "uniform.h"
#include <SDL_scancode.h>

class AnimatedToy
{
public:
    AnimatedToy();
    virtual ~AnimatedToy();

    virtual Uniform* uniform() const;
    virtual void button(int code, bool shifted, bool on);
    virtual void advance(int nanoseconds);

private:
    Uniform* m_uniform;
};

#endif // _ANIMATED_TOY_H_
