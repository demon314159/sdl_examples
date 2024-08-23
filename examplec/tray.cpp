//
// tray.cpp
//

#include "tray.h"
#include "token.h"
#include "plane_shape.h"
#include "tray_border_shape.h"

Tray::Tray(int rows, int cols)
    : m_rows(rows)
    , m_cols(cols)
{
}

Tray::~Tray()
{
}

int Tray::rows() const
{
    return m_rows;
}

int Tray::cols() const
{
    return m_cols;
}

void Tray::one_square(CadModel& cm, int row, int col, float animation_id) const
{
    float pitch = TILE_PITCH;
    float width = TILE_WIDTH;
    float height = TILE_HEIGHT;
    float thick = TILE_THICK;

    CadModel s1(PlaneShape(width, width), TRAY_BODY_COLOR, animation_id);
    CadModel s2(TrayBorderShape(pitch, width, height, row == (m_rows - 1), row == 0.0, col == 0, col == (m_cols - 1)), TRAY_BORDER_COLOR, animation_id);
    cm.add(s1, pitch * (float) col, height / 2.0, -pitch * (float) row);
    cm.add(s2, pitch * (float) col, 0.0, -pitch * (float) row);
    s1.rotate_ax(180.0);
    cm.add(s1, pitch * (float) col, -height / 2.0, -pitch * (float) row);
}

CadModel Tray::model(float animation_id) const
{
    CadModel cm;

    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            one_square(cm, r, c, animation_id);
        }
    }
    return cm;
}

