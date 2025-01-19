//
// choose.h
//

#ifndef _CHOOSE_H_
#define _CHOOSE_H_

#include "cad_model.h"
#include "matrix4x4.h"

class Choose
{
public:
    Choose(float dimx, float dimy, float dimz, const PaintCan& marker_color);
    ~Choose();
    void select_no_choice();
    void select_choice(Int3 c, bool gable_flag, int gable_orientation);
    CadModel model(float animation_id) const;
    const float* data();
    bool new_element_chosen(Int3& pos, int& width, int& orientation) const;
    bool valid_roof_selection() const;
    void adjust_roof_orientation(Int3& p, int& o);

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    PaintCan m_color;
    bool m_first_selected;
    bool m_first_gable_flag;
    int m_first_gable_orientation;
    bool m_second_selected;
    bool m_second_gable_flag;
    int m_second_gable_orientation;
    Int3 m_first_choice;
    Int3 m_second_choice;
    Matrix4x4 m_animation;
};

#endif // _CHOOSE_H_
