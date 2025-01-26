//
// command_menu.cpp
//

#include "command_menu.h"
#include "cube_shape.h"
#include "plane_shape.h"
#include "look.h"
#include <math.h>
#include <stdio.h>

#define BUTTON_RADIUS 0.015
#define YPITCH (4.0 * BUTTON_RADIUS)

#define XPOS (-2.0 * BUTTON_RADIUS)
#define XPOS2 (XPOS - 2.0 * BUTTON_RADIUS)
#define YPOS (- 2.0 * BUTTON_RADIUS)

#define IMAGEY (YPITCH * 0.9)
#define BIG_IMAGEY (9.1 * YPITCH)

#define PANEL8_DIMX 234.0
#define PANEL8_DIMY 827.0
#define BIG_IMAGE_WIDTH  (BIG_IMAGEY * PANEL8_DIMX / PANEL8_DIMY)

#define IBUTTON1_POSITION {52.0, 26.0}
#define IBUTTON1_REGION {170.0, 73.0}
#define IBUTTON2_POSITION {63.0, 119.0}
#define IBUTTON2_REGION {161.0, 75.0}
#define IBUTTON3_POSITION {65.0, 210.0}
#define IBUTTON3_REGION {158.0, 69.0}
#define IBUTTON4_POSITION {50.0, 301.0}
#define IBUTTON4_REGION {172.0, 65.0}
#define IBUTTON5_POSITION {49.0, 391.0}
#define IBUTTON5_REGION {174.0, 72.0}
#define IBUTTON6_POSITION {34.0, 482.0}
#define IBUTTON6_REGION {190.0, 68.0}
#define IBUTTON7_POSITION {39.0, 569.0}
#define IBUTTON7_REGION {184.0, 72.0}
#define IBUTTON8_POSITION {55.0, 661.0}
#define IBUTTON8_REGION {169.0, 82.0}
#define IBUTTON9_POSITION {5.0, 750.0}
#define IBUTTON9_REGION {220.0, 69.0}

CommandMenu::CommandMenu()
    : m_command(COMMAND_NOP)
    , m_button1(NULL)
    , m_button2(NULL)
    , m_button3(NULL)
    , m_button4(NULL)
    , m_button5(NULL)
    , m_button6(NULL)
    , m_button7(NULL)
    , m_button8(NULL)
    , m_button9(NULL)
    , m_panel8(NULL)
    , m_ibutton1(NULL)
    , m_ibutton2(NULL)
    , m_ibutton3(NULL)
    , m_ibutton4(NULL)
    , m_ibutton5(NULL)
    , m_ibutton6(NULL)
    , m_ibutton7(NULL)
    , m_ibutton8(NULL)
    , m_ibutton9(NULL)
{
    m_button1 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS, 0.0});
    m_button2 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 1.0 * YPITCH, 0.0});
    m_button3 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 2.0 * YPITCH, 0.0});
    m_button4 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 3.0 * YPITCH, 0.0});
    m_button5 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 4.0 * YPITCH, 0.0});
    m_button6 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 5.0 * YPITCH, 0.0});
    m_button7 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 6.0 * YPITCH, 0.0});
    m_button8 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 7.0 * YPITCH, 0.0});
    m_button9 = new PushButton(BUTTON_RADIUS, BUTTON_RADIUS / 4.0, {XPOS, YPOS - 8.0 * YPITCH, 0.0});
    m_panel8 = new ImagePanel(BIG_IMAGE_WIDTH, BIG_IMAGEY, {XPOS2 - BIG_IMAGE_WIDTH, YPOS - BIG_IMAGEY / 2.0 + 0.7 * YPITCH, 0.0} );
    m_ibutton1 = new ImageButton(m_panel8, PANEL8_DIMX, PANEL8_DIMY, IBUTTON1_POSITION, IBUTTON1_REGION);
    m_ibutton2 = new ImageButton(m_panel8, PANEL8_DIMX, PANEL8_DIMY, IBUTTON2_POSITION, IBUTTON2_REGION);
    m_ibutton3 = new ImageButton(m_panel8, PANEL8_DIMX, PANEL8_DIMY, IBUTTON3_POSITION, IBUTTON3_REGION);
    m_ibutton4 = new ImageButton(m_panel8, PANEL8_DIMX, PANEL8_DIMY, IBUTTON4_POSITION, IBUTTON4_REGION);
    m_ibutton5 = new ImageButton(m_panel8, PANEL8_DIMX, PANEL8_DIMY, IBUTTON5_POSITION, IBUTTON5_REGION);
    m_ibutton6 = new ImageButton(m_panel8, PANEL8_DIMX, PANEL8_DIMY, IBUTTON6_POSITION, IBUTTON6_REGION);
    m_ibutton7 = new ImageButton(m_panel8, PANEL8_DIMX, PANEL8_DIMY, IBUTTON7_POSITION, IBUTTON7_REGION);
    m_ibutton8 = new ImageButton(m_panel8, PANEL8_DIMX, PANEL8_DIMY, IBUTTON8_POSITION, IBUTTON8_REGION);
    m_ibutton9 = new ImageButton(m_panel8, PANEL8_DIMX, PANEL8_DIMY, IBUTTON9_POSITION, IBUTTON9_REGION);
    m_width = -XPOS2 + BIG_IMAGE_WIDTH;
}

CommandMenu::~CommandMenu()
{
    delete m_ibutton9;
    delete m_ibutton8;
    delete m_ibutton7;
    delete m_ibutton6;
    delete m_ibutton5;
    delete m_ibutton4;
    delete m_ibutton3;
    delete m_ibutton2;
    delete m_ibutton1;
    delete m_panel8;
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

void CommandMenu::build_texture(Texture* texture) const
{
    texture->add("p_panel8.png", "texture8");
}

void CommandMenu::build_uniform(Uniform* uniform)
{
    uniform->add("animation_12_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button1->data());
    uniform->add("animation_13_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button2->data());
    uniform->add("animation_14_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button3->data());
    uniform->add("animation_15_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button4->data());
    uniform->add("animation_16_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button5->data());
    uniform->add("animation_17_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button6->data());
    uniform->add("animation_18_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button7->data());
    uniform->add("animation_19_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button8->data());
    uniform->add("animation_20_matrix", UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR, 1, m_button9->data());
}

void CommandMenu::update_uniform()
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
}

CadModel CommandMenu::model() const
{
    CadModel cm;
    cm.add(m_button1->model(FIXED_RIGHT_ANIMATION_ID, BUTTON12_ANIMATION_ID));
    cm.add(m_button2->model(HIDE_RIGHT_ANIMATION_ID, BUTTON13_ANIMATION_ID));
    cm.add(m_button3->model(HIDE_RIGHT_ANIMATION_ID, BUTTON14_ANIMATION_ID));
    cm.add(m_button4->model(HIDE_RIGHT_ANIMATION_ID, BUTTON15_ANIMATION_ID));
    cm.add(m_button5->model(HIDE_RIGHT_ANIMATION_ID, BUTTON16_ANIMATION_ID));
    cm.add(m_button6->model(HIDE_RIGHT_ANIMATION_ID, BUTTON17_ANIMATION_ID));
    cm.add(m_button7->model(HIDE_RIGHT_ANIMATION_ID, BUTTON18_ANIMATION_ID));
    cm.add(m_button8->model(HIDE_RIGHT_ANIMATION_ID, BUTTON19_ANIMATION_ID));
    cm.add(m_button9->model(HIDE_RIGHT_ANIMATION_ID, BUTTON20_ANIMATION_ID));
    cm.add(m_panel8->model(HIDE_RIGHT_ANIMATION_ID, IMAGE8_TEXTURE_ID));
    return cm;
}

float CommandMenu::width() const
{
    return m_width;
}

int CommandMenu::command() const
{
    return m_command;
}

void CommandMenu::clear_command()
{
    m_command = COMMAND_NOP;
}

bool CommandMenu::hide_button_pressed(const MouseVector& mv, const Float3& top_right, bool hidden) const
{
    Float3 sel_pos = pos_at_zlevel(-1.0, mv);
    if (m_button1->collide(sel_pos, top_right) || (!hidden && m_ibutton1->collide(sel_pos, top_right))) {
        m_button1->press();
        return true;
    }
    return false;
}

bool CommandMenu::menu_button_pressed(const MouseVector& mv, const Float3& top_right)
{
    Float3 sel_pos = pos_at_zlevel(-1.0, mv);
    if (m_button2->collide(sel_pos, top_right) || m_ibutton2->collide(sel_pos, top_right)) {
        if (!m_button2->pressed()) {
            m_command = COMMAND_QUIT;
        }
        m_button2->press();
        return true;
    }
    if (m_button3->collide(sel_pos, top_right) || m_ibutton3->collide(sel_pos, top_right)) {
        if (!m_button3->pressed()) {
            m_command = COMMAND_NEW;
        }
        m_button3->press();
        return true;
    }
    if (m_button4->collide(sel_pos, top_right) || m_ibutton4->collide(sel_pos, top_right)) {
        if (!m_button4->pressed()) {
            m_command = COMMAND_LOAD;
        }
        m_button4->press();
        return true;
    }
    if (m_button5->collide(sel_pos, top_right) || m_ibutton5->collide(sel_pos, top_right)) {
        if (!m_button5->pressed()) {
            m_command = COMMAND_SAVE;
        }
        m_button5->press();
        return true;
    }
    if (m_button6->collide(sel_pos, top_right) || m_ibutton6->collide(sel_pos, top_right)) {
        if (!m_button6->pressed()) {
            m_command = COMMAND_UNDO;
        }
        m_button6->press();
        return true;
    }
    if (m_button7->collide(sel_pos, top_right) || m_ibutton7->collide(sel_pos, top_right)) {
        if (!m_button7->pressed()) {
            m_command = COMMAND_REDO;
        }
        m_button7->press();
        return true;
    }
    if (m_button8->collide(sel_pos, top_right) || m_ibutton8->collide(sel_pos, top_right)) {
        if (!m_button8->pressed()) {
            m_command = COMMAND_HELP;
        }
        m_button8->press();
        return true;
    }
    if (m_button9->collide(sel_pos, top_right) || m_ibutton9->collide(sel_pos, top_right)) {
        if (!m_button9->pressed()) {
            m_command = COMMAND_ABOUT;
        }
        m_button9->press();
        return true;
    }
    return false;
}

Float3 CommandMenu::pos_at_zlevel(float z, const MouseVector& mv) const
{
    float depth;
    Float3 sel_pos = mv.position_at_z(z, depth);
    return {sel_pos.v1, sel_pos.v2, -1.0};
}

void CommandMenu::release(void)
{
    m_button1->release();
    m_button2->release();
    m_button3->release();
    m_button4->release();
    m_button5->release();
    m_button6->release();
    m_button7->release();
    m_button8->release();
    m_button9->release();
}

