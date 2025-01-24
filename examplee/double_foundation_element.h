//
// double_foundation_element.h
//

#ifndef _DOUBLE_FOUNDATION_ELEMENT_H_
#define _DOUBLE_FOUNDATION_ELEMENT_H_

#include "element.h"

class DoubleFoundationElement: public Element
{
public:
    DoubleFoundationElement(Int3 pos, int orientation);
    DoubleFoundationElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    static CadModel m_double_foundation_model_ns;
    static CadModel m_double_foundation_model_ew;
};

#endif // _DOUBLE_FOUNDATION_ELEMENT_H_
