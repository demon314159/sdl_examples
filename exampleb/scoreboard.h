//
// scoreboard.h
//

#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include "digit.h"
#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"

class Scoreboard
{
public:
    Scoreboard(const Float3& position, const Float2& size,
               const Float2& backglass_image_size,
               const Float2& trim, const PaintCan& trim_color,
               float texture_id_backglass, float texture_id_score);
    ~Scoreboard();

    CadModel model(float animation_id_first_digit, float animation_id_scoreboard) const;
    int digits() const;
    float* data() const;

    void advance(float seconds);
    void set_digit(int ix, const Digit& digit);
    Digit get_digit(int ix) const;
    int max_players() const;
    int player_digits() const;

private:
    bool m_flash_template;
    float m_flash_timer;
    Float3 m_position;
    Float2 m_size;
    Float2 m_backglass_image_size;
    Float2 m_trim;
    PaintCan m_trim_color;
    float m_texture_id_backglass;
    float m_texture_id_score;
    Digit* m_digit;
    float* m_data;
    CadModel player_digits_model(int player, const Float2& position, const Float2& size, float animation_id_first_digit) const;
    CadModel credits_model(const Float2& position, const Float2& size, float animation_id_first_digit) const;
    CadModel ball_in_play_model(const Float2& position, const Float2& size, float animation_id_first_digit) const;
};

#endif // _SCOREBOARD_H_
