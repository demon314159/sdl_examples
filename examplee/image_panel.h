//
// image_panel.h
//

#ifndef _IMAGE_PANEL_H_
#define _IMAGE_PANEL_H_

#include "float3.h"
#include "cad_model.h"
#include "matrix4x4.h"

class ImagePanel
{
public:
    ImagePanel(float width, float height, const Float3& position);
    ~ImagePanel();

    float width() const;
    float height() const;
    Float3 position() const;

    CadModel model(float animation_id, float texture_id) const;

protected:
    float m_width;
    float m_height;
    Float3 m_position;
};

#endif // _IMAGE_PANEL_H_
