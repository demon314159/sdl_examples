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

    CadModel* get_model() const;


private:
    CadModel* m_model;

    void build_model();
};

#endif // _TOY_H_
