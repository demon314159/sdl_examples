//
// back_door_element.h
//

#ifndef _BACK_DOOR_ELEMENT_H_
#define _BACK_DOOR_ELEMENT_H_

#include "element.h"

class BackDoorElement: public Element
{
public:
    BackDoorElement(Int3 pos, int orientation);
    BackDoorElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    CadModel m_model;
};

#endif // _BACK_DOOR_ELEMENT_H_
