//
// message_panel.h
//

#ifndef _MESSAGE_PANEL_H_
#define _MESSAGE_PANEL_H_

#include "float3.h"
#include "cad_model.h"
#include "matrix4x4.h"


class MessagePanel
{
public:
    MessagePanel(float width, float height, const Float2& position);
    ~MessagePanel();

    void set_visible(bool v);

    CadModel model(float texture_id) const;
    const float* data();

protected:
    float m_width;
    float m_height;
    Float2 m_position;
    bool m_visible;
    float m_animate;
};

#endif // _MESSAGE_PANEL_H_
