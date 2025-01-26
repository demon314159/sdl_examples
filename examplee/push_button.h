//
// push_button.h
//

#ifndef _PUSH_BUTTON_H_
#define _PUSH_BUTTON_H_

#include "float3.h"
#include "cad_model.h"
#include "matrix4x4.h"

#define PUSH_BUTTON_COLOR PaintCan(1.0, 0.25, 0.25)
#define PUSH_BUTTON_COLOR_LIT PaintCan(0.25, 0.75, 0.25)

#define BEVEL_COLOR PaintCan(0.25, 0.25, 0.25)

class PushButton
{
public:
    PushButton(float radius, float height, const Float3& position);
    ~PushButton();
    void press();
    void release();
    bool pressed() const;

    bool collide(const Float3& sel_pos, const Float3& top_corner) const;
    CadModel model(float body_animation_id, float button_animation_id, float lamp_texture_id = 0.0) const;
    const float* data();

protected:
    float m_radius;
    float m_height;
    Float3 m_position;
    bool m_pressed;
    Matrix4x4 m_animate;
};

#endif // _PUSH_BUTTON_H_
