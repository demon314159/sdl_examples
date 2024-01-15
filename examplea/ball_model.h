//
// ball_model.h
//

#if !defined(_BALL_MODEL_H_)
#define _BALL_MODEL_H_

#include "cad_model.h"

class BallModel: public CadModel
{
public:
    BallModel(float animation_id,
              const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color,
              float radius);
    ~BallModel();

private:
};

#endif // _BALL_MODEL_H_
