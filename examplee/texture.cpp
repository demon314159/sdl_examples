//
// texture.cpp
//

#include "texture.h"

Texture::Texture(int max_textures)
    : m_max_textures(max_textures)
    , m_textures(0)
    , m_texture(new TextureRec[max_textures])
{

}

Texture::~Texture()
{
    delete [] m_texture;
}

int Texture::textures() const
{
    return m_textures;
}

const char* Texture::file_name(int ix) const
{
    return m_texture[ix].file_name;
}

const char* Texture::uniform_name(int ix) const
{
    return m_texture[ix].uniform_name;
}

void* Texture::data(int ix) const
{
    return &m_texture[ix].data;
}

void Texture::add(const char* file_name, const char* uniform_name)
{
   if (m_textures < m_max_textures) {
       m_texture[m_textures] = {file_name, uniform_name, m_textures};
       ++m_textures;
   }
}

