//
// command_menu.h
//

#ifndef _COMMAND_MENU_H_
#define _COMMAND_MENU_H_

#include "float3.h"
#include "cad_model.h"
#include "matrix4x4.h"
#include "push_button.h"
#include "texture.h"
#include "uniform.h"
#include "image_panel.h"
#include "image_button.h"
#include "mouse_vector.h"

#define COMMAND_QUIT  0
#define COMMAND_NEW   1
#define COMMAND_LOAD  2
#define COMMAND_SAVE  3
#define COMMAND_UNDO  4
#define COMMAND_REDO  5
#define COMMAND_HELP  6
#define COMMAND_ABOUT 7

class CommandMenu
{
public:
    CommandMenu();
    ~CommandMenu();

    void build_texture(Texture* texture) const;
    void build_uniform(Uniform* uniform);
    void update_uniform();
    CadModel model() const;
    float width() const;
    int command() const;
    bool hide_button_pressed(const MouseVector& mv, const Float3& top_right, bool hidden) const;
    bool menu_button_pressed(const MouseVector& mv, const Float3& top_right);
    void release(void);

protected:
    float m_width;
    int m_command;
    PushButton* m_button1;
    PushButton* m_button2;
    PushButton* m_button3;
    PushButton* m_button4;
    PushButton* m_button5;
    PushButton* m_button6;
    PushButton* m_button7;
    PushButton* m_button8;
    PushButton* m_button9;
    ImagePanel* m_panel8;
    Float3 pos_at_zlevel(float z, const MouseVector& mv) const;
    void update_lamp_data();
};

#endif // _COMMAND_MENU_H_
