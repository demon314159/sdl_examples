//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "animated_toy.h"
#include "document.h"
#include "choose.h"
#include "history.h"
#include "table.h"
#include "material_menu.h"
#include "command_menu.h"

class Toy: public AnimatedToy
{
public:
    Toy();
    ~Toy();

    bool button(int code, bool shifted, bool on) override;
    bool mouse(SDL_Event* e, bool on) override;
    void advance(int nanoseconds) override;
    bool quit_signal() const override;
    Document* get_doc() const;
    Camera* get_camera() const;
    void reframe();

private:
    Table* m_table;
    Document* m_doc;
    History* m_history;
    Choose* m_choose;
    MaterialMenu* m_left_menu;
    CommandMenu* m_right_menu;
    bool m_quit_signal;
    float m_seconds;
    void build_texture();
    void build_model();
    void build_uniform();
    void update_uniform();
    Int3 table_coord_selected(const MouseVector& mv, float& depth) const;
    bool top_face_selection(int sx, int sy, Int3& pos, bool& gable_flag, int& gable_orientation) const;
    bool try_hide_button(int sx, int sy);
    bool try_menu_button(int sx, int sy);
    void try_top_face(int sx, int sy);
    void try_delete_any_face(int sx, int sy);
    void adjust_table_size();
    void execute_right_menu_command();

    bool mouse_vector_intersects_face(const MouseVector& mv, const Face& f, float& depth, Float3& ip) const;
    Float3 normal(const Face& f) const;
    bool in_face(const Float3& p, const Face& f) const;
    double length(const Float3& v1, const Float3& v2) const;
    double tri_area(const Float3& v1, const Float3& v2, const Float3& v3) const;
    double quad_area(const Float3& v1, const Float3& v2, const Float3& v3, const Float3& v4) const;
};

#endif // _TOY_H_
