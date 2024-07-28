//
// token.h
//
#ifndef _TOKEN_H_
#define _TOKEN_H_

#define MAX_TILES  6

#include "tile_rec.h"
#include "matrix4x4.h"

class Token
{
public:
    Token();
    ~Token();
    Token& add_tile(int posh, int posv);
    int tiles() const;
    int posh(int tix, int orientation) const;
    int posv(int tix, int orientation) const;
    const float* data();

protected:
    int m_tiles;
    TileRec m_tile[MAX_TILES];
    Matrix4x4 m_animation;
};

#endif // _TOKEN_H_
