//
// animated_toy.cpp
//

#include "animated_toy.h"

AnimatedToy::AnimatedToy()
: m_uniform(new Uniform)
{
}

AnimatedToy::~AnimatedToy()
{
    delete m_uniform;
}

Uniform* AnimatedToy::uniform() const
{
    return m_uniform;
}


