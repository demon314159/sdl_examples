//
// uniform.h
//

#ifndef _UNIFORM_H_
#define _UNIFORM_H_

#define UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR 0
#define UNIFORM_TYPE_3_FLOAT_VECTOR       1
#define UNIFORM_TYPE_1_FLOAT_VECTOR       2
#define UNIFORM_TYPE_1_INTEGER_VECTOR     3

class Uniform
{
public:
    Uniform();
    ~Uniform();

    int uniforms() const;
    const char* name(int ix) const;
    void set_handle(int ix, int handle);
    int uniform_type(int ix) const;
    int handle(int ix) const;
    int items(int ix) const;
    void* data(int ix) const;

private:
};

#endif // _UNIFORM_H_

