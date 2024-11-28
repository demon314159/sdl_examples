//
// push_button.h
//

#ifndef _PUSH_BUTTON_H_
#define _PUSH_BUTTON_H_

#include "float3.h"
#include "cad_model.h"
#include "matrix4x4.h"


class PushButton
{
public:
    PushButton(float radius, float height, const Float2& position);
    ~PushButton();

    bool mouse_hit(const Float2& mouse_selection);
    void release();

    CadModel model(float animation_id, float texture_id) const;
    const float* data();

protected:
    float m_radius;
    float m_height;
    Float2 m_position;
    bool m_pressed;
    Matrix4x4 m_animate;
};

#endif // _PUSH_BUTTON_H_
