//
// char_file.cpp
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>
#include <algorithm>

#include "char_file.h"

CharFile::CharFile(const char* file_name)
    : m_error_flag(false)
    , m_error_message(new char[256])
    , m_line_count1(1)
    , m_line_count2(1)
    , m_pos(0)
    , m_size(0)
    , m_buf(NULL)
{
    m_error_message[0] = 0;
    FILE* ffi = fopen(file_name, "rb");
    if (ffi == NULL) {
        sprintf(m_error_message, "Error opening file '%s'", file_name);
        m_error_flag = true;
    } else {
        struct stat st;
        stat(file_name, &st);
        m_size = st.st_size;
        m_buf = new char[m_size];
        int n = fread(m_buf, 1, m_size, ffi);
        fclose(ffi);
        if (n != m_size) {
            m_size = 0;
            sprintf(m_error_message, "Error reading file '%s'", file_name);
            m_error_flag = true;
        }
    }
}

CharFile::~CharFile()
{
    delete [] m_error_message;
    if (m_buf != NULL) {
        delete [] m_buf;
    }
}

int CharFile::line_count() const
{
    return std::max(m_line_count1, m_line_count2);
}

bool CharFile::error_flag() const
{
    return m_error_flag;
}

const char* CharFile::error_message() const
{
    return m_error_message;
}

void CharFile::rewind()
{
    m_pos = 0;
}

void CharFile::advance()
{
    if (is_eol1()) {
        ++m_line_count1;
    }
    if (is_eol2()) {
        ++m_line_count2;
    }
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
