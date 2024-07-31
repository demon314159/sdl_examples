//
// tray.h
//

#ifndef _TRAY_H_
#define _TRAY_H_

#include "cad_model.h"

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
