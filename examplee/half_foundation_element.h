//
// half_foundation_element.h
//

#ifndef _HALF_FOUNDATION_ELEMENT_H_
#define _HALF_FOUNDATION_ELEMENT_H_

#include "element.h"

class HalfFoundationElement: public Element
{
public:
    HalfFoundationElement(Int3 pos);
    HalfFoundationElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    static CadModel m_half_foundation_model;
};

#endif // _HALF_FOUNDATION_ELEMENT_H_
