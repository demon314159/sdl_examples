//
// animated_toy.h
//

#ifndef _ANIMATED_TOY_H_
#define _ANIMATED_TOY_H_

#include "uniform.h"


class AnimatedToy
{
public:
    AnimatedToy();
    virtual ~AnimatedToy();

    virtual Uniform* uniform() const;

private:
    Uniform* m_uniform;
};

#endif // _ANIMATED_TOY_H_
