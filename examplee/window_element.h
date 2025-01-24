//
// window_element.h
//

#ifndef _WINDOW_ELEMENT_H_
#define _WINDOW_ELEMENT_H_

#include "element.h"

class WindowElement: public Element
{
public:
    WindowElement(Int3 pos, int orientation);
    WindowElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    CadModel m_model;
};

#endif // _WINDOW_ELEMENT_H_
