//
// triple_foundation_element.h
//

#ifndef _TRIPLE_FOUNDATION_ELEMENT_H_
#define _TRIPLE_FOUNDATION_ELEMENT_H_

#include "element.h"

class TripleFoundationElement: public Element
{
public:
    TripleFoundationElement(Int3 pos, int orientation);
    TripleFoundationElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    static CadModel m_triple_foundation_model_ns;
    static CadModel m_triple_foundation_model_ew;
};

#endif // _TRIPLE_FOUNDATION_ELEMENT_H_
