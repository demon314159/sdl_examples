//
// texture.h
//

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

struct TextureRec {
  const char* file_name;
  const char* uniform_name;
  int data;
};

class Texture
{
public:
    Texture(int max_textures);
    ~Texture();

    int textures() const;
    const char* file_name(int ix) const;
    const char* uniform_name(int ix) const;
    void* data(int ix) const;

    void add(const char* file_name, const char* uniform_name);

private:
    int m_max_textures;
    int m_textures;
    TextureRec* m_texture;
};

#endif // _TEXTURE_H_
