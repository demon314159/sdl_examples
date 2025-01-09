//
// document.h
//
#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include "element.h"
#include "token_file.h"
#include "vertex_image.h"

// one_change means that one element has changed and only a small patch will be made to the vertex data
// many_changes means that more than one element has changed and the vertex data will be rebuilt entirely
//
// Most user edit operations only cause one change and the image can be maintained with no lag
//     add_element:  one_change
//     remove_element: one_change
//     unremove_element: one_change
//     new: many_changes
//     load: many_changes
//     save: neither because document remains unchanged

class Element;

class Document
{
public:
    Document(int max_elements = 16384);
    Document(const char* file_name, int max_elements = 16384);
    ~Document();
    int elements() const;
    int facets() const;
    const Element* element(int ix) const;
    void add_element(Element* e);
    void remove_element(int ix);
    Element* remove_last_element();
    void unremove_element(int ix);
    bool load(const char* file_name, char* error_message);
    bool save(const char* file_name, char* error_message) const;
    bool just_one_change() const; // one and only one change
    int changed_ix() const;       // index of the one element that changed
    bool many_changes() const;    // more than one change
    void clear_changes();
    void note_one_change(int ix);
    void note_many_changes();
    const VertexImage* building() const;
    const VertexImage* glass() const;
    int building_index(int ix) const;
    int glass_index(int ix) const;
    bool occupied(int x, int y, int z) const;
    bool occupied(const Element* e) const;

private:
    bool m_one_change;
    bool m_many_changes;
    int m_changed_ix;

    int m_max_elements;
    int m_elements;
    Element** m_element_ptr;
    int* m_building_index;
    int* m_glass_index;
    VertexImage* m_building;
    VertexImage* m_glass;

    void double_the_storage();
    bool expect(TokenFile& tf, const char* pattern, char* error_message);
    bool parse_integer3(TokenFile& tf, int& x, int& y, int& z, char* error_message);
    bool parse_integer(TokenFile& tf, int &v, char* error_message);
};

#endif // _DOCUMENT_H_
