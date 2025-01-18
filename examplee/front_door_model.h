//
// front_door_model.h
//

#ifndef _FRONT_DOOR_MODEL_H_
#define _FRONT_DOOR_MODEL_H_

#include "cad_model.h"

class FrontDoorModel: public CadModel
{
public:
    FrontDoorModel(float dimx, float dimy, float dimz, float dimb, int vgrilles, int hgrilles, float animation_id = 0.0);
    virtual ~FrontDoorModel();

private:
};

#endif // _FRONT_DOOR_MODEL_H_
