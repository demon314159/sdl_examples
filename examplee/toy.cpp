//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"
#include <math.h>
#include "look.h"
#include <stdio.h>

#define HIDE_TIME 0.25

Toy::Toy()
    : m_table(NULL)
    , m_doc(new Document("first.brk"))
    , m_history(new History())
    , m_choose(new Choose(DIMX, DIMY, DIMZ, MARKER_COLOR))
    , m_seconds(0.0)
    , m_menu(NULL)
{
    m_menu = new MaterialMenu();
    m_table = new Table(DIMX, DIMY, DIMZ);
    build_texture();
    build_model();
    build_uniform();
    reframe();
    adjust_table_size();
    m_camera->hide(-m_menu->width(), 0.0, 0.0, 0.0);
}

Toy::~Toy()
{
    delete m_table;
    delete m_menu;
    delete m_choose;
    delete m_history;
    delete m_doc;
}

void Toy::reframe()
{
    BoundingBox bb = m_doc->building()->bounding_box();
    bb.vmin.v1 -= (2.0 * DIMX);
    bb.vmin.v3 -= (2.0 * DIMZ);
    bb.vmax.v1 += (2.0 * DIMX);
    bb.vmax.v3 += (2.0 * DIMZ);
    m_camera->frame(bb);
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
    m_table->build_texture(m_texture);
}

void Toy::build_model()
{
    m_model->clear();
    m_model->add(m_choose->model(MARKER_ANIMATION_ID));
    m_model->add(m_menu->model());
    m_model->add(m_table->model(TABLE_ANIMATION_ID));
}

void Toy::build_uniform()
{
    for (int i = 0; i < m_texture->textures(); i++) {
        m_uniform->add(m_texture->uniform_name(i), UNIFORM_TYPE_1_INTEGER_VECTOR, 1, m_texture->data(i));
    }
    m_uniform->add("animation_0_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_choose->data());
    m_menu->build_uniform(m_uniform);
    m_table->build_uniform(m_uniform);
}

void Toy::update_uniform()
{
    m_choose->data();
    m_menu->update_uniform();
    m_table->update_uniform();
}

void Toy::advance(int nanoseconds)
{
    AnimatedToy::advance(nanoseconds);
    m_seconds += (1.0e-9 * (float) nanoseconds);
    float seconds = 1.0e-3;
    while (m_seconds > seconds) {
        m_seconds -= seconds;
        m_camera->advance_hide_fixed(seconds);
    }
    update_uniform();
    m_camera->update_hide_fixed_matrix();
    if (m_doc->just_one_change() || m_doc->many_changes()) {
        adjust_table_size();
    }
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
    if (sel_pos.v2 == -1) { // No top faces selected
        if (!m_table->contains(sel_pos.v1, sel_pos.v3)) {
            return false;
        }
    }
    // Check to see if final candidate has anything above it
    if (m_doc->location_occupied(sel_pos.v1, sel_pos.v2 + 1, sel_pos.v3)) {
        return false;
    }
    pos = sel_pos;
    return true;
}

bool Toy::try_hide_button(int sx, int sy)
{
    MouseVector mv = m_camera->new_fixed_mouse_vector(sx, sy);
    if (m_menu->hide_button_pressed(mv, m_camera->top_left())) {
        if (m_camera->hidden()) {
            m_camera->unhide(HIDE_TIME);
        } else {
            m_camera->hide(-m_menu->width(), 0.0, 0.0, HIDE_TIME);
        }
        return true;
    } else {
        return false;
    }
}

bool Toy::try_menu_button(int sx, int sy)
{
    MouseVector mv = m_camera->new_fixed_mouse_vector(sx, sy);
    if (m_camera->hidden()) {
        return false;
    }
    return m_menu->menu_button_pressed(mv, m_camera->top_left());
}

void Toy::try_top_face(int sx, int sy)
{
    Int3 pos;
    if (top_face_selection(sx, sy, pos)) {
        pos.v2++;
        m_choose->select_choice(pos);
        Int3 p;
        int w;
        int o;
        if (m_choose->new_element_chosen(p, w, o)) {
            if (w == 1) {
                switch(m_menu->material()) {
                    case MATERIAL_FOUNDATION:
                    case MATERIAL_DOUBLE_FOUNDATION:
                    case MATERIAL_TRIPLE_FOUNDATION:
                        m_history->do_command(new AddElementCommand(new HalfFoundationElement(p), m_doc));
                        break;
                    default:
                        m_history->do_command(new AddElementCommand(new HalfBrickElement(p), m_doc));
                }
            } else if (w > 1) {
                w = 2;
                Element* item;
                switch(m_menu->material()) {
                    case MATERIAL_BRICK:
                        item = new BrickElement(p, o);
                        break;
                    case MATERIAL_FOUNDATION:
                        item = new FoundationElement(p, o);
                        break;
                    case MATERIAL_DOUBLE_FOUNDATION:
                        item = new DoubleFoundationElement(p, o);
                        break;
                    case MATERIAL_TRIPLE_FOUNDATION:
                        item = new TripleFoundationElement(p, o);
                        break;
                    case MATERIAL_GABLE_BRICK:
                        item = new GableBrickElement(p, o);
                        break;
//                  case MATERIAL_ROOF:
//                        item = new BrickElement(p, o);
//                        break;
                    case MATERIAL_WINDOW:
                        item = new WindowElement(p, o);
                        break;
                    case MATERIAL_CORNER_WINDOW:
                        item = new CornerWindowElement(p, o);
                        break;
                    case MATERIAL_FRONT_DOOR:
                        item = new FrontDoorElement(p, o);
                        break;
                    case MATERIAL_BACK_DOOR:
                        item = new BackDoorElement(p, o);
                        break;
                    default:
                        item = new BrickElement(p, o);
                        break;
                }
                if (!m_doc->element_occupied(item)) {
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
            if (!try_hide_button(e->button.x, e->button.y)) {
                if (!try_menu_button(e->button.x, e->button.y)) {
                    try_top_face(e->button.x, e->button.y);
                }
            }
        } else {
            m_menu->release();
        }
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
        if (on) {
        } else {
        }
    }
    return false;
}

void Toy::adjust_table_size()
{
    IntegerBoundingBox bb = m_doc->integer_bounding_box();
    bb.vmin.v1 -= 2;
    bb.vmin.v3 -= 2;
    bb.vmax.v1 += 2;
    bb.vmax.v3 += 2;
    m_table->change_size({bb.vmin.v1, bb.vmax.v3}, {bb.vmax.v1 - bb.vmin.v1 + 1, bb.vmax.v3 - bb.vmin.v3 + 1});
}

