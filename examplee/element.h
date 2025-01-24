//
// element.h
//

#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "brick_shape.h"
#include "int3.h"
#include "float3.h"
#include "cad_model.h"
#include "bounding_box.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define UNIT_SQUARE 0.1f
#define DIMX  UNIT_SQUARE
#define DIMY  (UNIT_SQUARE * 2.0f / 3.0f)
#define DIMZ  UNIT_SQUARE
#define DIMB  (UNIT_SQUARE / 40.0f)
#define GABLE_ANGLE 33.69006753

class Element
{
public:
    Element(Int3 pos, int width, int height, int orientation);
    Element() = delete;
    virtual ~Element();
    void remove();
    void unremove();
    bool removed() const;
    Int3 pos() const;
    Float3 model_pos() const;
    int width() const;
    int height() const;
    int orientation() const;
    bool contains(int x, int y, int z) const;
    void update_integer_bounding_box(IntegerBoundingBox& bb);

    virtual void save_to_file(FILE* ffo) const = 0;
    virtual const CadModel* model() const;
    virtual bool corner_flag() const;
    virtual bool gable_flag() const;
    virtual int faces() const;
    virtual Face face(int ix, bool* top_face = NULL) const;
protected:
    bool m_removed;
    Int3 m_pos;
    int m_width;
    int m_height;
    int m_orientation;
    Face general_top_face(Int3 pos, int width, int height, int orientation) const;
    Face general_bottom_face(Int3 pos, int width, int height, int orientation) const;
    Face general_face(Int3 pos, int width, int height, int orientation, int ix, bool* top_face) const;
private:
    CadModel m_model;
    static CadModel m_half_brick_model;
    static CadModel m_brick_model_ns;
    static CadModel m_brick_model_ew;
    bool in_range(int v, int v1, int v2) const;
    bool partial_contains(Int3 pos, int width, int height, int orientation, int x, int y, int z) const;
};

#endif // _ELEMENT_H_
