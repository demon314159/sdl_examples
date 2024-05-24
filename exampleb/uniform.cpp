//
// uniform.cpp
//

#include "uniform.h"

Uniform::Uniform(int max_uniforms)
    : m_max_uniforms(max_uniforms)
    , m_uniforms(0)
    , m_uniform(new UniformRec[max_uniforms])

{
}

Uniform::~Uniform()
{
    delete [] m_uniform;
}

int Uniform::uniforms() const
{
    return m_uniforms;
}

const char* Uniform::name(int ix) const
{
    return m_uniform[ix].name;
}

void Uniform::set_handle(int ix, int handle)
{
    m_uniform[ix].handle = handle;
}


int Uniform::uniform_type(int ix) const
{
    return m_uniform[ix].uniform_type;
}

int Uniform::handle(int ix) const
{
    return m_uniform[ix].handle;
}

int Uniform::items(int ix) const
{
    return m_uniform[ix].items;
}

void* Uniform::data(int ix) const
{
    return m_uniform[ix].data;
}

void Uniform::add(const char* name, int uniform_type, int items, void* data)
{
    if (m_uniforms < m_max_uniforms) {
        m_uniform[m_uniforms] = {name, uniform_type, -1, items, data};
        m_uniforms++;
    }
}
