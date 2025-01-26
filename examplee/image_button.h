//
// image_button.h
//

#ifndef _IMAGE_BUTTON_H_
#define _IMAGE_BUTTON_H_

#include "image_panel.h"
#include "float3.h"

class ImageButton
{
public:
    ImageButton(const ImagePanel* panel, float image_dimx, float image_dimy,
                const Float2& region_pos, const Float2& region_size);
    ~ImageButton();
    bool collide(const Float3& sel_pos, const Float3& top_corner) const;

protected:
    float m_image_dimx;
    float m_image_dimy;
    Float2 m_region_pos;
    Float2 m_region_size;
    const ImagePanel* m_panel;
};

#endif // _IMAGE_BUTTON_H_
