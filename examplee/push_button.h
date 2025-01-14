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
    PushButton(float radius, float height, const Float3& position);
    ~PushButton();
    void press();
    void release();

    bool collide(const Float3& sel_pos, const Float3& top_left) const;
    CadModel model(float body_animation_id, float button_animation_id) const;
    const float* data();

protected:
    float m_radius;
    float m_height;
    Float3 m_position;
    bool m_pressed;
    Matrix4x4 m_animate;
};

#endif // _PUSH_BUTTON_H_
