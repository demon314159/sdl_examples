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
#include "paint_can.h"

#define TILE_PITCH 0.010f
#define TILE_WIDTH 0.0090f
#define TILE_HEIGHT 0.001f
#define TILE_THICK 0.0005f
#define TILE_BORDER 0.001f

#define TILE_BORDER_COLOR PaintCan(1.0, 1.0, 0.0)
#define TILE_BODY_COLOR PaintCan(0.8, 0.8, 0.0)

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
    bool set_position(float posx, float posy, float posz, int orientation, float seconds = 0.0, float transit_height = 0.0);
    Float3 position() const;

protected:
    Float3 m_position;
    Float2 m_angle;
    Float3 m_velocity;
    Float2 m_angular_velocity;
    float m_time_left;
    float m_transit_height;
    int m_tiles;
    TileRec m_tile[MAX_TILES];
    Matrix4x4 m_animation;

    void one_tile(CadModel& cm, int tile, float animation_id) const;
    bool occupied(int ph, int pv) const;
    Float2 angles(int orientation) const;
    Float3 velocity(const Float3& p1, const Float3& p0, float period) const;
    Float2 angular_velocity(const Float2& p1, const Float2& p0, float period) const;
    Float3 current_position(const Float3& p, const Float3& v, float tleft) const;
    Float2 current_angle(const Float2& p, const Float2& v, float tleft) const;
    float angle_diff(float a1, float a0) const;
};

#endif // _TOKEN_H_
