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

#define NORTH 0
#define WEST  1
#define SOUTH 2
#define EAST  3

#define BOTTOM_FACE 0
#define TOP_FACE    1
#define LEFT_FACE   2
#define RIGHT_FACE  3
#define FRONT_FACE  4
#define BACK_FACE   5

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
    virtual bool roof_flag() const;
    virtual int faces() const;
    virtual Face face(int ix, bool* top_face = NULL) const;
protected:
    bool m_removed;
    Int3 m_pos;
    int m_width;
    int m_height;
    int m_orientation;
    Face general_face(Int3 pos, int width, int height, int orientation, int ix, bool* top_face) const;
private:
    CadModel m_model;
    static CadModel m_half_brick_model;
    static CadModel m_brick_model_ns;
    static CadModel m_brick_model_ew;
    bool in_range(int v, int v1, int v2) const;
    bool partial_contains(Int3 pos, int width, int height, int orientation, int x, int y, int z) const;
};

class GableBrickElement: public Element
{
public:
    GableBrickElement(Int3 pos, int orientation);
    GableBrickElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
    bool gable_flag() const override;
protected:
private:
    CadModel m_model;
};

class HalfBrickElement: public Element
{
public:
    HalfBrickElement(Int3 pos);
    HalfBrickElement() = delete;
    void save_to_file(FILE* ffo) const override;
protected:
private:
};

class BrickElement: public Element
{
public:
    BrickElement(Int3 pos, int orientation);
    BrickElement() = delete;
    void save_to_file(FILE* ffo) const override;
protected:
private:
};

class HalfFoundationElement: public Element
{
public:
    HalfFoundationElement(Int3 pos);
    HalfFoundationElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    static CadModel m_half_foundation_model;
};

class FoundationElement: public Element
{
public:
    FoundationElement(Int3 pos, int orientation);
    FoundationElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    static CadModel m_foundation_model_ns;
    static CadModel m_foundation_model_ew;
};

class DoubleFoundationElement: public Element
{
public:
    DoubleFoundationElement(Int3 pos, int orientation);
    DoubleFoundationElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    static CadModel m_double_foundation_model_ns;
    static CadModel m_double_foundation_model_ew;
};

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

class RoofElement: public Element
{
public:
    RoofElement(Int3 pos, int width, int orientation);
    RoofElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
    bool roof_flag() const override;
protected:
    CadModel m_model;
};

class FlatRoofElement: public Element
{
public:
    FlatRoofElement(Int3 pos, int width, int orientation);
    FlatRoofElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
    CadModel m_model;
};

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

class FrontDoorElement: public Element
{
public:
    FrontDoorElement(Int3 pos, int orientation);
    FrontDoorElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    CadModel m_model;
};

class BackDoorElement: public Element
{
public:
    BackDoorElement(Int3 pos, int orientation);
    BackDoorElement() = delete;
    void save_to_file(FILE* ffo) const override;
    const CadModel* model() const override;
protected:
private:
    CadModel m_model;
};

#endif // _ELEMENT_H_
