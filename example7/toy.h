//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "cad_model.h"
#include "matrix4x4.h"

class Toy
{
public:
    Toy();
    ~Toy();

    bool model_changed() const;
    void clear_model_changed();
    CadModel* get_model() const;
    int get_matrix_uniforms() const;
    Matrix4x4 get_matrix(int i) const;

    void advance(int nanoseconds);

private:
    bool m_model_changed;
    CadModel* m_model;

    void build_model();
};

#endif // _TOY_H_
