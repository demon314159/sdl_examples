//
// brick_element.h
//

#ifndef _BRICK_ELEMENT_H_
#define _BRICK_ELEMENT_H_

#include "element.h"

class BrickElement: public Element
{
public:
    BrickElement(Int3 pos, int orientation);
    BrickElement() = delete;
    void save_to_file(FILE* ffo) const override;
protected:
private:
};

#endif // _BRICK_ELEMENT_H_
