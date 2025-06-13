//
// uniform.h
//

#ifndef _UNIFORM_H_
#define _UNIFORM_H_

#define UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR 0
#define UNIFORM_TYPE_3_FLOAT_VECTOR       1
#define UNIFORM_TYPE_1_FLOAT_VECTOR       2
#define UNIFORM_TYPE_1_INTEGER_VECTOR     3

struct UniformRec {
    const char* name;
    int uniform_type;
    int handle;
    int items;
    const void* data;
};


class Uniform
{
public:
    Uniform(int max_uniforms);
    ~Uniform();

    int uniforms() const;
    const char* name(int ix) const;
    void set_handle(int ix, int handle);
    int uniform_type(int ix) const;
    int handle(int ix) const;
    int items(int ix) const;
    const void* data(int ix) const;

    void add(const char* name, int uniform_type, int items, const void* data);

private:
    int m_max_uniforms;
    int m_uniforms;
    UniformRec* m_uniform;
};

#endif // _UNIFORM_H_

