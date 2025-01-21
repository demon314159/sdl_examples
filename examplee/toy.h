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

class Toy: public AnimatedToy
{
public:
    Toy();
    ~Toy();

    bool button(int code, bool shifted, bool on) override;
    bool mouse(SDL_Event* e, bool on) override;
    void advance(int nanoseconds) override;
    Document* get_doc() const;
    Camera* get_camera() const;
    void reframe();

private:
    Table* m_table;
    Document* m_doc;
    History* m_history;
    Choose* m_choose;
    MaterialMenu* m_menu;

    float m_seconds;
    void build_texture();
    void build_model();
    void build_uniform();
    void update_uniform();
    bool top_face_selection(int sx, int sy, Int3& pos, bool& gable_flag, int& gable_orientation) const;
    Int3 top_face_coord_at_level(int iy, const MouseVector& mv) const;
    Int3 gable_face_coord(Int3 pos, int orientation, const MouseVector& mv) const;
    Int3 roof_face_coord(Int3 pos, int orientation, const MouseVector& mv) const;
    bool try_hide_button(int sx, int sy);
    bool try_menu_button(int sx, int sy);
    void try_top_face(int sx, int sy);
    void try_delete_top_face(int sx, int sy);
    void adjust_table_size();
    Float3 rotate_ax(Float3 p, float angle) const;
    Float3 rotate_ay(Float3 p, float angle) const;
    Float3 rotate_az(Float3 p, float angle) const;
    Float3 translate(Float3 p, float dx, float dy, float dz) const;
    bool in_rectangle(const Float2& p, const Float2& lower_left, const Float2& upper_right) const;
};

#endif // _TOY_H_
