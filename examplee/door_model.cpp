//
// door_model.cpp
//

#include "door_model.h"
#include "frame_model.h"
#include "brick_shape.h"
#include "cube_shape.h"
#include "look.h"
#include <cstddef>

DoorModel::DoorModel(float dimx, float dimy, float dimz, float dimb, int vgrills, int hgrills, float animation_id)
{
    float f_sill = dimz / 40.0;
    float f_head = dimz / 10.0;
    float f_jamb = dimz / 10.0;
    float f_thickness = f_jamb * 2;


    float f_mid = dimy * 0.7;
    float f_stile = f_jamb * 4.0;
    float sill_zoffset = 0.5 * dimz / 2.0;

    float upper_sash_dy = dimy - f_mid + f_stile - dimb;
    float lower_sash_dy = f_mid - dimb;

    FrameModel frame(dimx, dimy, dimz, dimb, f_sill, f_head, f_jamb, DOOR_PAINT, animation_id);
    add(frame, 0.0, 0.0, 0.0);
    FrameModel upper_sash(dimx - dimb, upper_sash_dy, f_thickness, dimb, f_stile, f_stile, f_stile, DOOR_PAINT, animation_id);
    add(upper_sash, 0.0, (dimy - upper_sash_dy) / 2 - dimb, sill_zoffset);
    FrameModel lower_sash(dimx - dimb, lower_sash_dy, f_thickness, dimb, f_stile, f_stile, f_stile, DOOR_PAINT, animation_id);
    add(lower_sash, 0.0, -(dimy - lower_sash_dy) / 2 + dimb, sill_zoffset);
    CubeShape pane(dimx - dimb, upper_sash_dy, f_jamb / 2);
    CadModel pane_model(pane, PANE_PAINT, animation_id);
    add(pane_model, 0.0, (dimy - upper_sash_dy) / 2 - dimb, sill_zoffset);
    CubeShape cube(dimx - dimb, f_mid, f_jamb);
    CadModel cube_model(cube, DOOR_PAINT, animation_id);
    add(cube_model, 0.0, -(dimy - f_mid) / 2, sill_zoffset);

    float f_upper_grille = 0.7 * f_jamb;
    float f_lower_grille = f_thickness;
    if (vgrills > 0) {
        BrickShape upper_vs(f_upper_grille, upper_sash_dy, f_upper_grille, dimb);
        BrickShape lower_vs(f_lower_grille, lower_sash_dy, f_lower_grille, dimb);
        CadModel upper_vgrille(upper_vs, DOOR_PAINT, animation_id);
        CadModel lower_vgrille(lower_vs, DOOR_PAINT, animation_id);

        float dx = dimx - 2.0 * f_stile;
        float upper_space = (dx - f_upper_grille * (float) vgrills) / (float) (vgrills + 1);
        float lower_space = (dx - f_lower_grille * (float) vgrills) / (float) (vgrills + 1);
        for (int i = 0; i < vgrills; i++) {
            add(upper_vgrille, -dx / 2.0 + (upper_space + f_upper_grille) * (float) (i + 1) - f_upper_grille / 2.0, (dimy - upper_sash_dy) / 2 - dimb, sill_zoffset);
            add(lower_vgrille, -dx / 2.0 + (lower_space + f_lower_grille) * (float) (i + 1) - f_lower_grille / 2.0, -(dimy - lower_sash_dy) / 2 + dimb, sill_zoffset);
        }
    }
    if (hgrills > 0) {
        BrickShape hs(dimx - dimb, f_upper_grille, f_upper_grille, dimb);
        CadModel hgrille(hs, DOOR_PAINT, animation_id);
        float dy = dimy -f_stile - f_mid;
        float space = (dy - f_upper_grille * (float) hgrills) / (float) (hgrills + 1);
        for (int i = 0; i < hgrills; i++) {
            add(hgrille, 0.0, (dimy - dy) / 2 - f_stile -dy / 2.0 + (space + f_upper_grille) * (float) (i + 1) - f_upper_grille / 2.0, sill_zoffset);
        }
    }
}

DoorModel::~DoorModel()
{
}



