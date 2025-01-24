//
// corner_window_element.h
//

#ifndef _CORNER_WINDOW_ELEMENT_H_
#define _CORNER_WINDOW_ELEMENT_H_

#include "element.h"

class CornerWindowElement: public Element
{
public:
    CornerWindowElement(Int3 pos, int orientation);
    CornerWindowElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
    bool corner_flag() const override;
    int faces() const override;
    Face face(int ix, bool* top_face = NULL) const override;
protected:
private:
    CadModel m_model;
};

#endif // _CORNER_WINDOW_ELEMENT_H_
