//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"

#include <stdio.h>

Toy::Toy()
    : m_doc(new Document("first.brk"))
{
    build_model();
    BoundingBox bb = m_model->bounding_box();
    m_doc->building()->update_bounding_box(bb);
    m_camera->frame(bb);
}

Toy::~Toy()
{
    delete m_doc;
}

Document* Toy::get_doc() const
{
    return m_doc;
}

Camera* Toy::get_camera() const
{
    return m_camera;
}

void Toy::build_model()
{
    m_model->clear();
    CadModel csx(CubeShape(0.2, 0.002, 0.002), PaintCan(0.0, 1.0, 1.0), 0.0);
    CadModel csy(CubeShape(0.002, 0.2, 0.002), PaintCan(0.0, 0.0, 1.0), 0.0);
    CadModel csz(CubeShape(0.002, 0.002, 0.2), PaintCan(0.0, 1.0, 0.0), 0.0);
    m_model->add(csx, 0.0, 0.0, 0.0);
    m_model->add(csy, 0.0, 0.0, 0.0);
    m_model->add(csz, 0.0, 0.0, 0.0);
}

bool Toy::button(int code, bool shifted, bool on)
{
    bool ret_val = AnimatedToy::button(code, shifted, on);
    if (!ret_val)
        return false;
    switch (code) {
        case SDL_SCANCODE_C:
            if (on) {
                m_doc->add_element(new Element({0, 2, 0}, 1, 1, 0));
            }
            break;
        default:
            break;
    }
    return ret_val;
}
