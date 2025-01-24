//
// front_door_element.h
//

#ifndef _FRONT_DOOR_ELEMENT_H_
#define _FRONT_DOOR_ELEMENT_H_

#include "element.h"

class FrontDoorElement: public Element
{
public:
    FrontDoorElement(Int3 pos, int orientation);
    FrontDoorElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    CadModel m_model;
};

#endif // _FRONT_DOOR_ELEMENT_H_
