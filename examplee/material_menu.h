//
// material_menu.h
//

#ifndef _MATERIAL_MENU_H_
#define _MATERIAL_MENU_H_

#include "float3.h"
#include "cad_model.h"
#include "matrix4x4.h"
#include "push_button.h"
#include "texture.h"
#include "uniform.h"
#include "image_panel.h"
#include "mouse_vector.h"

#define MATERIAL_BRICK         0
#define MATERIAL_DOUBLE_BRICK  1
#define MATERIAL_TRIPLE_BRICK  2
#define MATERIAL_GABLE_BRICK   3
#define MATERIAL_WINDOW        4
#define MATERIAL_DOOR          5
#define MATERIAL_ROOF          6

class MaterialMenu
{
public:
    MaterialMenu();
    ~MaterialMenu();

    void build_texture(Texture* texture) const;
    void build_uniform(Uniform* uniform) const;
    void update_uniform();
    CadModel model() const;
    float width() const;
    int material() const;
    bool hide_button_pressed(const MouseVector& mv, const Float3& top_left) const;
    bool menu_button_pressed(const MouseVector& mv, const Float3& top_left);
    void release(void);

protected:
    float m_width;
    float m_material;
    PushButton* m_button1;
    PushButton* m_button2;
    PushButton* m_button3;
    PushButton* m_button4;
    PushButton* m_button5;
    PushButton* m_button6;
    PushButton* m_button7;
    PushButton* m_button8;
    ImagePanel* m_panel1;
    ImagePanel* m_panel2;
    ImagePanel* m_panel5;
    ImagePanel* m_panel6;
    ImagePanel* m_panel7;
    Float3 pos_at_zlevel(float z, const MouseVector& mv) const;
};

#endif // _MATERIAL_MENU_H_
