//
// score.h
//

#ifndef _SCORE_H_
#define _SCORE_H_

#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"
#include "queue.h"

class Score
{
public:
    Score(int max_players, int digits, const Float3& position, const Float2& size,
          float texture_id_backglass, float texture_id_score);
    ~Score();

    CadModel model(float animation_id_first_digit, float animation_id_scoreboard) const;
    void advance(float seconds);
    int digits() const;
    float* data() const;

    void clear();
    void start_replay(int sound_solenoid_id, int out_hole_solenoid_id);
    void add_tens(int player, int n, int solenoid_id);
    void add_hundreds(int player, int n, int solenoid_id);
    void add_thousands(int player, int n, int solenoid_id);

    int solenoid_id() const;

private:
    int m_max_players;
    int m_digits;
    Float3 m_position;
    Float2 m_size;
    float m_texture_id_backglass;
    float m_texture_id_score;
    int* m_digit;
    float* m_data;
    float m_delay_time;
    int m_solenoid_id;
    Queue* m_queue;

    bool non_zero_digits() const;
    void perform_action(int command, int digit, int solenoid_id);
    void command_clear_digits(int solenoid_id);
    void command_increment_digit(int digit, int solenoid_id);
    void command_out_hole(int solenoid_id);
};

#endif // _SCORE_H_
