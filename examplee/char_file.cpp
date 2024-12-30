//
// char_file.cpp
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>

#include "char_file.h"

#define notVERBOSE

CharFile::CharFile(const char* file_name)
    : m_pos(0)
    , m_size(0)
    , m_buf(NULL)
{
#ifdef VERBOSE
    printf("CharFile(%s)\n", file_name);
#endif
    FILE* ffi = fopen(file_name, "r");
    if (ffi == NULL) {
#ifdef VERBOSE
        printf("<<< Error opening file '%s' >>>\n", file_name);
#endif
    } else {
        struct stat st;
        stat(file_name, &st);
        m_size = st.st_size;
        m_buf = new char[m_size];
#ifdef VERBOSE
        printf("Size of file = %d\n", m_size);
#endif
        int n = fread(m_buf, 1, m_size, ffi);
        fclose(ffi);
#ifdef VERBOSE
        printf("Chars read = %d\n", n);
#endif
        if (n != m_size) {
            m_size = 0;
        }
    }
}

CharFile::~CharFile()
{
#ifdef VERBOSE
    printf("~CharFile()\n");
#endif
    if (m_buf != NULL) {
        delete [] m_buf;
    }
}

void CharFile::rewind()
{
    m_pos = 0;
}

void CharFile::advance()
{
    if (m_pos < m_size) {
        ++m_pos;
    }
}

char CharFile::current() const
{
    if (m_pos < m_size) {
        return m_buf[m_pos];
    } else {
        return ' ';
    }
}

bool CharFile::is_eof() const
{
    return m_pos >= m_size;
}

bool CharFile::is_eol() const
{
    return is_eol1() || is_eol2();
}

bool CharFile::is_eol1() const
{
    if (m_pos < m_size) {
        return m_buf[m_pos] == 0x0a;
    }
    return false;
}

bool CharFile::is_eol2() const
{
    if (m_pos < m_size) {
        return m_buf[m_pos] == 0x0d;
    }
    return false;
}

bool CharFile::is_blank() const
{
    if (m_pos < m_size) {
        return isblank(m_buf[m_pos]);
    }
    return false;
}

bool CharFile::is_alpha() const
{
    if (m_pos < m_size) {
        return isalpha(m_buf[m_pos]) || m_buf[m_pos] == '_';
    }
    return false;
}

bool CharFile::is_digit() const
{
    if (m_pos < m_size) {
        return isdigit(m_buf[m_pos]);
    }
    return false;
}

bool CharFile::is_symbol() const
{
    if (m_pos < m_size) {
        return ispunct(m_buf[m_pos]) && m_buf[m_pos] != '_';
    }
    return false;
}
