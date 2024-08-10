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
    bool set_position(float posx, float posy, float posz, int orientation, float seconds = 0.0);
    Float3 position() const;

protected:
    Float3 m_position;
    Float3 m_angle;
    Float3 m_velocity;
    Float3 m_angular_velocity;
    float m_time_left;
    int m_tiles;
    TileRec m_tile[MAX_TILES];
    Matrix4x4 m_animation;

    void one_tile(CadModel& cm, int tile, float animation_id) const;
    bool occupied(int ph, int pv) const;
    Float3 angles(int orientation) const;
    Float3 velocity(const Float3& p1, const Float3& p0, float period) const;
    Float3 angular_velocity(const Float3& p1, const Float3& p0, float period) const;
    Float3 current_value(const Float3& p, const Float3& v, float tleft) const;
    float angle_diff(float a1, float a0) const;
};

#endif // _TOKEN_H_
