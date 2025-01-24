//
// foundation_element.h
//

#ifndef _FOUNDATION_ELEMENT_H_
#define _FOUNDATION_ELEMENT_H_

#include "element.h"

class FoundationElement: public Element
{
public:
    FoundationElement(Int3 pos, int orientation);
    FoundationElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    static CadModel m_foundation_model_ns;
    static CadModel m_foundation_model_ew;
};

#endif // _FOUNDATION_ELEMENT_H_
