//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "animated_toy.h"
#include "token_set.h"
#include "cad_model.h"

class Toy: public AnimatedToy
{
public:
    Toy();
    ~Toy();

    void advance(int nanoseconds) override;

private:
    TokenSet* m_token_set;
    char** m_token_names;
    float m_seconds;

    void build_model();
    void build_uniform();
    void update_uniform();
    CadModel token_model(int token_id);
};

#endif // _TOY_H_
