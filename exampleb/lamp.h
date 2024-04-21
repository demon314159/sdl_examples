//
// lamp.h
//

#ifndef _LAMP_H_
#define _LAMP_H_

#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"

#define MAX_LAMPS 30

class Lamp
{
public:
    Lamp(float animation_id_fixed_lamp1);
    ~Lamp();

    int lamps() const;
    void add(Float3 position, Float2 size, const PaintCan& on_color, const PaintCan& off_color);

    CadModel model(float animation_id) const;
    Float3 color(int ix) const;
    bool lit(int ix) const;
    void set(int ix, bool v);
    void toggle(int ix);
    float* data() const;

private:
    float m_animation_id_fixed_lamp1;
    int m_lamps;
    bool m_state[MAX_LAMPS];
    Float3 m_position[MAX_LAMPS];
    Float2 m_size[MAX_LAMPS];
    Float3 m_on_color[MAX_LAMPS];
    Float3 m_off_color[MAX_LAMPS];
    float* m_data;
};

#endif // _LAMP_H_
