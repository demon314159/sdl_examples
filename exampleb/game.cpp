//
// game.cpp
//

#include "game.h"

#define MAX_PLAYERS 4
#define MAX_BALLS 5

Game::Game(int credits)
    : m_ball_in_play(0)
    , m_player_up(0)
    , m_players(0)
    , m_credits(credits)
{
}

Game::~Game()
{
}

int Game::ball_in_play() const
{
    return m_ball_in_play;
}

int Game::player_up() const
{
    return m_player_up;
}

int Game::players() const
{
    return m_players;
}

int Game::credits() const
{
    return m_credits;
}

void Game::add_credit()
{
    ++m_credits;
}

void Game::add_player()
{
    if (m_credits > 0) {
        if (m_players < MAX_PLAYERS) {
            ++m_players;
            m_player_up = 1;
            --m_credits;
        }
    }
}

void Game::next_player()
{
    if (m_player_up == m_players) {
        if (m_ball_in_play == MAX_BALLS) {
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

