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
    , m_game_in_progress(false)
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
            --m_credit;
            if (m_players == 1) {
                m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_HUNDREDS_CHIME);
                m_queue->put(QCOMMAND_SOLENOID, 0, SOLENOID_ID_DROP_TARGET_ALL);
                m_queue->put(QCOMMAND_ADD_CREDIT, 0, -1);
                m_queue->put(QCOMMAND_SET_SCORE, 0, 0);
                m_queue->put(QCOMMAND_SET_PLAYER, 0, 1);
                m_queue->put(QCOMMAND_SET_BALL, 0, 1);
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

void Game::next_player()
{
//    if (m_player_up == m_players) {
//        if (m_ball_in_play == MAX_BALLS) {
//            m_ball_in_play = 0;
//            m_player_up = 0;
//        } else {
//            m_player_up = 1;
//            ++m_ball_in_play;
//        }
//    } else {
//        ++m_player_up;
//    }
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
    m_game_in_progress = true;
    for (int i = 0; i < n; i++) {
        m_queue->put(QCOMMAND_SOLENOID, 0, solenoid_id);
        m_queue->put(QCOMMAND_ADD_SCORE, m_player_up, score);
        m_queue->put(QCOMMAND_DELAY, 0, SCORE_DELAY);
    }
}

void Game::rollover_rules()
{
    if (m_sensor->rising(SENSOR_ID_ROLLOVER_A)) {
        if (m_lamp->lit(LAMP_ID_TOP_ROLLOVER_A)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        }
        m_lamp->set(LAMP_ID_TOP_ROLLOVER_A, false);
        m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_A, false);
    }
    if (m_sensor->rising(SENSOR_ID_ROLLOVER_B)) {
        if (m_lamp->lit(LAMP_ID_TOP_ROLLOVER_B)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        }
        m_lamp->set(LAMP_ID_TOP_ROLLOVER_B, false);
        m_lamp->set(LAMP_ID_BOTTOM_LEFT_ROLLOVER_B, false);
        m_lamp->set(LAMP_ID_BOTTOM_RIGHT_ROLLOVER_B, false);
    }
    if (m_sensor->rising(SENSOR_ID_ROLLOVER_C)) {
        if (m_lamp->lit(LAMP_ID_TOP_ROLLOVER_C)) {
            multiscore(5, SOLENOID_ID_THOUSANDS_CHIME, 1000);
        } else {
            multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        }
        m_lamp->set(LAMP_ID_TOP_ROLLOVER_C, false);
        m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_C, false);
    }
    if (m_sensor->rising(SENSOR_ID_SPECIAL)) {
        multiscore(5, SOLENOID_ID_HUNDREDS_CHIME, 100);
        if (m_lamp->lit(LAMP_ID_SPECIAL)) {
//            m_scoreboard->add_credit();
            m_lamp->set(LAMP_ID_SPECIAL, false);
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

void Game::target_rules()
{
    if (m_sensor->rising(SENSOR_ID_DROP_10)) {
        target_score(LAMP_ID_TENS_BONUS);
        jacks_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_J1)) {
        target_score(LAMP_ID_JACKS_BONUS);
        jacks_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_J2)) {
        target_score(LAMP_ID_JACKS_BONUS);
        jacks_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_Q1)) {
        target_score(LAMP_ID_QUEENS_BONUS);
        queens_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_Q2)) {
        target_score(LAMP_ID_QUEENS_BONUS);
        queens_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_Q3)) {
        target_score(LAMP_ID_QUEENS_BONUS);
        queens_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K1)) {
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K2)) {
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K3)) {
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_K4)) {
        target_score(LAMP_ID_KINGS_BONUS);
        kings_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A1)) {
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A2)) {
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A3)) {
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_A4)) {
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
    if (m_sensor->rising(SENSOR_ID_DROP_JOKER)) {
        target_score(LAMP_ID_ACES_BONUS);
        aces_test();
    }
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


