//
// stl_interface.cpp
//
#include <stdio.h>
#include "stl_interface.h"

#define notVERBOSE

StlInterface::StlInterface(const char* file_name)
    : m_file_is_valid(false)
    , m_bi(file_name)
    , m_error_message("no errors")
    , m_facet_count(0)
    , m_v1(nullptr)
    , m_v2(nullptr)
    , m_v3(nullptr)
{
#ifdef VERBOSE
    printf("StlInterface(%s)\n", file_name);
#endif
    parse();
#ifdef VERBOSE
    printf("%d facets\n", m_facet_count);
#endif
}

StlInterface::~StlInterface()
{
#ifdef VERBOSE
    printf("~StlInterface()\n");
#endif
    if (m_v1 != nullptr)
        delete [] m_v1;
    if (m_v2 != nullptr)
        delete [] m_v2;
    if (m_v3 != nullptr)
        delete [] m_v3;
}

int StlInterface::facets() const
{
    return m_facet_count;
}

Float3 StlInterface::facet_v1(int facet_ix) const
{
    if (facet_ix < m_facet_count) {
        return m_v1[facet_ix];
    } else {
        Float3 v = {0.0, 0.0, 0.0};
        return v;
    }
}

Float3 StlInterface::facet_v2(int facet_ix) const
{
    if (facet_ix < m_facet_count) {
        return m_v2[facet_ix];
    } else {
        Float3 v = {0.0, 0.0, 0.0};
        return v;
    }
}

Float3 StlInterface::facet_v3(int facet_ix) const
{
    if (facet_ix < m_facet_count) {
        return m_v3[facet_ix];
    } else {
        Float3 v = {0.0, 0.0, 0.0};
        return v;
    }
}

bool StlInterface::file_is_valid() const
{
    return m_file_is_valid;
}

const char* StlInterface::error_message() const
{
    return m_error_message;
}

bool StlInterface::parse()
{
    m_file_is_valid = false;
    int header_count = 80;
    while (!m_bi.is_eof() && header_count > 0) {
        m_bi.advance();
        --header_count;
    }
    if (m_bi.is_eof()) {
        sprintf(m_error_message, "File is too small");
        return false;
    }
    int n = m_bi.get_int();
    if (n < 1) {
        sprintf(m_error_message, "No faces found");
        return false;
    }
    m_v1 = new Float3[n];
    m_v2 = new Float3[n];
    m_v3 = new Float3[n];
    float mag = 1.0;
    for (int i = 0; i < n; i++) {
        if (m_bi.is_eof()) {
            sprintf(m_error_message, "End Of File at face %d out of %d", i+1, n);
            return false;
        }
        m_bi.get_float();              // Skip normal vector
        m_bi.get_float();
        m_bi.get_float();
        m_v1[i].v1 = mag * m_bi.get_float(); // Get first vertex
        m_v1[i].v2 = mag * m_bi.get_float();
        m_v1[i].v3 = mag * m_bi.get_float();
        m_v2[i].v1 = mag * m_bi.get_float(); // Get second vertex
        m_v2[i].v2 = mag * m_bi.get_float();
        m_v2[i].v3 = mag * m_bi.get_float();
        m_v3[i].v1 = mag * m_bi.get_float(); // Get third vertex
        m_v3[i].v2 = mag * m_bi.get_float();
        m_v3[i].v3 = mag * m_bi.get_float();
        if (m_bi.is_eof()) {
            sprintf(m_error_message, "End Of File at face %d out of %d", i+1, n);
            return false;
        }
        m_bi.get_unsigned_short();     // Skip attribute
    }
    m_facet_count = n;
    m_file_is_valid = true;
    return m_file_is_valid;
}

