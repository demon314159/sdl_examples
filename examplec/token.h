//
// token.h
//

#ifndef _TOKEN_H_
#define _TOKEN_H_

#define MAX_TILES  6

#include "tile_rec.h"
#include "matrix4x4.h"
#include "float3.h"
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
    void advance(float seconds);
    CadModel model(float animation_id) const;
    const float* data();
    void set_position(float posx, float posy, float posz, float seconds = 0.0);
    void set_angle(float angle, float seconds = 0.0);
    Float3 current_position() const;
    float current_angle() const;

protected:
    Float3 m_position;
    float m_angle;
    Float3 m_velocity;
    float m_angular_velocity;
    float m_translation_time_left;
    float m_rotation_time_left;
    int m_tiles;
    TileRec m_tile[MAX_TILES];
    Matrix4x4 m_animation;

    void one_tile(CadModel& cm, int tile, float animation_id) const;
    bool occupied(int ph, int pv) const;
};

#endif // _TOKEN_H_
