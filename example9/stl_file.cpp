//
// stl_file.cpp
//
#include <stdio.h>
#include "stl_file.h"

#define notVERBOSE

StlFile::StlFile(const char* file_name)
    : m_file_is_valid(false)
    , m_bf(file_name)
    , m_error_message("no errors")
    , m_facet_count(0)
    , m_v1(nullptr)
    , m_v2(nullptr)
    , m_v3(nullptr)
{
#ifdef VERBOSE
    printf("StlFile(%s)\n", file_name);
#endif
    parse();
#ifdef VERBOSE
    printf("%d facets\n", m_facet_count);
#endif
}

StlFile::~StlFile()
{
#ifdef VERBOSE
    printf("~StlFile()\n");
#endif
    if (m_v1 != nullptr)
        delete [] m_v1;
    if (m_v2 != nullptr)
        delete [] m_v2;
    if (m_v3 != nullptr)
        delete [] m_v3;
}

int StlFile::facets() const
{
    return m_facet_count;
}

Float3 StlFile::facet_v1(int facet_ix) const
{
    if (facet_ix < m_facet_count) {
        return m_v1[facet_ix];
    } else {
        Float3 v = {0.0, 0.0, 0.0};
        return v;
    }
}

Float3 StlFile::facet_v2(int facet_ix) const
{
    if (facet_ix < m_facet_count) {
        return m_v2[facet_ix];
    } else {
        Float3 v = {0.0, 0.0, 0.0};
        return v;
    }
}

Float3 StlFile::facet_v3(int facet_ix) const
{
    if (facet_ix < m_facet_count) {
        return m_v3[facet_ix];
    } else {
        Float3 v = {0.0, 0.0, 0.0};
        return v;
    }
}

bool StlFile::file_is_valid() const
{
    return m_file_is_valid;
}

const char* StlFile::error_message() const
{
    return m_error_message;
}

bool StlFile::parse()
{
    m_file_is_valid = false;
    int header_count = 80;
    while (!m_bf.is_eof() && header_count > 0) {
        m_bf.advance();
        --header_count;
    }
    if (m_bf.is_eof()) {
        sprintf(m_error_message, "File is too small");
        return false;
    }
    int n = m_bf.get_int();
    if (n < 1) {
        sprintf(m_error_message, "No faces found");
        return false;
    }
    m_v1 = new Float3[n];
    m_v2 = new Float3[n];
    m_v3 = new Float3[n];
    float mag = 1.0;
    for (int i = 0; i < n; i++) {
        if (m_bf.is_eof()) {
            sprintf(m_error_message, "End Of File at face %d out of %d", i+1, n);
            return false;
        }
        m_bf.get_float();              // Skip normal vector
        m_bf.get_float();
        m_bf.get_float();
        m_v1[i].v1 = mag * m_bf.get_float(); // Get first vertex
        m_v1[i].v2 = mag * m_bf.get_float();
        m_v1[i].v3 = mag * m_bf.get_float();
        m_v2[i].v1 = mag * m_bf.get_float(); // Get second vertex
        m_v2[i].v2 = mag * m_bf.get_float();
        m_v2[i].v3 = mag * m_bf.get_float();
        m_v3[i].v1 = mag * m_bf.get_float(); // Get third vertex
        m_v3[i].v2 = mag * m_bf.get_float();
        m_v3[i].v3 = mag * m_bf.get_float();
        if (m_bf.is_eof()) {
            sprintf(m_error_message, "End Of File at face %d out of %d", i+1, n);
            return false;
        }
        m_bf.get_unsigned_short();     // Skip attribute
    }
    m_facet_count = n;
    m_file_is_valid = true;
    return m_file_is_valid;
}

