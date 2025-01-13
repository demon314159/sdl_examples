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

class MaterialMenu
{
public:
    MaterialMenu(float width, float height, float depth, const Float3& position);
    ~MaterialMenu();

    void build_texture(Texture* texture) const;
    void build_uniform(Uniform* uniform) const;
    void update_uniform();
    CadModel model() const;

    void press(void);
    void release(void);

protected:
    float m_width;
    float m_height;
    float m_depth;
    Float3 m_position;
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
};

#endif // _MATERIAL_MENU_H_
