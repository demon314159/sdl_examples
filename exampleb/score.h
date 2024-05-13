//
// score.h
//

#ifndef _SCORE_H_
#define _SCORE_H_

#include "scoreboard.h"
#include "lamp.h"
#include "field.h"

class Score
{
public:
    Score(Scoreboard* scoreboard, Lamp* lamp);
    ~Score();

    void advance(float seconds);

    void set_credit(int v);
    void add_credit(int v);
    int get_credit() const;

    void set_ball_in_play(int v);
    int get_ball_in_play() const;

    void set_match(int v);
    int get_match() const;

    void set_player_score(int player, int v);
    void add_player_score(int player, int v);
    int get_player_score(int player) const;

    void set_high_game(int high_game);
    int get_high_game() const;

    void set_player_flash(int player, bool v);
    void set_player_blank(int player, bool v);

private:
    Scoreboard* m_scoreboard;
    Lamp* m_lamp;
    int m_ball_in_play;
    int m_match;
    int m_high_game;
    int m_fields;
    Field* m_field;
    bool m_flash_high_game;
    bool m_flash_template;
    float m_flash_timer;
    void apply_field(int ix);
    void apply_high_game(int ix, int high_game);
    void update_high_game(int score);
};

#endif // _SCORE_H_
