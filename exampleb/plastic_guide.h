//
// plastic_guide.h
//

#ifndef _PLASTIC_GUIDE_H_
#define _PLASTIC_GUIDE_H_

#include "float3.h"

class PlasticGuide
{
public:
    PlasticGuide(const Float2& image_size,
                 const Float2& image_p1, const Float2& image_p2, const Float2& image_p3,
                 const Float2& blank_p1, const Float2& blank_p2, const Float2& blank_p3);

    Float2 blank_size() const;
    Float2 blank_position() const;
    float blank_angle() const;

protected:
    Float2 m_image_size;
    Float2 m_image_p1;
    Float2 m_image_p2;
    Float2 m_image_p3;
    Float2 m_blank_p1;
    Float2 m_blank_p2;
    Float2 m_blank_p3;
};

#endif // _PLASTIC_GUIDE_H_

