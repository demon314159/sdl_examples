//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"
#include <math.h>
#include "look.h"
#include <stdio.h>

#define MENU_DIMX  0.25f
#define MENU_DIMY  0.50f
#define MENU_DIMZ  0.005f

Toy::Toy()
    : m_doc(new Document("first.brk"))
    , m_history(new History())
    , m_choose(new Choose(DIMX, DIMY, DIMZ, MARKER_COLOR))
    , m_seconds(0.0)
    , m_menu(NULL)
{
    m_menu = new MaterialMenu(MENU_DIMX, MENU_DIMY, MENU_DIMZ, {0.0, 0.0, 0.0});
    build_texture();
    build_model();
    build_uniform();
    BoundingBox bb = m_model->bounding_box();
    m_doc->building()->update_bounding_box(bb);
    m_camera->frame(bb);
}

Toy::~Toy()
{
    delete m_menu;
    delete m_choose;
    delete m_history;
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

void Toy::build_texture()
{
    m_menu->build_texture(m_texture);
}

void Toy::build_model()
{
    m_model->clear();
//    CadModel csx(CubeShape(0.2, 0.002, 0.002), PaintCan(0.0, 1.0, 1.0), 0.0);
//    CadModel csy(CubeShape(0.002, 0.2, 0.002), PaintCan(0.0, 0.0, 1.0), 0.0);
///    CadModel csz(CubeShape(0.002, 0.002, 0.2), PaintCan(0.0, 1.0, 0.0), 0.0);
//    m_model->add(csx, 0.0, 0.0, 0.0);
//    m_model->add(csy, 0.0, 0.0, 0.0);
//    m_model->add(csz, 0.0, 0.0, 0.0);
    m_model->add(m_choose->model(MARKER_ANIMATION_ID));
    m_model->add(m_menu->model());
}

void Toy::build_uniform()
{
    for (int i = 0; i < m_texture->textures(); i++) {
        m_uniform->add(m_texture->uniform_name(i), UNIFORM_TYPE_1_INTEGER_VECTOR, 1, m_texture->data(i));
    }
    m_uniform->add("animation_0_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_choose->data());
    m_menu->build_uniform(m_uniform);
}

void Toy::update_uniform()
{
    m_choose->data();
    m_menu->update_uniform();
}

void Toy::advance(int nanoseconds)
{
    AnimatedToy::advance(nanoseconds);
    m_seconds += (1.0e-9 * (float) nanoseconds);
    float seconds = 1.0e-3;
    while (m_seconds > seconds) {
        m_seconds -= seconds;

    }
    update_uniform();
}

bool Toy::button(int code, bool shifted, bool on)
{
    bool ret_val = AnimatedToy::button(code, shifted, on);
    if (!ret_val)
        return false;
    switch (code) {
        case SDL_SCANCODE_C:
            if (on) {
            }
            break;
        case SDL_SCANCODE_U:
            if (on) {
                m_history->undo_command();
            }
            break;
        case SDL_SCANCODE_R:
            if (on) {
                m_history->redo_command();
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
    if (m_doc->occupied(sel_pos.v1, sel_pos.v2 + 1, sel_pos.v3)) {
        return false;
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
                pos.v2++;
                m_choose->select_choice(pos);
                Int3 p;
                int w;
                int o;
                if (m_choose->new_element_chosen(p, w, o)) {
                    if (w == 1) {
                        m_history->do_command(new AddElementCommand(new HalfBrickElement(p), m_doc));
                    } else if (w > 1) {
                        w = 2;
                        Element* item;
                        item = new BrickElement(p, o);
//                        item = new DoubleBrickElement(p, o);
//                        item = new TripleBrickElement(p, o);
//                        item = new GableBrickElement(p, o);
//                        item = new WindowElement(p, o);
//                        item = new DoorElement(p, o);
                        if (!m_doc->occupied(item)) {
                            m_history->do_command(new AddElementCommand(item, m_doc));
                        } else {
                            delete item;
                        }
                    }
                    m_choose->select_no_choice();
                }
            } else {
                m_choose->select_no_choice();
            }
        } else {
        }
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
        if (on) {
            m_menu->press();
        } else {
            m_menu->release();
        }
    }
    return false;
}

