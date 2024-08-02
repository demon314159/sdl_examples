//
// token_set.h
//

#ifndef _TOKEN_SET_H_
#define _TOKEN_SET_H_

#define MAX_TOKENS 40

#include "token.h"
#include "dock.h"

class TokenSet
{
public:
    TokenSet(void);
    ~TokenSet();
    int tokens() const;
    int tiles(int token_id) const;
    int posh(int token_id, int tix, int orientation) const;
    int posv(int token_id, int tix, int orientation) const;
    bool token_contained(int token_id, int orientation, int ph, int pv, int dimh, int dimv) const;
    bool token_collision(int token_id1, int orientation1, int ph1, int pv1, int token_id2, int orientation2, int ph2, int pv2) const;
    bool tile_at(int token_id, int orientation, int ph, int pv) const;
    float horz_center(int token_id, int orientation, float pitch) const;
    float vert_center(int token_id, int orientation, float pitch) const;
    void advance(float seconds);
    CadModel model(int token_id, float animation_id) const;
    const float* data(int token_id);
    void set_position(int token_id, float posx, float posy, float posz, float seconds = 0.0);
    void set_orientation(int token_id, int orientation, float seconds = 0.0);
    void set_dock_position(int token_id, int dock_id, const Dock* dock, float seconds = 0.0);
    void set_board_position(int token_id, int posh, int posv, int orientation, const Dock* dock, float seconds = 0.0);
    void set_angle_ax(int token_id, float angle, float seconds = 0.0);
    void set_angle_ay(int token_id, float angle, float seconds = 0.0);
    void set_angle_az(int token_id, float angle, float seconds = 0.0);
    Float3 position(int token_id) const;

protected:
    int m_tokens;
    Token m_token[MAX_TOKENS];

    void add_token(const Token& token);
};

#endif // _TOKEN_SET_H_
