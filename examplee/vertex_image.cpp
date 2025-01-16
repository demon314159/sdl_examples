
#include "vertex_image.h"
#include "cad_model.h"
#include <math.h>

VertexImage::VertexImage(int max_vertex_count)
    : m_max_vertex_count(max_vertex_count)
    , m_vertex_count(0)
{
    m_vertex_data = new VertexData[m_max_vertex_count];
}

VertexImage::~VertexImage()
{
    delete [] m_vertex_data;
}

int VertexImage::vertex_count() const
{
    return m_vertex_count;
}

void VertexImage::trim_to(int vix)
{
    m_vertex_count = vix;
}

void VertexImage::add_element(Element* e, bool transparent)
{
    float an_id;
    Float3 vp;
    VertexData vd;
    if (e == NULL)
        return;
    Float3 pos = e->model_pos();
    const CadModel* model = e->model();
    for (int i = 0; i < model->facets(); i++) {
        an_id = model->facet_animation_id(i);
        if ((transparent && (an_id == 99.0)) || (!transparent && (an_id != 99.0))) {
            // Common
            vd.animation_id = an_id;
            vd.texture_id = model->facet_texture_id(i);
            vd.normal = model->facet_normal(i);
            vd.color = model->facet_color(i);
            // Vertex 1
            vp = model->facet_v1(i);
            vd.position = {vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3};
            vd.texture_position = model->facet_texture_v1(i);
            add_vertex(vd);
            // Vertex 2
            vp = model->facet_v2(i);
            vd.position = {vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3};
            vd.texture_position = model->facet_texture_v2(i);
            add_vertex(vd);
            // Vertex 3
            vp = model->facet_v3(i);
            vd.position = {vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3};
            vd.texture_position = model->facet_texture_v3(i);
            add_vertex(vd);
        }
    }
}

void VertexImage::add_vertex(const VertexData& vd)
{
    if (m_vertex_count >= m_max_vertex_count)
        double_the_storage();
    m_vertex_data[m_vertex_count] = vd;
    ++m_vertex_count;
}

void VertexImage::double_the_storage()
{
    // this will double the value of m_max_items
    // and copy existing data to new array
    // to seamlessly keep the buffer larger than data
    m_max_vertex_count = 2 * m_max_vertex_count;
    VertexData* temp = new VertexData[m_max_vertex_count];
    for (int i = 0; i < m_vertex_count; i++) {
        temp[i] = m_vertex_data[i];
    }
    delete [] m_vertex_data;
    m_vertex_data = temp;
}

void VertexImage::update_element(int start_ix, const Element* e, bool transparent)
{
    float dd = 0.04;
    float dx = dd * 10;
    float an_id;
    Float3 vp;
    VertexData vd;
    if (e == NULL)
        return;
    Float3 pos = e->model_pos();
    bool removed = e->removed();
    const CadModel* model = e->model();
    for (int i = 0; i < model->facets(); i++) {
        an_id = model->facet_animation_id(i);
        if ((transparent && (an_id == 99.0)) || (!transparent && (an_id != 99.0))) {

            vd.animation_id = removed ? 3.0 : an_id;
            vd.texture_id = removed ? 0.0 : model->facet_texture_id(i);
            vd.normal = model->facet_normal(i);
            vd.color = model->facet_color(i);

            if (removed) {
                vd.position = {dx, -dd, 0.0};
            } else {
                vp = model->facet_v1(i);
                vd.position = {vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3};
            }
            vd.texture_position = model->facet_texture_v1(i);
            m_vertex_data[start_ix++] = vd;

            if (removed) {
                vd.position = {dx - dd, -2 * dd, 0.0};
            } else {
                vp = model->facet_v2(i);
                vd.position = {vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3};
            }
            vd.texture_position = model->facet_texture_v2(i);
            m_vertex_data[start_ix++] = vd;

            if (removed) {
                vd.position = {dx + dd, -2 * dd, 0.0};
            } else {
                vp = model->facet_v3(i);
                vd.position = {vp.v1 + pos.v1, vp.v2 + pos.v2, vp.v3 + pos.v3};
            }
            vd.texture_position = model->facet_texture_v3(i);
            m_vertex_data[start_ix++] = vd;
        }
    }
}

const VertexData* VertexImage::vertex_data() const
{
    return m_vertex_data;
}

BoundingBox VertexImage::bounding_box() const
{
    BoundingBox bb;
    if (m_vertex_count == 0) {
        bb.vmin.v1 = -DIMX / 2.0;
        bb.vmin.v2 = -DIMY / 2.0;
        bb.vmin.v3 = -DIMZ / 2.0;
        bb.vmax.v1 = DIMX / 2.0;
        bb.vmax.v2 = DIMY / 2.0;
        bb.vmax.v3 = DIMZ / 2.0;
        return bb;
    }
    bb.vmin = m_vertex_data[0].position;
    bb.vmax = m_vertex_data[0].position;
    update_bounding_box(bb);
    return bb;
}

bool VertexImage::vertex_regular(int ix) const
{
    float id = m_vertex_data[ix].animation_id;
    if (id > 1.5 && id < 13.5)
        return false;
    return id < 98.5;
}

void VertexImage::update_bounding_box(BoundingBox& bb) const
{
    for (int i = 0; i < m_vertex_count; i++) {
        if (vertex_regular(i)) {
            Float3 v = m_vertex_data[i].position;
            bb.vmin.v1 = fmin(bb.vmin.v1, v.v1);
            bb.vmin.v2 = fmin(bb.vmin.v2, v.v2);
            bb.vmin.v3 = fmin(bb.vmin.v3, v.v3);
            bb.vmax.v1 = fmax(bb.vmax.v1, v.v1);
            bb.vmax.v2 = fmax(bb.vmax.v2, v.v2);
            bb.vmax.v3 = fmax(bb.vmax.v3, v.v3);
        }
    }
}

