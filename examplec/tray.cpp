//
// tray.cpp
//

#include "tray.h"
#include "paint_can.h"
#include "cube_shape.h"
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
    float pitch = 0.010;
    float width = 0.0095;
    float height = 0.001;
    float thick = 0.0005;
    PaintCan red(1.0, 0.0, 0.0);
    PaintCan black(0.0, 0.0, 0.0);

    CadModel s1(CubeShape(width, height, width), red, animation_id);
    CadModel s2(TrayBorderShape(pitch, width, height, row == 0, row == (m_rows - 1), col == 0, col == (m_cols - 1)), black, animation_id);


    cm.add(s1, pitch * (float) col, 0.0, pitch * (float) row);
    cm.add(s2, pitch * (float) col, 0.0, pitch * (float) row);
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

