//
// push_button.h
//

#ifndef _PUSH_BUTTON_H_
#define _PUSH_BUTTON_H_

#include "float3.h"
#include "cad_model.h"

#define PUSH_BUTTON_COLOR PaintCan(0.0, 0.0, 1.0)

class PushButton
{
public:
    PushButton(const Float2& dimension, const Float2& position);
    ~PushButton();

    bool mouse_hit(const Float2& mouse_selection) const;
    CadModel model(float animation_id) const;

protected:
    Float2 m_dimension;
    Float2 m_position;
};

#endif // _PUSH_BUTTON_H_
