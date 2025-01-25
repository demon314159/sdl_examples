//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"
#include <math.h>
#include "look.h"
#include "pi.h"
#include "gable_brick_element.h"
#include "half_brick_element.h"
#include "brick_element.h"
#include "half_foundation_element.h"
#include "foundation_element.h"
#include "double_foundation_element.h"
#include "triple_foundation_element.h"
#include "roof_element.h"
#include "flat_roof_element.h"
#include "window_element.h"
#include "corner_window_element.h"
#include "front_door_element.h"
#include "back_door_element.h"

#include <stdio.h>

#define HIDE_TIME 0.25
#define THRESHOLD 0.00001

Toy::Toy()
    : m_table(NULL)
    , m_doc(new Document("first.brk"))
    , m_history(new History())
    , m_choose(new Choose(DIMX, DIMY, DIMZ, MARKER_COLOR))
    , m_seconds(0.0)
    , m_left_menu(NULL)
    , m_right_menu(NULL)
{
    m_left_menu = new MaterialMenu();
    m_right_menu = new CommandMenu();
    m_table = new Table(DIMX, DIMY, DIMZ);
    build_texture();
    build_model();
    build_uniform();
    reframe();
    adjust_table_size();
    m_camera->hide_left(-m_left_menu->width(), 0.0, 0.0, 0.0);
    m_camera->hide_right(m_right_menu->width(), 0.0, 0.0, 0.0);
}

Toy::~Toy()
{
    delete m_table;
    delete m_right_menu;
    delete m_left_menu;
    delete m_choose;
    delete m_history;
    delete m_doc;
}

void Toy::reframe()
{
    BoundingBox bb = m_doc->building()->bounding_box();
    // Add the table effect
    bb.vmin.v1 -= (2.0 * DIMX);
    bb.vmin.v3 -= (2.0 * DIMZ);
    bb.vmax.v1 += (2.0 * DIMX);
    bb.vmax.v3 += (2.0 * DIMZ);
    bb.vmin.v2 = (-DIMY / 2.0);
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
    m_left_menu->build_texture(m_texture);
    m_right_menu->build_texture(m_texture);
    m_table->build_texture(m_texture);
}

void Toy::build_model()
{
    m_model->clear();
    m_model->add(m_choose->model(MARKER_ANIMATION_ID));
    m_model->add(m_left_menu->model());
    m_model->add(m_right_menu->model());
    m_model->add(m_table->model(TABLE_ANIMATION_ID));
}

void Toy::build_uniform()
{
    for (int i = 0; i < m_texture->textures(); i++) {
        m_uniform->add(m_texture->uniform_name(i), UNIFORM_TYPE_1_INTEGER_VECTOR, 1, m_texture->data(i));
    }
    m_uniform->add("animation_0_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_choose->data());
    m_left_menu->build_uniform(m_uniform);
    m_right_menu->build_uniform(m_uniform);
    m_table->build_uniform(m_uniform);
}

void Toy::update_uniform()
{
    m_choose->data();
    m_left_menu->update_uniform();
    m_right_menu->update_uniform();
    m_table->update_uniform();
}

void Toy::advance(int nanoseconds)
{
    AnimatedToy::advance(nanoseconds);
    m_seconds += (1.0e-9 * (float) nanoseconds);
    float seconds = 1.0e-3;
    while (m_seconds > seconds) {
        m_seconds -= seconds;
        m_camera->advance_hide(seconds);
    }
    update_uniform();
    m_camera->update_hide_matrix();
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
        case SDL_SCANCODE_S:
            char error_msg[256];
            if (on) {
                if (!m_doc->save("saved.brk", error_msg)) {
                    printf("Toy::button save: %s\n", error_msg);
                }
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
        case SDL_SCANCODE_ESCAPE:
            if (on) {
                m_choose->select_no_choice();
            }

            break;
        default:
            break;
    }
    return ret_val;
}

Int3 Toy::table_coord_selected(const MouseVector& mv, float& depth) const
{
    float level = -DIMY / 2.0;
    Float3 sel_pos = mv.position_at_y(level, depth);
    int ix = round(sel_pos.v1 / DIMX);
    int iz = round(sel_pos.v3 / DIMZ);
    return {ix, -1, iz};
}

bool Toy::top_face_selection(int sx, int sy, Int3& pos, bool& gable_flag, int& gable_orientation) const
{
    gable_flag = false;
    gable_orientation = 0;

    MouseVector mv = m_camera->new_mouse_vector(sx, sy);
    Float3 v = mv.vector();
    float min_depth;
    int min_element = -1;
    Float3 min_ip = {0.0, 0.0, 0.0};
    bool min_top_face = false;
    Int3 sel_pos = table_coord_selected(mv, min_depth);
    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        if (!e->removed()) {
            for (int j = 0; j < e->faces(); j++) {
                float depth;
                bool top_face;
                Float3 ip;
                if (mouse_vector_intersects_face(mv, e->face(j, &top_face), depth, ip)) {
                    if (depth < min_depth) {
                        min_depth = depth;
                        min_element = i;
                        min_ip = ip;
                        min_top_face = top_face;
                    }
                }
            }
        }
    }
    if (min_element < 0) { // No element faces selected
        if (!m_table->contains(sel_pos.v1, sel_pos.v3)) {
            gable_flag = false;
            gable_orientation = 0;
            return false;
        }
    } else {
        if (min_top_face) {
            gable_flag = m_doc->element(min_element)->gable_flag();
            if (gable_flag) {
                gable_orientation = m_doc->element(min_element)->orientation();
                sel_pos = {(int) round(min_ip.v1 / DIMX), (int) round((min_ip.v2) / DIMY), (int) round(min_ip.v3 / DIMZ)};
            } else {
                sel_pos = {(int) round(min_ip.v1 / DIMX), (int) round((min_ip.v2 - DIMY / 2.0) / DIMY), (int) round(min_ip.v3 / DIMZ)};
            }
        } else {
            gable_flag = false;
            gable_orientation = 0;
            return false;
        }
    }
    // Check to see if final candidate has anything above it
    if (m_doc->location_occupied(sel_pos.v1, sel_pos.v2 + 1, sel_pos.v3)) {
        gable_flag = false;
        gable_orientation = 0;
        return false;
    }
    pos = sel_pos;
    return true;
}

bool Toy::try_hide_button(int sx, int sy)
{
    MouseVector mv = m_camera->new_fixed_mouse_vector(sx, sy);
    if (m_left_menu->hide_button_pressed(mv, m_camera->top_left(), m_camera->hidden_left())) {
        if (m_camera->hidden_left()) {
            m_camera->unhide_left(HIDE_TIME);
        } else {
            m_camera->hide_left(-m_left_menu->width(), 0.0, 0.0, HIDE_TIME);
        }
        return true;
    } else if (m_right_menu->hide_button_pressed(mv, m_camera->top_right(), m_camera->hidden_right())) {
        if (m_camera->hidden_right()) {
            m_camera->unhide_right(HIDE_TIME);
        } else {
            m_camera->hide_right(m_right_menu->width(), 0.0, 0.0, HIDE_TIME);
        }
        return true;
    } else {
        return false;
    }
}

bool Toy::try_menu_button(int sx, int sy)
{
    MouseVector mv = m_camera->new_fixed_mouse_vector(sx, sy);
    if (!m_camera->hidden_left()) {
        if (m_left_menu->menu_button_pressed(mv, m_camera->top_left())) {
            return true;
        }
    }
    if (!m_camera->hidden_right()) {
        if (m_right_menu->menu_button_pressed(mv, m_camera->top_right())) {
            return true;
        }
    }
    return false;
}

void Toy::try_top_face(int sx, int sy)
{
    Int3 pos;
    bool gable_flag;
    int gable_orientation;
    if (top_face_selection(sx, sy, pos, gable_flag, gable_orientation)) {
        pos.v2++;
        m_choose->select_choice(pos, gable_flag, gable_orientation);
        Int3 p;
        int w;
        int o;
        if (m_choose->new_element_chosen(p, w, o)) {
            if (w == 1) {
                switch(m_left_menu->material()) {
                    case MATERIAL_FOUNDATION:
                    case MATERIAL_DOUBLE_FOUNDATION:
                    case MATERIAL_TRIPLE_FOUNDATION:
                        m_history->do_command(new AddElementCommand(new HalfFoundationElement(p), m_doc));
                        break;
                    case MATERIAL_ROOF:
                        if (m_choose->valid_roof_selection()) {
                            m_choose->adjust_roof_orientation(p, w, o);
                            m_history->do_command(new AddElementCommand(new RoofElement(p, w, o), m_doc));
                        } else {
                            m_history->do_command(new AddElementCommand(new FlatRoofElement(p, w, o), m_doc));
                        }
                        break;
                    default:
                        m_history->do_command(new AddElementCommand(new HalfBrickElement(p), m_doc));
                }
            } else if (w > 1) {
                Element* item;
                switch(m_left_menu->material()) {
                    case MATERIAL_GABLE_BRICK:
                        item = new GableBrickElement(p, o);
                        break;
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
                    case MATERIAL_ROOF:
                        if (m_choose->valid_roof_selection()) {
                            m_choose->adjust_roof_orientation(p, w, o);
                            item = new RoofElement(p, w, o);
                        } else {
                            item = new FlatRoofElement(p, w, o);
                        }
                        break;
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
                if (m_left_menu->material() == MATERIAL_ROOF) {
                    m_history->do_command(new AddElementCommand(item, m_doc));
                } else {
                    if (!m_doc->element_occupied(item)) {
                        m_history->do_command(new AddElementCommand(item, m_doc));
                    } else {
                        delete item;
                    }
                }
            }
            m_choose->select_no_choice();
        }
    } else {
        m_choose->select_no_choice();
    }
}

void Toy::try_delete_any_face(int sx, int sy)
{
    MouseVector mv = m_camera->new_mouse_vector(sx, sy);
    Float3 v = mv.vector();
    float min_depth = 1000.0;
    int min_element = -1;
    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        if (!e->removed()) {
            for (int j = 0; j < e->faces(); j++) {
                float depth;
                bool top_face;
                Float3 ip;
                if (mouse_vector_intersects_face(mv, e->face(j, &top_face), depth, ip)) {
                    if (depth < min_depth) {
                        min_depth = depth;
                        min_element = i;
                    }
                }
            }
        }
    }
    if (min_element >= 0) {
        m_history->do_command(new RemoveElementCommand(min_element, m_doc));
    }
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
            m_left_menu->release();
            m_right_menu->release();
        }
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
        if (on) {
            try_delete_any_face(e->button.x, e->button.y);
        } else {
        }
    }
    return false;
}

bool Toy::mouse_vector_intersects_face(const MouseVector& mv, const Face& f, float& depth, Float3& ip) const
{
    Float3 vec = mv.vector();
    Float3 org = mv.origin();
    Float3 plane = normal(f);

    double denom = plane.v1 * vec.v1 + plane.v2 * vec.v2 + plane.v3 * vec.v3;
    if (fabs(denom) < THRESHOLD) {
        return false;
    }
    double num_a = plane.v1 * f.v1.v1 + plane.v2 * f.v1.v2 + plane.v3 * f.v1.v3;
    double num_b = plane.v1 * org.v1 + plane.v2 * org.v2 + plane.v3 * org.v3;

    double t = (num_a - num_b) / denom;
    ip.v1 = org.v1 + t * vec.v1;
    ip.v2 = org.v2 + t * vec.v2;
    ip.v3 = org.v3 + t * vec.v3;

    if (in_face(ip, f)) {
        depth = (float) t;
        return true;
    }
    return false;
}

Float3 Toy::normal(const Face& f) const
{
    Float3 p1, p2, p3;
    p1 = f.v1;
    p2 = f.v2;
    p3 = f.v3;
    Float3 va, vb;
    va.v1 = p2.v1 - p1.v1;
    va.v2 = p2.v2 - p1.v2;
    va.v3 = p2.v3 - p1.v3;
    vb.v1 = p3.v1 - p1.v1;
    vb.v2 = p3.v2 - p1.v2;
    vb.v3 = p3.v3 - p1.v3;
    Float3 xp;
    xp.v1 = va.v2 * vb.v3 - vb.v2 * va.v3;
    xp.v2 = vb.v1 * va.v3 - va.v1 * vb.v3;
    xp.v3 = va.v1 * vb.v2 - vb.v1 * va.v2;
    return xp;
}

bool Toy::in_face(const Float3& p, const Face& f) const
{
    double area1 = quad_area(f.v1, f.v2, f.v3, f.v4);
    double area2 = tri_area(f.v1, f.v2, p) + tri_area(f.v2, f.v3, p) + tri_area(f.v3, f.v4, p) + tri_area(f.v4, f.v1, p);
    return area2 <= (1.01 * area1);
}

double Toy::length(const Float3& v1, const Float3& v2) const
{
    double a = v1.v1 - v2.v1;
    double b = v1.v2 - v2.v2;
    double c = v1.v3 - v2.v3;
    return sqrt(a * a + b * b + c * c);
}

double Toy::tri_area(const Float3& v1, const Float3& v2, const Float3& v3) const
{
    double a = length(v1, v2);
    double b = length(v2, v3);
    double c = length(v3, v1);
    double s = (a + b + c) / 2.0;
    return sqrt(fabs(s * (s - a) * (s - b) * (s - c)));
}

double Toy::quad_area(const Float3& v1, const Float3& v2, const Float3& v3, const Float3& v4) const
{
    double a = length(v1, v2);
    double b = length(v2, v3);
    double c = length(v3, v4);
    double d = length(v4, v1);
    double p = length(v1, v3);
    double q = length(v2, v4);
    double k = b * b + d * d - a * a - c * c;
    return sqrt(fabs(4.0 * p * p * q * q - k * k)) / 4.0;
}


