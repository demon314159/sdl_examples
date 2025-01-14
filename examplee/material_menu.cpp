//
// material_menu.cpp
//

#include "material_menu.h"
#include "cube_shape.h"
#include "plane_shape.h"
#include "look.h"
#include <math.h>

#define BUTTON_RADIUS 0.015
#define YPITCH (4.0 * BUTTON_RADIUS)

#define XPOS (2.0 * BUTTON_RADIUS)
#define XPOS2 (XPOS + 3.0 * BUTTON_RADIUS)
#define YPOS (- 2.0 * BUTTON_RADIUS - YPITCH)

#define IMAGEY (YPITCH * 0.9)
#define BIG_IMAGEY (0.9 * (4.0 * YPITCH))


MaterialMenu::MaterialMenu()
    : m_button1(NULL)
    , m_button2(NULL)
    , m_button3(NULL)
    , m_button4(NULL)
    , m_button5(NULL)
    , m_button6(NULL)
    , m_button7(NULL)
    , m_button8(NULL)
    , m_panel1(NULL)
    , m_panel2(NULL)
    , m_panel5(NULL)
    , m_panel6(NULL)
    , m_panel7(NULL)
{
    m_button1 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS + 1.0 * YPITCH, 0.0});
    m_button2 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS, 0.0});
    m_button3 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 1.0 * YPITCH, 0.0});
    m_button4 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 2.0 * YPITCH, 0.0});
    m_button5 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 3.0 * YPITCH, 0.0});
    m_button6 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 4.0 * YPITCH, 0.0});
    m_button7 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 5.0 * YPITCH, 0.0});
    m_button8 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 6.0 * YPITCH, 0.0});
    m_panel2 = new ImagePanel(IMAGEY * 193.0 / 91.0, IMAGEY, {XPOS2, YPOS + YPITCH, 0.0} );
    m_panel1 = new ImagePanel(BIG_IMAGEY * 804.0 / 628.0, BIG_IMAGEY, {XPOS2, YPOS - 1.5 * YPITCH, 0.0} );
    m_panel5 = new ImagePanel(IMAGEY * 640.0 / 842.0, IMAGEY, {XPOS2, YPOS - 4.0 * YPITCH, 0.0} );
    m_panel6 = new ImagePanel(IMAGEY * 479.0 / 933.0, IMAGEY, {XPOS2, YPOS - 5.0 * YPITCH, 0.0} );
    m_panel7 = new ImagePanel(IMAGEY * 199.0 / 116.0, IMAGEY, {XPOS2, YPOS - 6.0 * YPITCH, 0.0} );
    m_width = XPOS2 + BIG_IMAGEY * 804.0 / 628.0;
}


MaterialMenu::~MaterialMenu()
{
    delete m_panel7;
    delete m_panel6;
    delete m_panel5;
    delete m_panel2;
    delete m_panel1;
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

void MaterialMenu::build_uniform(Uniform* uniform) const
{
    uniform->add("animation_1_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button1->data());
    uniform->add("animation_2_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button2->data());
    uniform->add("animation_3_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button3->data());
    uniform->add("animation_4_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button4->data());
    uniform->add("animation_5_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button5->data());
    uniform->add("animation_6_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button6->data());
    uniform->add("animation_7_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button7->data());
    uniform->add("animation_8_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button8->data());
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
}

CadModel MaterialMenu::model() const
{
    CadModel cm;
//    CadModel body(CubeShape(m_width, m_height, m_depth), PaintCan(1.0, 1.0, 1.0), FIXED_ANIMATION_ID);
//    cm.add(body, m_position.v1, m_position.v2, m_position.v3);
    cm.add(m_button1->model(FIXED_ANIMATION_ID, BUTTON1_ANIMATION_ID));
    cm.add(m_button2->model(HIDE_FIXED_ANIMATION_ID, BUTTON2_ANIMATION_ID));
    cm.add(m_button3->model(HIDE_FIXED_ANIMATION_ID, BUTTON3_ANIMATION_ID));
    cm.add(m_button4->model(HIDE_FIXED_ANIMATION_ID, BUTTON4_ANIMATION_ID));
    cm.add(m_button5->model(HIDE_FIXED_ANIMATION_ID, BUTTON5_ANIMATION_ID));
    cm.add(m_button6->model(HIDE_FIXED_ANIMATION_ID, BUTTON6_ANIMATION_ID));
    cm.add(m_button7->model(HIDE_FIXED_ANIMATION_ID, BUTTON7_ANIMATION_ID));
    cm.add(m_button8->model(HIDE_FIXED_ANIMATION_ID, BUTTON8_ANIMATION_ID));
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

void MaterialMenu::press(void)
{
    m_button1->press();
}

void MaterialMenu::release(void)
{
    m_button1->release();
}

