
#ifndef _VERTEX_IMAGE_H_
#define _VERTEX_IMAGE_H_

#include "element.h"
#include "vertex_data.h"
#include "bounding_box.h"

class VertexImage
{
public:
    VertexImage(int max_vertex_count = 1024 * 1024);
    ~VertexImage();
    int vertex_count() const;
    void add_element(Element* e, bool transparent);
    void update_element(int start_ix, const Element* e, bool transparent);
    const VertexData* vertex_data() const;
    void trim_to(int vix);
    BoundingBox bounding_box() const;
    void update_bounding_box(BoundingBox& bb) const;

private:
    int m_max_vertex_count;
    int m_vertex_count;
    VertexData* m_vertex_data;

    void double_the_storage();
    void add_vertex(const VertexData& vd);
};

#endif // _VERTEX_IMAGE_H_
