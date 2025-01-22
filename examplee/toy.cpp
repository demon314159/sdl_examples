//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"
#include <math.h>
#include "look.h"
#include "pi.h"

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

Int3 Toy::top_face_coord_at_level(int iy, const MouseVector& mv) const
{
    float depth;
    float level = DIMY / 2.0 + DIMY * (float) iy;
    Float2 sel_pos = mv.position_at_y(level, depth);
    int ix = round(sel_pos.v1 / DIMX);
    int iz = round(sel_pos.v2 / DIMZ);
    return {ix, iy, iz};
}

//
// Translate the frame so the brick is at 0.0
// Rotate the frame of reference by 33.69 degrees so the gable face on the XZ plane at y = 0
// Find the position on the XZ plane
// UnRotate the position by -33.69 degrees
// UnTranslate the position
// Convert position to integer
//
Int3 Toy::gable_face_coord(Int3 pos, int orientation, const MouseVector& mv) const
{
    float cx = DIMX * (float) pos.v1;
    float cy = DIMY * (float) pos.v2;
    float cz = DIMZ * (float) pos.v3;
    MouseVector tmv = mv;
    // Translate gable face to XZ plane at 0,0,0
    tmv.translate({-cx, -cy, -cz});
    Float2 sel_pos;
    Float3 new_pos;
    float depth;
    if (orientation == 3) {        // Rotate frame about ax +33.69 degrees
        tmv.rotate_ax(GABLE_ANGLE);
        sel_pos = tmv.position_at_y(0.0, depth);
        new_pos = {sel_pos.v1, 0.0, sel_pos.v2};
        new_pos = rotate_ax(new_pos, -GABLE_ANGLE);
    } else if (orientation == 2) { // Rotate frame about az +33.69 degrees
        tmv.rotate_az(GABLE_ANGLE);
        sel_pos = tmv.position_at_y(0.0, depth);
        new_pos = {sel_pos.v1, 0.0, sel_pos.v2};
        new_pos = rotate_az(new_pos, -GABLE_ANGLE);
    } else if (orientation == 1) { // Rotate frame about ax -33.69 degrees
        tmv.rotate_ax(-GABLE_ANGLE);
        sel_pos = tmv.position_at_y(0.0, depth);
        new_pos = {sel_pos.v1, 0.0, sel_pos.v2};
        new_pos = rotate_ax(new_pos, GABLE_ANGLE);
    } else {                       // Rotate frame about az -33.69 degrees
        tmv.rotate_az(-GABLE_ANGLE);
        sel_pos = tmv.position_at_y(0.0, depth);
        new_pos = {sel_pos.v1, 0.0, sel_pos.v2};
        new_pos = rotate_az(new_pos, GABLE_ANGLE);
    }
    // Untranslate
    new_pos = translate(new_pos, cx, cy, cz);
    int ix = round(new_pos.v1 / DIMX);
    int iy = round(new_pos.v2 / DIMY);
    int iz = round(new_pos.v3 / DIMZ);
    return {ix, iy, iz};
}

bool Toy::in_rectangle(const Float2& p, const Float2& lower_left, const Float2& upper_right) const
{
    if (p.v1 < lower_left.v1)
        return false;
    if (p.v1 > upper_right.v1)
        return false;
    if (p.v2 < lower_left.v2)
        return false;
    if (p.v2 > upper_right.v2)
        return false;
    return true;
}

Int3 Toy::roof_face_coord(Int3 pos, int orientation, const MouseVector& mv) const
{
    float cx = DIMX * (float) pos.v1;
    float cy = DIMY * (float) pos.v2;
    float cz = DIMZ * (float) pos.v3;
    MouseVector tmv = mv;
    // Translate gable face to XZ plane at 0,0,0
    tmv.translate({-cx, -cy + DIMY / 2.0f, -cz});
    Float2 sel_pos;
    float depth;
    if (orientation == 3) {        //  Rotate frame about az -33.69 degrees
        tmv.rotate_az(-GABLE_ANGLE);
        sel_pos = tmv.position_at_y(0.0, depth);
        if (in_rectangle(sel_pos, {-0.9f * DIMX, -0.75f * DIMX}, {0.6f * DIMX, 0.75f * DIMX})) {
            return pos;
        }
    } else if (orientation == 2) { //  Rotate frame about ax +33.69 degrees
        tmv.rotate_ax(GABLE_ANGLE);
        sel_pos = tmv.position_at_y(0.0, depth);
        if (in_rectangle(sel_pos, {-0.75f * DIMX, -0.9f * DIMX}, {0.75f * DIMX, 0.6f * DIMX})) {
            return pos;
        }
    } else if (orientation == 1) { // Rotate frame about az +33.69 degrees
        tmv.rotate_az(GABLE_ANGLE);
        sel_pos = tmv.position_at_y(0.0, depth);
        if (in_rectangle(sel_pos, {-0.6f * DIMX, -0.75f * DIMX}, {0.9f * DIMX, 0.759f * DIMX})) {
            return pos;
        }
    } else {                       // Rotate frame about ax -33.69 degrees
        tmv.rotate_ax(-GABLE_ANGLE);
        sel_pos = tmv.position_at_y(0.0, depth);
        if (in_rectangle(sel_pos, {-0.75f * DIMX, -0.6f * DIMX}, {0.75f * DIMX, 0.9f * DIMX})) {
            return pos;
        }
    }
    return {0, -2, 0};
}

bool Toy::top_face_selection(int sx, int sy, Int3& pos, bool& gable_flag, int& gable_orientation) const
{
    gable_flag = false;
    gable_orientation = 0;

    MouseVector mv = m_camera->new_mouse_vector(sx, sy);
    Float3 v = mv.vector();
    Int3 sel_pos = top_face_coord_at_level(-1, mv);
    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        int y = e->pos().v2 + e->height() - 1;
        if (y > sel_pos.v2) {
            Int3 new_pos;
            if (e->roof_flag()) {
                new_pos = roof_face_coord(e->pos(), e->orientation(), mv);
            } else if (e->gable_flag()) {
                new_pos = gable_face_coord(e->pos(), e->orientation(), mv);
                // Could be at a different y
            } else {
                new_pos = top_face_coord_at_level(y, mv);
                // Will be at same y
            }

            if (e->contains(new_pos.v1, new_pos.v2, new_pos.v3)) {
                sel_pos = new_pos;
                gable_flag = e->gable_flag();
                if (gable_flag) {
                    gable_orientation = e->orientation();
                }
            }
        }
    }
    if (sel_pos.v2 == -1) { // No top faces selected
        if (!m_table->contains(sel_pos.v1, sel_pos.v3)) {
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
                switch(m_menu->material()) {
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
                switch(m_menu->material()) {
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
                if (m_menu->material() == MATERIAL_ROOF) {
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
            try_delete_top_face(e->button.x, e->button.y);
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

Float3 Toy::rotate_ax(Float3 p, float angle) const
{
   Float3 p1 = p;
   p1.v2 = p.v2 * cos(angle * PI / 180.0) - p.v3 * sin(angle * PI / 180.0);
   p1.v3 = p.v2 * sin(angle * PI / 180.0) + p.v3 * cos(angle * PI / 180.0);
   return p1;
}

Float3 Toy::rotate_ay(Float3 p, float angle) const
{
   Float3 p1 = p;
   p1.v1 = p.v1 * cos(angle * PI / 180.0) + p.v3 * sin(angle * PI / 180.0);
   p1.v3 = -p.v1 * sin(angle * PI / 180.0) + p.v3 * cos(angle * PI / 180.0);
   return p1;
}

Float3 Toy::rotate_az(Float3 p, float angle) const
{
   Float3 p1 = p;
   p1.v1 = p.v1 * cos(angle * PI / 180.0) - p.v2 * sin(angle * PI / 180.0);
   p1.v2 = p.v1 * sin(angle * PI / 180.0) + p.v2 * cos(angle * PI / 180.0);
   return p1;
}

Float3 Toy::translate(Float3 p, float dx, float dy, float dz) const
{
    Float3 p1;
    p1.v1 = p.v1 + dx;
    p1.v2 = p.v2 + dy;
    p1.v3 = p.v3 + dz;
    return p1;
}

float Toy::min_x(const Face& face) const
{
    return fmin(fmin(face.v1.v1, face.v2.v1), fmin(face.v3.v1, face.v4.v1));
}

float Toy::min_y(const Face& face) const
{
    return fmin(fmin(face.v1.v2, face.v2.v2), fmin(face.v3.v2, face.v4.v2));
}

float Toy::min_z(const Face& face) const
{
    return fmin(fmin(face.v1.v3, face.v2.v3), fmin(face.v3.v3, face.v4.v3));
}

float Toy::max_x(const Face& face) const
{
    return fmax(fmax(face.v1.v1, face.v2.v1), fmax(face.v3.v1, face.v4.v1));
}

float Toy::max_y(const Face& face) const
{
    return fmax(fmax(face.v1.v2, face.v2.v2), fmax(face.v3.v2, face.v4.v2));
}

float Toy::max_z(const Face& face) const
{
    return fmax(fmax(face.v1.v3, face.v2.v3), fmax(face.v3.v3, face.v4.v3));
}

void Toy::try_delete_top_face(int sx, int sy)
{
    printf("try_delete_top_face\n");
    MouseVector mv = m_camera->new_mouse_vector(sx, sy);
    Float3 v = mv.vector();
    float min_depth = 100.0;
    int min_element;
    int min_face;
    bool min_top_face;
    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        for (int j = 0; j < e->faces(); j++) {
            float depth;
            bool top_face;
            if (face_intersection(mv, e->face(j, &top_face), depth)) {
                if (depth < min_depth) {
                    min_depth = depth;
                    min_element = i;
                    min_face = j;
                    min_top_face = top_face;
                }
            }
        }
    }
    if (min_depth < 99.0) {
        printf("    Element %d intersection on %s (face %d)\n", min_element, min_top_face ? "top_face" : "other_face", min_face);
    }
#ifdef NEVERMORE
    Int3 pos;
    bool gable_flag;
    int gable_orientation;
    if (top_face_selection(sx, sy, pos, gable_flag, gable_orientation)) {
        if (pos.v2 >= 0) {
            int ix;
            if (m_doc->find_element(ix, pos.v1, pos.v2, pos.v3)) {
                m_history->do_command(new RemoveElementCommand(ix, m_doc));
            }
        }
    }
#endif
}

bool Toy::same(const Float2& a, const Float2& b) const
{
    return a.v1 == b.v1 && a.v2 == b.v2;
}

bool Toy::face_intersection(const MouseVector& mv, const Face& face, float& depth) const
{

    Float2 sel_pos;
    if (face.v1.v1 == face.v2.v1 && face.v1.v1 == face.v3.v1 && face.v1.v1 == face.v4.v1) {
        sel_pos = mv.position_at_x(face.v1.v1, depth);
        if (in_rectangle(sel_pos, {face.v1.v2, face.v1.v3}, {face.v2.v2, face.v2.v3}, {face.v3.v2, face.v3.v3}, {face.v4.v2, face.v4.v3})) {
            printf("    Hit YZ face at pos (%.3f, %3f, %3f)  depth = %.3f\n", face.v1.v1, sel_pos.v1, sel_pos.v2, depth);
            return true;
        }
    } else if (face.v1.v2 == face.v2.v2 && face.v1.v2 == face.v3.v2 && face.v1.v2 == face.v4.v2) {
        sel_pos = mv.position_at_y(face.v1.v2, depth);
        if (in_rectangle(sel_pos, {face.v1.v1, face.v1.v3}, {face.v2.v1, face.v2.v3}, {face.v3.v1, face.v3.v3}, {face.v4.v1, face.v4.v3})) {
            printf("    Hit XZ face at pos (%.3f, %3f, %3f)  depth = %.3f\n", sel_pos.v1, face.v1.v2, sel_pos.v2, depth);
            return true;
        }
    } else if (face.v1.v3 == face.v2.v3 && face.v1.v3 == face.v3.v3 && face.v1.v3 == face.v4.v3) {
        sel_pos = mv.position_at_z(face.v1.v3, depth);
        if (in_rectangle(sel_pos, {face.v1.v1, face.v1.v2}, {face.v2.v1, face.v2.v2}, {face.v3.v1, face.v3.v2}, {face.v4.v1, face.v4.v2})) {
            printf("    Hit XY face at pos (%.3f, %3f, %3f)  depth = %.3f\n", sel_pos.v1, sel_pos.v2, face.v1.v3, depth);
            return true;
        }
    } else {
        printf("    slanting face\n");
        return false;
    }
    return false;
}

double Toy::length(Float2 v1, Float2 v2) const
{
    double a = v1.v1 - v2.v1;
    double b = v1.v2 - v2.v2;
    return sqrt(a * a + b * b);
}

double Toy::tri_area(Float2 v1, Float2 v2, Float2 v3) const
{
    double a = length(v1, v2);
    double b = length(v2, v3);
    double c = length(v3, v1);
    double s = (a + b + c) / 2.0;
    return sqrt(fabs(s * (s - a) * (s - b) * (s - c)));
}

double Toy::quad_area(Float2 v1, Float2 v2, Float2 v3, Float2 v4) const
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

bool Toy::in_rectangle(const Float2& p, const Float2& v1, const Float2& v2, const Float2& v3, const Float2& v4) const
{
    double area1 = quad_area(v1, v2, v3, v4);
    double area2 = tri_area(p, v1, v2) + tri_area(p, v2, v3) + tri_area(p, v3, v4) + tri_area(p, v4, v1);
    return area2 <= (1.01 * area1);
}


