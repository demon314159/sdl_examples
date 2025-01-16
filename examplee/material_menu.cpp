//
// material_menu.cpp
//

#include "material_menu.h"
#include "cube_shape.h"
#include "plane_shape.h"
#include "look.h"
#include <math.h>
#include <stdio.h>

#define BUTTON_RADIUS 0.015
#define YPITCH (4.0 * BUTTON_RADIUS)

#define XPOS (2.0 * BUTTON_RADIUS)
#define XPOS2 (XPOS + 3.0 * BUTTON_RADIUS)
#define YPOS (- 2.0 * BUTTON_RADIUS - YPITCH)

#define IMAGEY (YPITCH * 0.9)
#define BIG_IMAGEY (0.9 * (4.0 * YPITCH))


MaterialMenu::MaterialMenu()
    : m_material(0)
    , m_button1(NULL)
    , m_button2(NULL)
    , m_button3(NULL)
    , m_button4(NULL)
    , m_button5(NULL)
    , m_button6(NULL)
    , m_button7(NULL)
    , m_button8(NULL)
    , m_button9(NULL)
    , m_panel1(NULL)
    , m_panel2(NULL)
    , m_panel5(NULL)
    , m_panel6(NULL)
    , m_panel7(NULL)
    , m_lamp_data(new float[3 * BUTTON_LAMPS])
{
    m_button1 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS + 1.0 * YPITCH, 0.0});
    m_button2 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS, 0.0});
    m_button3 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 1.0 * YPITCH, 0.0});
    m_button4 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 2.0 * YPITCH, 0.0});
    m_button5 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 3.0 * YPITCH, 0.0});
    m_button6 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 4.0 * YPITCH, 0.0});
    m_button7 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 5.0 * YPITCH, 0.0});
    m_button8 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 6.0 * YPITCH, 0.0});
    m_button9 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 7.0 * YPITCH, 0.0});
    m_panel2 = new ImagePanel(IMAGEY * 193.0 / 91.0, IMAGEY, {XPOS2, YPOS + YPITCH, 0.0} );
    m_panel1 = new ImagePanel(BIG_IMAGEY * 804.0 / 628.0, BIG_IMAGEY, {XPOS2, YPOS - 1.5 * YPITCH, 0.0} );
    m_panel5 = new ImagePanel(IMAGEY * 640.0 / 842.0, IMAGEY, {XPOS2, YPOS - 4.0 * YPITCH, 0.0} );
    m_panel6 = new ImagePanel(IMAGEY * 479.0 / 933.0, IMAGEY, {XPOS2, YPOS - 5.0 * YPITCH, 0.0} );
    m_panel7 = new ImagePanel(IMAGEY * 199.0 / 116.0, IMAGEY, {XPOS2, YPOS - 6.0 * YPITCH, 0.0} );
    m_width = XPOS2 + BIG_IMAGEY * 804.0 / 628.0;
    update_lamp_data();
}

MaterialMenu::~MaterialMenu()
{
    delete [] m_lamp_data;
    delete m_panel7;
    delete m_panel6;
    delete m_panel5;
    delete m_panel2;
    delete m_panel1;
    delete m_button9;
    delete m_button8;
    delete m_button7;
    delete m_button6;
    delete m_button5;
    delete m_button4;
    delete m_button3;
    delete m_button2;
    delete m_button1;
}

void MaterialMenu::build_texture(Texture* texture) const
{
    texture->add("p_bricks.png", "texture1");
    texture->add("p_hide.png", "texture2");
    texture->add("p_window.png", "texture5");
    texture->add("p_door.png", "texture6");
    texture->add("p_roof.png", "texture7");
}

void MaterialMenu::build_uniform(Uniform* uniform)
{
    uniform->add("animation_1_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button1->data());
    uniform->add("animation_2_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button2->data());
    uniform->add("animation_3_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button3->data());
    uniform->add("animation_4_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button4->data());
    uniform->add("animation_5_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button5->data());
    uniform->add("animation_6_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button6->data());
    uniform->add("animation_7_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button7->data());
    uniform->add("animation_8_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button8->data());
    uniform->add("animation_9_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button9->data());
    uniform->add("lamp_color", UNIFORM_TYPE_3_FLOAT_VECTOR, BUTTON_LAMPS, (void*) m_lamp_data);
}

void MaterialMenu::update_uniform()
{
    m_button1->data();
    m_button2->data();
    m_button3->data();
    m_button4->data();
    m_button5->data();
    m_button6->data();
    m_button7->data();
    m_button8->data();
    m_button9->data();
    update_lamp_data();
}

void MaterialMenu::update_lamp_data()
{
    for (int i = 0; i < BUTTON_LAMPS; i++) {
        if (m_material == i) {
           Float3 c = PUSH_BUTTON_COLOR_LIT.ambient_color();
           m_lamp_data[3 * i + 0] = c.v1;
           m_lamp_data[3 * i + 1] = c.v2;
           m_lamp_data[3 * i + 2] = c.v3;
        } else {
           Float3 c = PUSH_BUTTON_COLOR.ambient_color();
           m_lamp_data[3 * i + 0] = c.v1;
           m_lamp_data[3 * i + 1] = c.v2;
           m_lamp_data[3 * i + 2] = c.v3;
        }
    }
}

CadModel MaterialMenu::model() const
{
    CadModel cm;
    cm.add(m_button1->model(FIXED_ANIMATION_ID, BUTTON1_ANIMATION_ID));
    cm.add(m_button2->model(HIDE_FIXED_ANIMATION_ID, BUTTON2_ANIMATION_ID, LAMP1_TEXTURE_ID));
    cm.add(m_button3->model(HIDE_FIXED_ANIMATION_ID, BUTTON3_ANIMATION_ID, LAMP2_TEXTURE_ID));
    cm.add(m_button4->model(HIDE_FIXED_ANIMATION_ID, BUTTON4_ANIMATION_ID, LAMP3_TEXTURE_ID));
    cm.add(m_button5->model(HIDE_FIXED_ANIMATION_ID, BUTTON5_ANIMATION_ID, LAMP4_TEXTURE_ID));
    cm.add(m_button6->model(HIDE_FIXED_ANIMATION_ID, BUTTON6_ANIMATION_ID, LAMP5_TEXTURE_ID));
    cm.add(m_button7->model(HIDE_FIXED_ANIMATION_ID, BUTTON7_ANIMATION_ID, LAMP6_TEXTURE_ID));
    cm.add(m_button8->model(HIDE_FIXED_ANIMATION_ID, BUTTON8_ANIMATION_ID, LAMP7_TEXTURE_ID));
    cm.add(m_button9->model(HIDE_FIXED_ANIMATION_ID, BUTTON9_ANIMATION_ID, LAMP8_TEXTURE_ID));
    cm.add(m_panel1->model(HIDE_FIXED_ANIMATION_ID, IMAGE1_TEXTURE_ID));
    cm.add(m_panel2->model(HIDE_FIXED_ANIMATION_ID, IMAGE2_TEXTURE_ID));
    cm.add(m_panel5->model(HIDE_FIXED_ANIMATION_ID, IMAGE5_TEXTURE_ID));
    cm.add(m_panel6->model(HIDE_FIXED_ANIMATION_ID, IMAGE6_TEXTURE_ID));
    cm.add(m_panel7->model(HIDE_FIXED_ANIMATION_ID, IMAGE7_TEXTURE_ID));
    return cm;
}

float MaterialMenu::width() const
{
    return m_width;
}

int MaterialMenu::material() const
{
    return m_material;
}

bool MaterialMenu::hide_button_pressed(const MouseVector& mv, const Float3& top_left) const
{
    Float3 sel_pos = pos_at_zlevel(-1.0, mv);
    if (m_button1->collide(sel_pos, top_left)) {
        m_button1->press();
        return true;
    }
    return false;
}

bool MaterialMenu::menu_button_pressed(const MouseVector& mv, const Float3& top_left)
{
    Float3 sel_pos = pos_at_zlevel(-1.0, mv);
    if (m_button2->collide(sel_pos, top_left)) {
        m_button2->press();
        m_material = MATERIAL_BRICK;
        return true;
    }
    if (m_button3->collide(sel_pos, top_left)) {
        m_button3->press();
        m_material = MATERIAL_FOUNDATION;
        return true;
    }
    if (m_button4->collide(sel_pos, top_left)) {
        m_button4->press();
        m_material = MATERIAL_DOUBLE_FOUNDATION;
        return true;
    }
    if (m_button5->collide(sel_pos, top_left)) {
        m_button5->press();
        m_material = MATERIAL_TRIPLE_FOUNDATION;
        return true;
    }
    if (m_button6->collide(sel_pos, top_left)) {
        m_button6->press();
        m_material = MATERIAL_GABLE_BRICK;
        return true;
    }
    if (m_button7->collide(sel_pos, top_left)) {
        m_button7->press();
        m_material = MATERIAL_ROOF;
        return true;
    }
    if (m_button8->collide(sel_pos, top_left)) {
        m_button8->press();
        m_material = MATERIAL_WINDOW;
        return true;
    }
    if (m_button9->collide(sel_pos, top_left)) {
        m_button9->press();
        m_material = MATERIAL_DOOR;
        return true;
    }
    return false;
}

Float3 MaterialMenu::pos_at_zlevel(float z, const MouseVector& mv) const
{
        Float2 sel_pos = mv.position_at_z(z);
        return {sel_pos.v1, sel_pos.v2, -1.0};
}

void MaterialMenu::release(void)
{
    m_button1->release();
    m_button2->release();
    m_button3->release();
    m_button4->release();
    m_button5->release();
    m_button6->release();
    m_button7->release();
    m_button8->release();
}

