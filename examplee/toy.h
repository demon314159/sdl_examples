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

    bool button(int code, bool shifted, bool on) override;
    Document* get_doc() const;
    Camera* get_camera() const;

private:
    Document* m_doc;
    void build_model();
};

#endif // _TOY_H_
