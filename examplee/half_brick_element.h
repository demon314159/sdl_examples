//
// half_brick_element.h
//

#ifndef _HALF_BRICK_ELEMENT_H_
#define _HALF_BRICK_ELEMENT_H_

#include "element.h"

class HalfBrickElement: public Element
{
public:
    HalfBrickElement(Int3 pos);
    HalfBrickElement() = delete;
    void save_to_file(FILE* ffo) const override;
protected:
private:
};

#endif // _HALF_BRICK_ELEMENT_H_
