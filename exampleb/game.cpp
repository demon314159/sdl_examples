//
// game.cpp
//

#include "game.h"

#define SCORE_DELAY 150 // milliseconds
#define BONUS_DELAY 250 // milliseconds

Game::Game(int credit, int max_players, int max_balls,
           Sensor* sensor, Target* target, Lamp* lamp, Queue* queue)
    : m_credit(credit)
    , m_max_players(max_players)
    , m_max_balls(max_balls)
    , m_sensor(sensor)
    , m_target(target)
    , m_lamp(lamp)
    , m_queue(queue)
    , m_players(0)
    , m_player_up(0)
    , m_ball_in_play(0)
    , m_game_in_progress(false)
    , m_match_value(0)
    , m_rollover_a(false)
    , m_rollover_b(false)
    , m_rollover_c(false)
    , m_scored(false)
{
    m_queue->put(QCOMMAND_ADD_CREDIT, 0, credit);
}

Game::~Game()
{
}

//int Game::ball_in_play() const
//{
//    return m_ball_in_play;
//}

//int Game::player_up() const
//{
//    return m_player_up;
//}

//int Game::players() const
//{
//    return m_players;
//}

//int Game::credit() const
//{
//    return m_credit;
//}

void Game::add_credit()
{
    ++m_credit;
}

void Game::add_player()
{
    if (m_credit > 0 && !m_game_in_progress) {
        if (m_players < m_max_players) {
            ++m_players;
            m_player_up = 1;
            m_ball_in_play = 1;
            --m_credit;
            if (m_players == 1) {
                m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_HUNDREDS_CHIME);
                m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_ALL);
                m_queue->put(QCOMMAND_ADD_CREDIT, 0, -1);
                m_queue->put(QCOMMAND_SET_SCORE, 0, 0);
                m_queue->put(QCOMMAND_SET_PLAYER, 0, m_player_up);
                m_queue->put(QCOMMAND_SET_BALL, 0, m_ball_in_play);
                set_rollover_lamps();
                m_queue->put(QCOMMAND_DELAY, 0, SCORE_DELAY);
                m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_OUT_HOLE);
            } else {
                m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_HUNDREDS_CHIME);
                m_queue->put(QCOMMAND_ADD_CREDIT, 0, -1);
                m_queue->put(QCOMMAND_SET_BLANK, m_players, 0);
                m_queue->put(QCOMMAND_SET_FLASH, m_players, 0);
                m_queue->put(QCOMMAND_DELAY, 0, SCORE_DELAY);
            }
        }
    }
}

void Game::set_rollover_lamps()
{
    m_rollover_a = false;
    m_rollover_b = false;
    m_rollover_c = false;
    m_scored = false;
    m_lamp->set(LAMP_ID_TOP_ROLLOVER_A, true);
    m_lamp->set(LAMP_ID_TOP_ROLLOVER_B, true);
    m_lamp->set(LAMP_ID_TOP_ROLLOVER_C, true);
    m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_A, true);
    m_lamp->set(LAMP_ID_BOTTOM_LEFT_ROLLOVER_B, true);
    m_lamp->set(LAMP_ID_BOTTOM_RIGHT_ROLLOVER_B, true);
    m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_C, true);
    m_lamp->set(LAMP_ID_EXTRA_BALL, false);
    m_lamp->set(LAMP_ID_SPECIAL, false);
}

void Game::next_player()
{
    if (!m_lamp->lit(LAMP_ID_SHOOT_AGAIN)) {
        if (m_player_up == m_players) {
            if (m_ball_in_play == (m_max_balls + 1)) {
                m_ball_in_play = 0;
                m_player_up = 0;
            } else {
                m_player_up = 1;
                ++m_ball_in_play;
            }
        } else {
            ++m_player_up;
        }
    }
    if (m_ball_in_play > 0 && m_player_up > 0) {
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_HUNDREDS_CHIME);
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_ALL);
        m_queue->put(QCOMMAND_SET_PLAYER, 0, m_player_up);
        m_queue->put(QCOMMAND_SET_BALL, 0, m_ball_in_play);
        for (int i = 0; i < m_players; i++) {
            m_queue->put(QCOMMAND_SET_BLANK, i + 1, 0);
        }
        set_rollover_lamps();
        m_queue->put(QCOMMAND_DELAY, 0, SCORE_DELAY);
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_OUT_HOLE);
    } else {
        m_queue->put(QCOMMAND_SET_MATCH, 0, m_match_value * 10);
        m_game_in_progress = false;
        m_players = 0;
    }
}

void Game::apply_rules()
{
    if (m_game_in_progress && m_sensor->rising(SENSOR_ID_OUTHOLE)) {
        scoring_sequence();
        next_player();
    } else {
        rollover_rules();
        target_rules();
        if (m_sensor->rising(SENSOR_ID_BUMPER)) {
                multiscore(1, SOLENOID_ID_HUNDREDS_CHIME, 100);
        }
        if (m_sensor->rising(SENSOR_ID_TEN_POINT)) {
                multiscore(1, SOLENOID_ID_TENS_CHIME, 10);
        }
    }
}

void Game::scoring_sequence()
{
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_1000_BONUS, 1);
    if (m_lamp->lit(LAMP_ID_TENS_BONUS)) {
        if (m_lamp->lit(LAMP_ID_5X_BONUS)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(1, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        }
    }
    m_queue->put(QCOMMAND_DELAY, 0, BONUS_DELAY);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_1000_BONUS, 0);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_TENS_BONUS, 0);
    //
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_2000_BONUS, 1);
    if (m_lamp->lit(LAMP_ID_JACKS_BONUS)) {
        if (m_lamp->lit(LAMP_ID_5X_BONUS)) {
            multiscore(10, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(2, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        }
    }
    m_queue->put(QCOMMAND_DELAY, 0, BONUS_DELAY);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_2000_BONUS, 0);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_JACKS_BONUS, 0);
    //
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_3000_BONUS, 1);
    if (m_lamp->lit(LAMP_ID_QUEENS_BONUS)) {
        if (m_lamp->lit(LAMP_ID_5X_BONUS)) {
            multiscore(15, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(3, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        }
    }
    m_queue->put(QCOMMAND_DELAY, 0, BONUS_DELAY);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_3000_BONUS, 0);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_QUEENS_BONUS, 0);
    //
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_4000_BONUS, 1);
    if (m_lamp->lit(LAMP_ID_KINGS_BONUS)) {
        if (m_lamp->lit(LAMP_ID_5X_BONUS)) {
            multiscore(20, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(4, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        }
    }
    m_queue->put(QCOMMAND_DELAY, 0, BONUS_DELAY);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_4000_BONUS, 0);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_KINGS_BONUS, 0);
    //
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_5000_BONUS, 1);
    if (m_lamp->lit(LAMP_ID_ACES_BONUS)) {
        if (m_lamp->lit(LAMP_ID_5X_BONUS)) {
            multiscore(25, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        }
    }
    m_queue->put(QCOMMAND_DELAY, 0, BONUS_DELAY);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_5000_BONUS, 0);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_ACES_BONUS, 0);
    m_queue->put(QCOMMAND_SET_LAMP, LAMP_ID_5X_BONUS, 0);
}

void Game::multiscore(int n, int solenoid_id, int score)
{
    if (!m_scored) {
        m_lamp->set(LAMP_ID_SHOOT_AGAIN, false);
        m_lamp->set(FIXED_LAMP_ID_SHOOT_AGAIN, false);
        m_scored = true;
    }
    m_game_in_progress = true;
    for (int i = 0; i < n; i++) {
        m_queue->put(QCOMMAND_SOLENOID, 0, solenoid_id);
        m_queue->put(QCOMMAND_ADD_SCORE, m_player_up, score);
        m_queue->put(QCOMMAND_DELAY, 0, SCORE_DELAY);
        ++m_match_value;
        m_match_value = m_match_value % 10;
    }
}

void Game::rollover_rules()
{
    if (m_sensor->rising(SENSOR_ID_ROLLOVER_A)) {
        m_lamp->set(LAMP_ID_TOP_ROLLOVER_A, false);
        m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_A, false);
        m_rollover_a = true;
        if (m_lamp->lit(LAMP_ID_TOP_ROLLOVER_A)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        }
    }
    if (m_sensor->rising(SENSOR_ID_ROLLOVER_B)) {
        m_lamp->set(LAMP_ID_TOP_ROLLOVER_B, false);
        m_lamp->set(LAMP_ID_BOTTOM_LEFT_ROLLOVER_B, false);
        m_lamp->set(LAMP_ID_BOTTOM_RIGHT_ROLLOVER_B, false);
        m_rollover_b = true;
        if (m_lamp->lit(LAMP_ID_TOP_ROLLOVER_B)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        }
    }
    if (m_sensor->rising(SENSOR_ID_ROLLOVER_C)) {
        m_lamp->set(LAMP_ID_TOP_ROLLOVER_C, false);
        m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_C, false);
        m_rollover_c = true;
        if (m_lamp->lit(LAMP_ID_TOP_ROLLOVER_C)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        }
    }
    if (m_sensor->rising(SENSOR_ID_SPECIAL)) {
        multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        if (m_lamp->lit(LAMP_ID_SPECIAL)) {
//            m_scoreboard->add_credit();
            m_lamp->set(LAMP_ID_SPECIAL, false);
        }
    }
    if (m_rollover_a && m_rollover_b && m_rollover_c) {
        if (!m_lamp->lit(LAMP_ID_EXTRA_BALL)) {
            m_lamp->set(LAMP_ID_EXTRA_BALL, true);
        }
    }
}

void Game::target_score(int lamp_id)
{
    if (m_lamp->lit(lamp_id)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
    } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
    }
}

void Game::tens_bonus_test()
{
    if (one_ten_dropped()) {
        if (m_ball_in_play == 1) {
            m_lamp->set(LAMP_ID_5X_BONUS, true);
        }
        m_lamp->set(LAMP_ID_TENS_BONUS, true);
    }
}

void Game::jacks_bonus_test()
{
    if (two_jacks_dropped()) {
        if (m_ball_in_play == 2) {
            m_lamp->set(LAMP_ID_5X_BONUS, true);
        }
        m_lamp->set(LAMP_ID_JACKS_BONUS, true);
    }
}

void Game::queens_bonus_test()
{
    if (queens_dropped()) {
        if (m_ball_in_play == 3) {
            m_lamp->set(LAMP_ID_5X_BONUS, true);
        }
        m_lamp->set(LAMP_ID_QUEENS_BONUS, true);
    }
}

void Game::kings_bonus_test()
{
    if (kings_dropped()) {
        if (m_ball_in_play == 4) {
            m_lamp->set(LAMP_ID_5X_BONUS, true);
        }
        m_lamp->set(LAMP_ID_KINGS_BONUS, true);
    }
}

void Game::aces_bonus_test()
{
    if (aces_dropped()) {
        if (m_ball_in_play == 5) {
            m_lamp->set(LAMP_ID_5X_BONUS, true);
        }
        m_lamp->set(LAMP_ID_ACES_BONUS, true);
    }
}

void Game::target_rules()
{
    if (m_sensor->rising(SENSOR_ID_EXTRA_BALL)) {
        if (m_lamp->lit(LAMP_ID_EXTRA_BALL)) {
            m_lamp->set(LAMP_ID_SHOOT_AGAIN, true);
            m_lamp->set(FIXED_LAMP_ID_SHOOT_AGAIN, true);
        }
        multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
    }
    if (m_sensor->rising(SENSOR_ID_DROP_10)) {
        target_score(LAMP_ID_TENS_BONUS);
        tens_bonus_test();
        jacks_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_J1)) {
        jacks_bonus_test();
        target_score(LAMP_ID_JACKS_BONUS);
        jacks_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_J2)) {
        jacks_bonus_test();
        target_score(LAMP_ID_JACKS_BONUS);
        jacks_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_Q1)) {
        queens_bonus_test();
        target_score(LAMP_ID_QUEENS_BONUS);
        queens_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_Q2)) {
        queens_bonus_test();
        target_score(LAMP_ID_QUEENS_BONUS);
        queens_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_Q3)) {
        queens_bonus_test();
        target_score(LAMP_ID_QUEENS_BONUS);
        queens_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K1)) {
        kings_bonus_test();
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K2)) {
        kings_bonus_test();
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K3)) {
        kings_bonus_test();
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K4)) {
        kings_bonus_test();
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A1)) {
        aces_bonus_test();
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A2)) {
        aces_bonus_test();
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A3)) {
        aces_bonus_test();
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A4)) {
        aces_bonus_test();
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_JOKER)) {
        aces_bonus_test();
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
}

bool Game::one_ten_dropped() const
{
    if (!m_target->dropped(DROP_TARGET_ID_10))
        return false;
    return true;
}

bool Game::two_jacks_dropped() const
{
    if (!m_target->dropped(DROP_TARGET_ID_J1))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_J2))
        return false;
    return true;
}

bool Game::jacks_dropped() const
{
    if (!m_target->dropped(DROP_TARGET_ID_10))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_J1))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_J2))
        return false;
    return true;
}

bool Game::queens_dropped() const
{
    if (!m_target->dropped(DROP_TARGET_ID_Q1))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_Q2))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_Q3))
        return false;
    return true;
}

bool Game::kings_dropped() const
{
    if (!m_target->dropped(DROP_TARGET_ID_K1))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_K2))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_K3))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_K4))
        return false;
    return true;
}

bool Game::aces_dropped() const
{
    if (!m_target->dropped(DROP_TARGET_ID_A1))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_A2))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_JOKER))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_A3))
        return false;
    if (!m_target->dropped(DROP_TARGET_ID_A4))
        return false;
    return true;
}

void Game::jacks_test()
{
    if (jacks_dropped()) {
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_JACKS);
        multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
    }
}

void Game::queens_test()
{
    if (queens_dropped()) {
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_QUEENS);
        multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
    }
}

void Game::kings_test()
{
    if (kings_dropped()) {
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_KINGS);
        multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
    }
}

void Game::aces_test()
{
    if (aces_dropped()) {
        m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_ACES);
        multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
    }
}


