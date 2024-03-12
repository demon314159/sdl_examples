//
// cad_model.h
//

#ifndef _CAD_MODEL_H_
#define _CAD_MODEL_H_

#include "float3.h"
#include "facet.h"
#include "bounding_box.h"
#include "int3.h"
#include "stl_file.h"
#include "paint_can.h"
#include "shape.h"
#include "face.h"

class CadModel
{
public:
    CadModel();
    CadModel(const CadModel& cad_model, float x = 0.0, float y = 0.0, float z = 0.0);
    CadModel(const StlFile& stl_file, const PaintCan& paint_can, float animation_id = 0.0);
    CadModel(const Shape& s, const PaintCan& paint_can, float animation_id = 0.0);
    CadModel(const Shape& s);
    ~CadModel();
    void add(const StlFile& stl_File, const PaintCan& paint_can, float animation_id = 0.0);
    void add(const Shape& s, const PaintCan& paint_can, float animation_id = 0.0);
    void add(const CadModel& cad_model, float x = 0.0, float y = 0.0, float z = 0.0);
    void rotate_ax(float angle);
    void rotate_ay(float angle);
    void rotate_az(float angle);
    void translate(float x, float y, float z);
    void magnify(float factor);
    int facets() const;
    Facet facet(int ix) const;
    float facet_animation_id(int facet_ix) const;
    Float3 facet_v1(int facet_ix) const;
    Float3 facet_v2(int facet_ix) const;
    Float3 facet_v3(int facet_ix) const;
    Float3 facet_color(int facet_ix) const;
    Float3 facet_normal(int facet_ix) const;
    float facet_texture_id(int facet_ix) const;
    Float2 facet_texture_v1(int facet_ix) const;
    Float2 facet_texture_v2(int facet_ix) const;
    Float2 facet_texture_v3(int facet_ix) const;
    BoundingBox bounding_box() const;

private:
    int m_facet_count;
    Facet* m_facet;
    Float3 translate(const Float3& v, const Float3& offset) const;
    Facet translate(const Facet& f, const Float3& offset) const;
    void filter_roof(float& v) const;
};

#endif // _CAD_MODEL_H_
