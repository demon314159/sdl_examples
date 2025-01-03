//
// token_file.cpp
//

#include "token_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define notVERBOSE
#define MAX_TOKEN_CHARS 255

TokenFile::TokenFile(const char* file_name)
    : m_cf(file_name)
    , m_type(TYPE_EMPTY)
    , m_token_ix(0)
    , m_token(new char[MAX_TOKEN_CHARS + 1])
{
#ifdef VERBOSE
    printf("TokenFile(%s)\n", file_name);
#endif
    clear_token();
}

TokenFile::~TokenFile()
{
#ifdef VERBOSE
    printf("~TokenFile()\n");
#endif
    delete [] m_token;
}

void TokenFile::rewind()
{
    m_cf.rewind();
    clear_token();
    m_type = TYPE_EMPTY;
}

void TokenFile::advance()
{
    skip_whitespace();
    clear_token();
    m_type = TYPE_EMPTY;
    if (m_cf.is_eof()) {
        return;
    } else if (m_cf.is_alpha()) {
        scan_identifier();
    } else if (m_cf.is_digit()) {
        scan_unsigned_integer();
    } else if (m_cf.is_symbol()) {
        scan_operator();
    }
}

bool TokenFile::is_eof() const
{
    return m_cf.is_eof();
}

char* TokenFile::current() const
{
    return m_token;
}

void TokenFile::skip_whitespace()
{
    bool in_comment = m_cf.current() == '#';

    while (in_comment || (!m_cf.is_alpha() && !m_cf.is_digit() && !m_cf.is_symbol() && !m_cf.is_eof())) {
        m_cf.advance();
        if (m_cf.is_eol1() || m_cf.is_eol2()) {
            in_comment = false;
        } else if (m_cf.current() == '#') {
            in_comment = true;
        }
    }
}

void TokenFile::clear_token()
{
    m_token_ix = 0;
    m_token[0] = 0;
}

void TokenFile::add_to_token(char c)
{
    if (m_token_ix < MAX_TOKEN_CHARS) {
        m_token[m_token_ix++] = c;
        m_token[m_token_ix] = 0;
    }
}

void TokenFile::scan_identifier()
{
    m_type = TYPE_IDENTIFIER;
    if (m_token_ix < MAX_TOKEN_CHARS) {
       add_to_token(m_cf.current());
    }
    m_cf.advance();
    while (m_cf.is_alpha() || m_cf.is_digit()) {
        add_to_token(m_cf.current());
        m_cf.advance();
    }
}

void TokenFile::scan_unsigned_integer()
{
    m_type = TYPE_UNSIGNED_INTEGER;
    add_to_token(m_cf.current());
    m_cf.advance();
    while (m_cf.is_digit()) {
        add_to_token(m_cf.current());
        m_cf.advance();
    }
}

void TokenFile::scan_operator()
{
    m_type = TYPE_OPERATOR;
    add_to_token(m_cf.current());
    m_cf.advance();
}

bool TokenFile::is_identifier() const
{
    return m_type == TYPE_IDENTIFIER;
}

bool TokenFile::is_unsigned_integer() const
{
    return m_type == TYPE_UNSIGNED_INTEGER;
}

bool TokenFile::is_operator() const
{
    return m_type == TYPE_OPERATOR;
}

