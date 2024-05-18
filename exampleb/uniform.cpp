//
// uniform.cpp
//

#include "uniform.h"

Uniform::Uniform()
{
}

Uniform::~Uniform()
{
}

int Uniform::uniforms() const
{
    return 0;
}

const char* Uniform::name(int ix) const
{
    return "none";
}

void Uniform::set_handle(int ix, int handle)
{
}

int Uniform::uniform_type(int ix) const
{
    return 0;
}

int Uniform::handle(int ix) const
{
    return -1;
}

int Uniform::items(int ix) const
{
    return 0;
}

void* Uniform::data(int ix) const
{
    return (void*) 0;
}

