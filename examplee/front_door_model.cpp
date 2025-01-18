//
// front_door_model.cpp
//

#include "front_door_model.h"
#include "frame_model.h"
#include "brick_shape.h"
#include "cube_shape.h"
#include "look.h"
#include <cstddef>

FrontDoorModel::FrontDoorModel(float dimx, float dimy, float dimz, float dimb, int vgrills, int hgrills, float animation_id)
{
    float f_sill = dimz / 40.0;
    float f_head = dimz / 10.0;
    float f_jamb = dimz / 10.0;
    float f_thickness = f_jamb * 2;


    float f_mid = dimy * 0.7;
    float f_stile = f_jamb * 2.0;
    float sill_zoffset = 0.5 * dimz / 2.0;

    float sash_dy = dimy - 2.0 * dimb;

    FrameModel frame(dimx, dimy, dimz, dimb, f_sill, f_head, f_jamb, DOOR_PAINT, animation_id);
    add(frame, 0.0, 0.0, 0.0);

    FrameModel sash(dimx - dimb, sash_dy, f_thickness, dimb, f_stile, f_stile, f_stile, DOOR_PAINT, animation_id);
    add(sash, 0.0, (dimy - sash_dy) / 2 - dimb, sill_zoffset);

    CubeShape body(dimx - dimb, dimy - dimb, f_jamb  * 0.4);
    CadModel body_model(body, DOOR_PAINT, animation_id);
    add(body_model, 0.0, 0.0, sill_zoffset);

    float pane_w = (dimx - f_jamb * 2.0) / (vgrills + 1);
    float pane_h = (dimy - f_sill - f_head - f_thickness) / (hgrills + 1);
    CubeShape pane(pane_w, pane_h, f_jamb * 0.6);
    CadModel pane_model(pane, PANE_PAINT, animation_id);
    add(pane_model, 0.0, pane_h, sill_zoffset);


    float f_grille = f_jamb;
    if (vgrills > 0) {
        BrickShape vs(f_grille, sash_dy, f_grille, dimb);
        CadModel vgrille(vs, DOOR_PAINT, animation_id);

        float dx = dimx - 2.0 * f_stile;
        float space = (dx - f_grille * (float) vgrills) / (float) (vgrills + 1);
        for (int i = 0; i < vgrills; i++) {
           add(vgrille, -dx / 2.0 + (space + f_grille) * (float) (i + 1) - f_grille / 2.0, 0.0, sill_zoffset);
        }
    }
    if (hgrills > 0) {
        BrickShape hs(dimx - dimb, f_grille, f_grille, dimb);
        CadModel hgrille(hs, DOOR_PAINT, animation_id);
        float dy = dimy - 2.0 * f_stile;
        float space = (dy - f_grille * (float) hgrills) / (float) (hgrills + 1);
        for (int i = 0; i < hgrills; i++) {
            add(hgrille, 0.0, -dy / 2.0 + (space + f_grille) * (float) (i + 1) - f_grille / 2.0, sill_zoffset);
        }
    }
}

FrontDoorModel::~FrontDoorModel()
{
}



