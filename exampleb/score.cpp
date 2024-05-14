//
// score.cpp
//

#include "score.h"

#define CREDIT_FIELD 0
#define BALL_IN_PLAY_FIELD 1
#define PLAYER1_FIELD 2

#define FLASH_ON_TIME  1.0
#define FLASH_OFF_TIME 5.0

Score::Score(Scoreboard* scoreboard, Lamp* lamp)
    : m_scoreboard(scoreboard)
    , m_lamp(lamp)
    , m_ball_in_play(0)
    , m_match(0)
    , m_high_game(0)
    , m_fields(2 + m_scoreboard->max_players())
    , m_field(new Field[m_fields])
    , m_flash_high_game(false)
    , m_flash_template(true)
    , m_flash_timer(0.0)
{
    int pd = m_scoreboard->player_digits();
    int mp = m_scoreboard->max_players();
    m_field[0] = {0, false, false, false, 4 * pd, 4 * pd + 1};
    m_field[1] = {0, false, false, true, 4 * pd + 2, 4 * pd + 3};
    for (int i = 0; i < mp; i++) {
        m_field[i + 2] = {0, false, false, false, i * pd, (i + 1) * pd - 1};
    }
    for (int i = 0; i < m_fields; i++) {
        apply_field(i);
    }
}

Score::~Score()
{
    delete [] m_field;
}

void Score::advance(float seconds)
{
    if (m_flash_high_game) {
        m_flash_timer -= seconds;
        if (m_flash_timer <= 0.0) {
            if (m_flash_template) {
                m_flash_template = false;
                m_flash_timer += FLASH_OFF_TIME;
                for (int i = 0; i < m_scoreboard->max_players(); i++) {
                    apply_field(PLAYER1_FIELD + i);
                }
                m_lamp->set(FIXED_LAMP_ID_HIGH_GAME_TO_DATE, false);
            } else {
                m_flash_template = true;
                m_flash_timer += FLASH_ON_TIME;
                for (int i = 0; i < m_scoreboard->max_players(); i++) {
                    apply_high_game(PLAYER1_FIELD + i, m_high_game);
                }
                m_lamp->set(FIXED_LAMP_ID_HIGH_GAME_TO_DATE, true);
            }
        }
    }
}

void Score::apply_field(int ix)
{
    Field f = m_field[ix];
    for (int i = f.first_digit; i <= f.last_digit; i++) {
        if (i == f.last_digit) {
            m_scoreboard->set_digit(i, {0, f.flash, f.blank});
        } else {
            m_scoreboard->set_digit(i, {f.leading_zeroes ? 0 : 10, f.flash, f.blank});
        }
    }
    int pos = f.last_digit;
    while (f.value > 0 && pos >= f.first_digit) {
        int v = f.value % 10;
        f.value = f.value / 10;
        m_scoreboard->set_digit(pos, {v, f.flash, f.blank});
        pos--;
    }
}

void Score::apply_high_game(int ix, int high_game)
{
    Field f = m_field[ix];
    f.value = high_game;
    for (int i = f.first_digit; i <= f.last_digit; i++) {
        if (i == f.last_digit) {
            m_scoreboard->set_digit(i, {0, f.flash, f.blank});
        } else {
            m_scoreboard->set_digit(i, {f.leading_zeroes ? 0 : 10, f.flash, f.blank});
        }
    }
    int pos = f.last_digit;
    while (f.value > 0 && pos >= f.first_digit) {
        int v = f.value % 10;
        f.value = f.value / 10;
        m_scoreboard->set_digit(pos, {v, f.flash, f.blank});
        pos--;
    }
}
void Score::set_credit(int v)
{
    if (v > 15) {
        v = 15;
    }
    m_field[CREDIT_FIELD].value = v;
    apply_field(CREDIT_FIELD);
}

void Score::add_credit(int v)
{
    v += m_field[CREDIT_FIELD].value;
    if (v > 15) {
        v = 15;
    }
    m_field[CREDIT_FIELD].value = v;
    apply_field(CREDIT_FIELD);
}

int Score::get_credit() const
{
    return m_field[CREDIT_FIELD].value;
}

void Score::set_ball_in_play(int v)
{
    m_ball_in_play = v;
    m_field[BALL_IN_PLAY_FIELD].value = v;
    m_field[BALL_IN_PLAY_FIELD].leading_zeroes = false;
    apply_field(BALL_IN_PLAY_FIELD);
    m_flash_high_game = false;
    m_lamp->set(FIXED_LAMP_ID_GAME_OVER, false);
    m_lamp->set(FIXED_LAMP_ID_BALL_IN_PLAY, true);
    m_lamp->set(FIXED_LAMP_ID_NUMBER_TO_MATCH, false);
}

int Score::get_ball_in_play() const
{
    return m_ball_in_play;
}

void Score::set_match(int v)
{
    m_match = v;
    m_field[BALL_IN_PLAY_FIELD].value = v;
    m_field[BALL_IN_PLAY_FIELD].leading_zeroes = true;
    apply_field(BALL_IN_PLAY_FIELD);
    for (int i = 0; i < m_scoreboard->max_players(); i++) {
        m_field[PLAYER1_FIELD + i].flash = false;
        m_field[PLAYER1_FIELD + i].blank = false;
        apply_field(PLAYER1_FIELD + i);
    }
    m_flash_high_game = true;
    m_lamp->set(FIXED_LAMP_ID_GAME_OVER, true);
    m_lamp->set(FIXED_LAMP_ID_BALL_IN_PLAY, false);
    m_lamp->set(FIXED_LAMP_ID_NUMBER_TO_MATCH, true);
    m_lamp->set(FIXED_LAMP_ID_PLAYER_1, false);
    m_lamp->set(FIXED_LAMP_ID_PLAYER_2, false);
    m_lamp->set(FIXED_LAMP_ID_PLAYER_3, false);
    m_lamp->set(FIXED_LAMP_ID_PLAYER_4, false);
}

int Score::get_match() const
{
    return m_match;
}

void Score::set_player_score(int player, int v)
{
    if (player == 0) {
        for (int i = 0; i < m_scoreboard->max_players(); i++) {
            int ix = PLAYER1_FIELD + i;
            m_field[ix].value = v;
            update_high_game(v);
            m_field[ix].flash = false;
            apply_field(ix);
        }
    } else {
        int ix = PLAYER1_FIELD + (player - 1);
        m_field[ix].value = v;
        update_high_game(v);
        m_field[ix].flash = false;
        apply_field(ix);
    }
}

void Score::add_player_score(int player, int v)
{
    int ix = PLAYER1_FIELD + (player - 1);
    m_field[ix].value = m_field[ix].value + v;
    update_high_game(m_field[ix].value);
    m_field[ix].flash = false;
    apply_field(ix);
}

int Score::get_player_score(int player) const
{
    int ix = PLAYER1_FIELD + (player - 1);
    return m_field[ix].value;
}

void Score::set_high_game(int high_game)
{
    m_high_game = high_game;
}

int Score::get_high_game() const
{
    return m_high_game;
}

void Score::update_high_game(int score)
{
    if (score > m_high_game) {
        m_high_game = score;
    }
}

void Score::set_player_flash(int player, bool v)
{
    int ix = PLAYER1_FIELD + (player - 1);
    m_field[ix].flash = v;
    apply_field(ix);
}

void Score::set_player_blank(int player, bool v)
{
    int ix = PLAYER1_FIELD + (player - 1);
    m_field[ix].blank = v;
    apply_field(ix);
}

void Score::set_player(int player)
{
    m_lamp->set(FIXED_LAMP_ID_PLAYER_1, player == 1);
    m_lamp->set(FIXED_LAMP_ID_PLAYER_2, player == 2);
    m_lamp->set(FIXED_LAMP_ID_PLAYER_3, player == 3);
    m_lamp->set(FIXED_LAMP_ID_PLAYER_4, player == 4);
    for (int i = 1; i <= m_scoreboard->max_players(); i++) {
        if (i == player) {
            set_player_flash(i, true);
        } else {
            set_player_blank(i, true);
        }
    }
}
