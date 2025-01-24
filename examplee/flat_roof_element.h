//
// flat_roof_element.h
//

#ifndef _FLAT_ROOF_ELEMENT_H_
#define _FLAT_ROOF_ELEMENT_H_

#include "element.h"

class FlatRoofElement: public Element
{
public:
    FlatRoofElement(Int3 pos, int width, int orientation);
    FlatRoofElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
    int faces() const override;
    Face face(int ix, bool* top_face = NULL) const override;
protected:
    CadModel m_model;
    Face flat_roof_top_face(Int3 pos, int width, int orientation) const;
    Face flat_roof_bottom_face(Int3 pos, int width, int orientation) const;
};

#endif // _ELEMENT_H_
