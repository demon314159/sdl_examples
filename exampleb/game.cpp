//
// game.cpp
//

#include "game.h"

#define SCORE_DELAY 150 // milliseconds

Game::Game(int credit, int max_players, int max_balls, Lamp* lamp, Queue* queue)
    : m_credit(credit)
    , m_max_players(max_players)
    , m_max_balls(max_balls)
    , m_lamp(lamp)
    , m_queue(queue)
    , m_players(0)
    , m_player_up(0)
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
    if (m_credit > 0) {
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

