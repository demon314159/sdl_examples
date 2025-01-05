//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "animated_toy.h"
#include "document.h"

class Toy: public AnimatedToy
{
public:
    Toy();
    ~Toy();

    Document* get_doc() const;

private:
    Document* m_doc;
    void build_model();
};

#endif // _TOY_H_
