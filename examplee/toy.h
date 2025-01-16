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
    bool top_face_selection(int sx, int sy, Int3& pos) const;
    Int3 coord_at_level(int iy, const MouseVector& mv) const;
    bool try_hide_button(int sx, int sy);
    bool try_menu_button(int sx, int sy);
    void try_top_face(int sx, int sy);
    void adjust_table_size();
};

#endif // _TOY_H_
