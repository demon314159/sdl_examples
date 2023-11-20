//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "cad_model.h"

class Toy
{
public:
    Toy();
    ~Toy();

    CadModel* get_static_model() const;
    void advance_animation(int nanoseconds);


private:
    CadModel* m_static_model;

    void build_static_model();
};

#endif // _TOY_H_
