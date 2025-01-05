//
// toy.cpp
//

#include "toy.h"
#include "cube_shape.h"

#include <stdio.h>

Toy::Toy()
    : m_doc(new Document("first.brk"))
{
    printf("Doc Elements = %d\n", m_doc->elements());
    printf("Doc Facets = %d\n", m_doc->facets());
//    for (int i = 0; i < m_doc->elements(); i++) {
//        const Element* ep = m_doc->element(i);
//        const CadModel cm = *ep->model();
//        Float3 mpos = ep->model_pos();
//        m_model->add(cm, mpos.v1, mpos.v2, mpos.v3);
//    }

    build_model();
    BoundingBox bb = m_model->bounding_box();
    m_doc->building()->update_bounding_box(bb);
    m_camera->frame(bb);
}

Toy::~Toy()
{
    delete m_doc;
}

Document* Toy::get_doc() const
{
    return m_doc;
}

void Toy::build_model()
{
    m_model->clear();
    CadModel csx(CubeShape(0.2, 0.002, 0.002), PaintCan(0.0, 1.0, 1.0), 0.0);
    CadModel csy(CubeShape(0.002, 0.2, 0.002), PaintCan(0.0, 0.0, 1.0), 0.0);
    CadModel csz(CubeShape(0.002, 0.002, 0.2), PaintCan(0.0, 1.0, 0.0), 0.0);
    m_model->add(csx, 0.0, 0.0, 0.0);
    m_model->add(csy, 0.0, 0.0, 0.0);
    m_model->add(csz, 0.0, 0.0, 0.0);
}
