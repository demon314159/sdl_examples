//
// tray.h
//

#ifndef _TRAY_H_
#define _TRAY_H_

#include "cad_model.h"
#include "paint_can.h"

#define TRAY_BORDER_COLOR PaintCan(0.75, 0.1875, 0.1875)
#define TRAY_BODY_COLOR PaintCan(1.0, 0.25, 0.25)

class Tray
{
public:
    Tray(int rows, int cols);
    ~Tray();
    int rows() const;
    int cols() const;
    CadModel model(float animation_id) const;

protected:
    int m_rows;
    int m_cols;

    void one_square(CadModel& cm, int row, int col, float animation_id) const;
};

#endif // _TRAY_H_
