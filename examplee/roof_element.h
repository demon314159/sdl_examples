//
// roof_element.h
//

#ifndef _ROOF_ELEMENT_H_
#define _ROOF_ELEMENT_H_

#include "element.h"

class RoofElement: public Element
{
public:
    RoofElement(Int3 pos, int width, int orientation);
    RoofElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
    int faces() const override;
    Face face(int ix, bool* top_face = NULL) const override;
protected:
    CadModel m_model;
};

#endif // _ROOF_ELEMENT_H_
