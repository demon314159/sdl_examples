//
// token.h
//
#ifndef _TOKEN_H_
#define _TOKEN_H_

#define MAX_TILES  6

#include "tile_rec.h"

class Token
{
public:
    Token();
    ~Token();
    Token& add_tile(int posh, int posv);
    int tiles() const;
    int posh(int tix, int orientation) const;
    int posv(int tix, int orientation) const;

protected:
    int m_tiles;
    TileRec m_tile[MAX_TILES];
};

#endif // _TOKEN_H_
