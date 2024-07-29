//
// token.h
//

#ifndef _TOKEN_H_
#define _TOKEN_H_

#define MAX_TILES  6

#include "tile_rec.h"
#include "matrix4x4.h"
#include "cad_model.h"

class Token
{
public:
    Token();
    ~Token();
    Token& add_tile(int posh, int posv);
    int tiles() const;
    int posh(int tix, int orientation) const;
    int posv(int tix, int orientation) const;
    CadModel model(float animation_id) const;
    const float* data();
    void set_position(float posx, float posy, float posz);

protected:
    float m_posx;
    float m_posy;
    float m_posz;
    int m_tiles;
    TileRec m_tile[MAX_TILES];
    Matrix4x4 m_animation;

    void one_tile(CadModel& cm, int tile, float animation_id) const;
    bool occupied(int ph, int pv) const;
};

#endif // _TOKEN_H_
