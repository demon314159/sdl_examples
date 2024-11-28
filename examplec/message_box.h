//
// message_box.h
//

#ifndef _MESSAGE_BOX_H_
#define _MESSAGE_BOX_H_

#include "float3.h"
#include "cad_model.h"
#include "matrix4x4.h"


class MessageBox
{
public:
    MessageBox(float width, float height, const Float2& position);
    ~MessageBox();

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

#endif // _MESSAGE_BOX_H_
