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
    bool mouse(SDL_Event* e, bool on) override;
    Document* get_doc() const;
    Camera* get_camera() const;

private:
    Document* m_doc;
    void build_model();
    bool top_face_selection(int sx, int sy, Int3& pos) const;
    Int3 coord_at_level(int iy, const MouseVector& mv) const;
};

#endif // _TOY_H_
