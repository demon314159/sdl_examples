//
// gable_brick_element.h
//

#ifndef _GABLE_BRICK_ELEMENT_H_
#define _GABLE_BRICK_ELEMENT_H_

#include "element.h"

class GableBrickElement: public Element
{
public:
    GableBrickElement(Int3 pos, int orientation);
    GableBrickElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
    bool gable_flag() const override;
    int faces() const;
    Face face(int ix, bool* top_face = NULL) const;
protected:
private:
    CadModel m_model;
};

#endif // _GABLE_BRICK_ELEMENT_H_
