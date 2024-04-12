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

    PlasticGuide(const Float2& image_size,
                 const Float2& image_p1, const Float2& image_p2,
                 const Float2& blank_p1, const Float2& blank_p2);

    Float2 blank_size() const;
    Float2 blank_position() const;
    float blank_angle() const;

protected:
    Float2 m_blank_size;
    Float2 m_blank_position;
    float m_blank_angle;

    float angle(const Float2& p1, const Float2& p2) const;
    float length(const Float2& p1, const Float2& p2) const;
    Float2 position(const Float2& p1, const Float2& p2, const Float2& p3) const;
    Float2 position(const Float2& p1, const Float2& p2) const;
    Float2 rotated(Float2 point, float angle) const;
};

#endif // _PLASTIC_GUIDE_H_

