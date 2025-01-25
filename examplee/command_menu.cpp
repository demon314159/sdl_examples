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
#define XPOS2 (XPOS - 3.0 * BUTTON_RADIUS)
#define YPOS (- 2.0 * BUTTON_RADIUS - YPITCH)

#define IMAGEY (YPITCH * 0.9)
#define BIG_IMAGEY (0.95 * (5.0 * YPITCH))

CommandMenu::CommandMenu()
    : m_command(COMMAND_QUIT)
    , m_button1(NULL)
    , m_button2(NULL)
    , m_button3(NULL)
    , m_button4(NULL)
    , m_button5(NULL)
    , m_button6(NULL)
    , m_button7(NULL)
    , m_button8(NULL)
    , m_button9(NULL)
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
    m_width = -XPOS2;
}

CommandMenu::~CommandMenu()
{
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

bool CommandMenu::hide_button_pressed(const MouseVector& mv, const Float3& top_right, bool hidden) const
{
    Float3 sel_pos = pos_at_zlevel(-1.0, mv);
    if (m_button1->collide(sel_pos, top_right)) {
        m_button1->press();
        return true;
    }
    return false;
}

bool CommandMenu::menu_button_pressed(const MouseVector& mv, const Float3& top_right)
{
    Float3 sel_pos = pos_at_zlevel(-1.0, mv);
    if (m_button2->collide(sel_pos, top_right)) {
        m_button2->press();
        m_command = COMMAND_QUIT;
        return true;
    }
    if (m_button3->collide(sel_pos, top_right)) {
        m_button3->press();
        m_command = COMMAND_NEW;
        return true;
    }
    if (m_button4->collide(sel_pos, top_right)) {
        m_button4->press();
        m_command = COMMAND_LOAD;
        return true;
    }
    if (m_button5->collide(sel_pos, top_right)) {
        m_button5->press();
        m_command = COMMAND_SAVE;
        return true;
    }
    if (m_button6->collide(sel_pos, top_right)) {
        m_button6->press();
        m_command = COMMAND_UNDO;
        return true;
    }
    if (m_button7->collide(sel_pos, top_right)) {
        m_button7->press();
        m_command = COMMAND_REDO;
        return true;
    }
    if (m_button8->collide(sel_pos, top_right)) {
        m_button8->press();
        m_command = COMMAND_HELP;
        return true;
    }
    if (m_button9->collide(sel_pos, top_right)) {
        m_button9->press();
        m_command = COMMAND_ABOUT;
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

