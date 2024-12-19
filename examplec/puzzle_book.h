//
// puzzle_book.h
//
#ifndef _PUZZLE_BOOK_H_
#define _PUZZLE_BOOK_H_

#define MAX_CHALLENGES 48
#define PUZZLE_BOOK_FILE_NAME ".hexominos.dat"

#include "challenge.h"
#include "token_set.h"

class PuzzleBook
{
public:
    PuzzleBook(const char* name);
    ~PuzzleBook();
    void save(const char* name);
    bool puzzle_solved() const;
    bool current_challenge_solved() const;
    int challenges() const;
    int current_challenge() const;
    bool go_to_next_challenge();
    bool go_to_previous_challenge();
    int pieces() const;
    int token_id(int pix) const;
    bool locked(int pix) const;
    bool on_board(int pix) const;
    int orientation(int pix) const;
    int posh(int pix) const;
    int posv(int pix) const;
    bool drop_piece(const TokenSet* token_set, int pix, int orientation, int posh, int posv);
    bool lift_piece(int pix);
    int dimh() const;
    int dimv() const;
    void set_orientation(int pix, int orientation);

protected:
    int m_challenges;
    int m_current_challenge;
    Challenge m_challenge[MAX_CHALLENGES];

    void add_challenges();
    void add_challenge(const Challenge& challenge);
};

#endif // _PUZZLE_BOOK_H_
