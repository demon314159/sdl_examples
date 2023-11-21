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

    bool model_changed() const;
    void clear_model_changed();
    CadModel* get_model() const;

    void advance(int nanoseconds);

private:
    bool m_model_changed;
    CadModel* m_model;

    void build_model();
};

#endif // _TOY_H_
