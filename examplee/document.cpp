//
// document.cpp
//

#include "document.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

Document::Document(int max_elements)
    : m_one_change(false)
    , m_many_changes(true)
    , m_changed_ix(0)
    , m_max_elements(max_elements)
    , m_elements(0)
    , m_building(new VertexImage(1024 * 1024))
    , m_glass(new VertexImage(128 * 1024))
{
    m_element_ptr = new Element*[m_max_elements];
    m_building_index = new int[m_max_elements];
    m_glass_index = new int[m_max_elements];
}

Document::Document(const char* file_name, int max_elements)
    : m_one_change(false)
    , m_many_changes(true)
    , m_changed_ix(0)
    , m_max_elements(max_elements)
    , m_elements(0)
    , m_building(new VertexImage())
    , m_glass(new VertexImage())
{
    char error_message[MAX_TOKEN_CHARS + 1];
    m_element_ptr = new Element*[m_max_elements];
    m_building_index = new int[m_max_elements];
    m_glass_index = new int[m_max_elements];
    if (!load(file_name, error_message)) {
        printf("Document::Document(%s, %d) Error:\n", file_name, max_elements);
        printf("    '%s'\n", error_message);
    }
}

Document::~Document()
{
    for (int i = 0; i < m_elements; i++) {
        delete m_element_ptr[i];
    }
    delete [] m_glass_index;
    delete [] m_building_index;
    delete [] m_element_ptr;
    delete m_glass;
    delete m_building;
}

int Document::elements() const
{
    return m_elements;
}

int Document::facets() const
{
    int total = 0;
    for (int i = 0; i < m_elements; i++) {
        Element* e = m_element_ptr[i];
        if (!e->removed()) {
            total += e->model()->facets();
        }
    }
    return total;
}

const Element* Document::element(int ix) const
{
    if (m_elements == 0)
        return NULL;
    int index = std::min(ix, m_elements - 1);
    return m_element_ptr[index];
}

void Document::add_element(Element* e)
{
    if (e == NULL)
        return;
    if (m_elements >= m_max_elements) {
        double_the_storage();
    }
    m_element_ptr[m_elements] = e;
    m_building_index[m_elements] = m_building->vertex_count();
    m_glass_index[m_elements] = m_glass->vertex_count();
    if (m_elements == 0)
        m_many_changes = true;

    m_building->add_element(e, false);
    m_glass->add_element(e, true);

    note_one_change(m_elements);
    ++m_elements;
}

void Document::remove_element(int ix)
{
    if (m_elements == 0)
        return;
    int index = std::min(ix, m_elements - 1);
    m_element_ptr[index]->remove();
    m_building->update_element(m_building_index[index], m_element_ptr[index], false);
    m_glass->update_element(m_glass_index[index], m_element_ptr[index], true);
    note_one_change(ix);
}

Element* Document::remove_last_element()
{
    if (m_elements == 0)
        return NULL;
    int index = m_elements - 1;
    Element* e = m_element_ptr[index];
    --m_elements;
    note_one_change(index);
    m_building->trim_to(m_building_index[index]);
    m_glass->trim_to(m_glass_index[index]);
    return e;
}

void Document::unremove_element(int ix)
{
    if (m_elements == 0)
        return;
    int index = std::min(ix, m_elements - 1);
    m_element_ptr[index]->unremove();
    m_building->update_element(m_building_index[index], m_element_ptr[index], false);
    m_glass->update_element(m_glass_index[index], m_element_ptr[index], true);
    note_one_change(ix);
}

// This adds to document, only used with new document so far
bool Document::load(const char* file_name, char* error_message)
{
    TokenFile tf(file_name);
    tf.advance();
    if (!expect(tf, "Bricks", error_message))
        return false;
    if (!expect(tf, "Document", error_message))
        return false;
    if (!expect(tf, "v1", error_message))
        return false;
    if (!expect(tf, ".", error_message))
        return false;
    if (!expect(tf, "0", error_message))
        return false;
    if (!expect(tf, ".", error_message))
        return false;
    if (!expect(tf, "0", error_message))
        return false;
    while (!tf.is_eof()) {
        char ename[MAX_TOKEN_CHARS + 1];
        strcpy(ename, tf.current());
        tf.advance();
        if (0 == strcmp(ename, "HalfBrick")) {
            int x, y, z;
            if (!expect(tf, "(", error_message))
                return false;
            if (!parse_integer3(tf, x, y, z, error_message))
                return false;
            if (!expect(tf, ")", error_message))
                return false;
            add_element(new Element({x, y, z}, 1, 1, 0));
        } else if (0 == strcmp(ename, "Brick")) {
            int x, y, z;
            int o;
            if (!expect(tf, "(", error_message))
                return false;
            if (!parse_integer3(tf, x, y, z, error_message))
                return false;
            if (!expect(tf, ",", error_message))
                return false;
            if (!parse_integer(tf, o, error_message))
                return false;
            if (!expect(tf, ")", error_message))
                return false;
            add_element(new Element({x, y, z}, 2, 1, o));
        } else {
            sprintf(error_message, "Expecting 'HalfBrick' or 'Brick' but found '%s'", ename);
            return false;
        }
    }
    return true;
}

bool Document::save(const char* file_name, char* error_message) const
{
    FILE* ffo = fopen(file_name, "w");
    if (ffo == NULL) {
        sprintf(error_message, "Error opening file '%s'", file_name);
        return false;
    }
    fprintf(ffo, "Bricks Document v1.0.0\n");
    for (int i = 0; i < m_elements; i++) {
        if (!m_element_ptr[i]->removed()) {
            m_element_ptr[i]->save_to_file(ffo);
        }
    }
    fclose(ffo);
    return true;
}

void Document::double_the_storage()
{
    // this will double the value of m_max_items
    // and copy existing data to new array
    // to seamlessly keep the buffer larger than data
    m_max_elements = 2 * m_max_elements;
    Element** temp_element_ptr = new Element*[m_max_elements];
    int* temp_building_index = new int[m_max_elements];
    int* temp_glass_index = new int[m_max_elements];

    for (int i = 0; i < m_elements; i++) {
        temp_element_ptr[i] = m_element_ptr[i];
        temp_building_index[i] = m_building_index[i];
        temp_glass_index[i] = m_glass_index[i];
    }
    delete [] m_element_ptr;
    delete [] m_building_index;
    delete [] m_glass_index;
    m_element_ptr = temp_element_ptr;
    m_building_index = temp_building_index;
    m_glass_index = temp_glass_index;
}

bool Document::expect(TokenFile& tf, const char* pattern, char* error_message)
{
    if (0 == strcmp(tf.current(), pattern)) {
        tf.advance();
        return true;
    }
    sprintf(error_message, "Expecting '%s' but found '%s'", pattern, tf.current());
    return false;
}

bool Document::parse_integer3(TokenFile& tf, int& x, int& y, int& z, char* error_message)
{
    if (!parse_integer(tf, x, error_message))
        return false;
    if (!expect(tf, ",", error_message))
        return false;
    if (!parse_integer(tf, y, error_message))
        return false;
    if (!expect(tf, ",", error_message))
        return false;
    return parse_integer(tf, z, error_message);
}

bool Document::parse_integer(TokenFile& tf, int &v, char* error_message)
{
    bool neg_flag = false;
    char s[MAX_TOKEN_CHARS + 1];
    s[0] = 0;

    if (0 == strcmp(tf.current(), "+") || 0 == strcmp(tf.current(), "-")) {
        neg_flag = 0 == strcmp(tf.current(), "-");
        tf.advance();
    }
    if (!tf.is_unsigned_integer()) {
        sprintf(error_message, "expecting integer but found '%s'", tf.current());
        return false;
    }
    strcat(s, tf.current());
    tf.advance();
    if (neg_flag) {
        v = -atoi(s);
    } else {
        v = atoi(s);
    }
    return true;
}

void Document::note_one_change(int ix)
{
    if (m_one_change && (ix != m_elements)) {
        m_many_changes = true;
    } else {
        m_one_change = true;
        m_changed_ix = ix;
    }
}

void Document::note_many_changes()
{
    m_many_changes = true;
}

bool Document::just_one_change() const
{
    return m_one_change && !m_many_changes;
}

bool Document::many_changes() const
{
    return m_many_changes;
}

void Document::clear_changes()
{
    m_one_change = false;
    m_many_changes= false;
    m_changed_ix = 0;
}

const VertexImage* Document::building() const
{
    return m_building;
}

const VertexImage* Document::glass() const
{
    return m_glass;
}

int Document::changed_ix() const
{
    return m_changed_ix;
}

int Document::building_index(int ix) const
{
    if (m_elements < 1)
        return 0;
    if (ix >= (m_elements))
        return m_building->vertex_count();
    return m_building_index[ix];
}

int Document::glass_index(int ix) const
{
    if (m_elements < 1)
        return 0;
    if (ix >= (m_elements))
        return m_glass->vertex_count();
    return m_glass_index[ix];
}

