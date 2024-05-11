//
// lamp.h
//

#ifndef _LAMP_H_
#define _LAMP_H_

#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"

#define MAX_LAMPS 30

#define LAMP_ID_5X_BONUS                 0
#define LAMP_ID_ACES_BONUS               1
#define LAMP_ID_KINGS_BONUS              2
#define LAMP_ID_QUEENS_BONUS             3
#define LAMP_ID_JACKS_BONUS              4
#define LAMP_ID_TENS_BONUS               5
#define LAMP_ID_5000_BONUS               6
#define LAMP_ID_4000_BONUS               7
#define LAMP_ID_3000_BONUS               8
#define LAMP_ID_2000_BONUS               9
#define LAMP_ID_1000_BONUS               10
#define LAMP_ID_TOP_ROLLOVER_A           11
#define LAMP_ID_TOP_ROLLOVER_B           12
#define LAMP_ID_TOP_ROLLOVER_C           13
#define LAMP_ID_BOTTOM_ROLLOVER_A        14
#define LAMP_ID_BOTTOM_LEFT_ROLLOVER_B   15
#define LAMP_ID_BOTTOM_RIGHT_ROLLOVER_B  16
#define LAMP_ID_BOTTOM_ROLLOVER_C        17
#define LAMP_ID_SHOOT_AGAIN              18
#define LAMP_ID_EXTRA_BALL               19
#define LAMP_ID_SPECIAL                  20
#define FIXED_LAMP_ID_BALL_IN_PLAY       21
#define FIXED_LAMP_ID_NUMBER_TO_MATCH    22
#define FIXED_LAMP_ID_HIGH_GAME_TO_DATE  23
#define FIXED_LAMP_ID_GAME_OVER          24
#define FIXED_LAMP_ID_SHOOT_AGAIN        25
#define FIXED_LAMP_ID_PLAYER_1           26
#define FIXED_LAMP_ID_PLAYER_2           27
#define FIXED_LAMP_ID_PLAYER_3           28
#define FIXED_LAMP_ID_PLAYER_4           29

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
