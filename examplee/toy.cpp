//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"
#include <math.h>
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

Int3 Toy::coord_at_level(int iy, const MouseVector& mv) const
{
        float level = DIMY / 2.0 + DIMY * (float) iy;
        Float2 sel_pos = mv.position_at_y(level);
        int ix = round(sel_pos.v1 / DIMX);
        int iz = round(sel_pos.v2 / DIMZ);
        return {ix, iy, iz};
}

bool Toy::top_face_selection(int sx, int sy, Int3& pos) const
{
    MouseVector mv = m_camera->new_mouse_vector(sx, sy);
    Int3 sel_pos = coord_at_level(-1, mv);
    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        int y = e->pos().v2 + e->height() - 1;
        if (y > sel_pos.v2) {
            Int3 new_pos = coord_at_level(y, mv);
            if (e->contains(new_pos.v1, new_pos.v2, new_pos.v3)) {
                sel_pos = new_pos;
            }
        }
    }
    // Check to see if final candidate has anything above it
    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        if (e->contains(sel_pos.v1, sel_pos.v2 + 1, sel_pos.v3)) {
            return false;
        }
    }
    pos = sel_pos;
    return true;
}

bool Toy::mouse(SDL_Event* e, bool on)
{
    bool ret_val = AnimatedToy::mouse(e, on);
    if (!ret_val)
        return false;
    if (e->button.button == SDL_BUTTON_MIDDLE) {
        if (on) {
        } else {
        }
    } else if (e->button.button == SDL_BUTTON_LEFT) {
        if (on) {
            Int3 pos;
            if (top_face_selection(e->button.x, e->button.y, pos)) {
                printf("Selected %d, %d, %d\n", pos.v1, pos.v2, pos.v3);
            }
        } else {

        }
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
        if (on) {
        } else {
        }
    }
    return false;
}

