//
// window_model.cpp
//

#include "window_model.h"
#include "frame_model.h"
#include "brick_shape.h"
#include "cube_shape.h"
#include "look.h"

WindowModel::WindowModel(float dimx, float dimy, float dimz, float dimb, int vgrills, int hgrills,
                         float animation_id,
                         bool no_left_side, bool no_right_side)
{
    float f_sill = dimz / 10.0;
    float f_head = dimz / 10.0;
    float f_jamb = dimz / 10.0;
    float f_rail = f_sill * 2.0;
    float f_stile = f_jamb * 2.0;
    float sill_offset = 0.75 * dimz / 2.0;
    float f_grille = f_jamb;

    FrameModel frame(dimx, dimy, dimz, dimb, f_sill, f_head, f_jamb, WINDOW_PAINT, animation_id, no_left_side, no_right_side);
    add(frame, 0.0, 0.0, 0.0);
    FrameModel sash(dimx, dimy, f_jamb, dimb, f_rail, f_rail, f_stile, WINDOW_PAINT, animation_id);
    add(sash, 0.0, 0.0, sill_offset);
    CubeShape pane(dimx - dimb, dimy - dimb, f_jamb / 2);
    CadModel pane_model(pane, PANE_PAINT, animation_id);
    add(pane_model, 0.0, 0.0, sill_offset);
    if (vgrills > 0) {
        BrickShape vs(f_grille, dimy, f_grille, dimb);
        CadModel vgrille(vs, WINDOW_PAINT, animation_id);
        float dx = dimx - 2.0 * f_stile;
        float space = (dx - f_grille * (float) vgrills) / (float) (vgrills + 1);
        for (int i = 0; i < vgrills; i++) {
            add(vgrille, -dx / 2.0 + (space + f_grille) * (float) (i + 1) - f_grille / 2.0, 0.0, sill_offset);
        }
    }
    if (hgrills > 0) {
        BrickShape hs(dimx, f_grille, f_grille, dimb);
        CadModel hgrille(hs, WINDOW_PAINT, animation_id);
        float dy = dimy - 2.0 * f_rail;
        float space = (dy - f_grille * (float) hgrills) / (float) (hgrills + 1);
        for (int i = 0; i < hgrills; i++) {
            add(hgrille, 0.0, -dy / 2.0 + (space + f_grille) * (float) (i + 1) - f_grille / 2.0, sill_offset);
        }
    }
}

WindowModel::~WindowModel()
{
}



