//
// game.h
//

#ifndef _GAME_H_
#define _GAME_H_

class Game
{
public:
    Game(int credit);
    ~Game();

    int ball_in_play() const;
    int player_up() const;
    int players() const;
    int credits() const;

    void add_credit();
    void add_player();
    void next_player();

private:
    int m_ball_in_play;
    int m_player_up;
    int m_players;
    int m_credits;
};

#endif // _GAME_H_
