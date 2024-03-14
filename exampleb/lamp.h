//
// lamp.h
//

#ifndef _LAMP_H_
#define _LAMP_H_

#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"

class Lamp
{
public:
    Lamp(float lamp_id, Float3 position, Float2 size, const PaintCan& on_color, const PaintCan& off_color);
    ~Lamp();

    CadModel model() const;

private:
    bool m_state;
    float m_lamp_id;
    Float3 m_position;
    Float2 m_size;
    PaintCan m_on_color;
    PaintCan m_off_color;
};

#endif // _LAMP_H_
