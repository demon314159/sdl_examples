//
// token_file.h
//

#ifndef _TOKEN_FILE_H_
#define _TOKEN_FILE_H_

#include "char_file.h"

#define MAX_TOKEN_CHARS 255

class TokenFile
{
    const int TYPE_EMPTY = 0;
    const int TYPE_UNKNOWN = 1;
    const int TYPE_IDENTIFIER = 2;
    const int TYPE_UNSIGNED_INTEGER = 3;
    const int TYPE_OPERATOR = 4;
public:
    TokenFile(const char* file_name);
    ~TokenFile();

    bool error_flag() const;
    const char* error_message() const;
    void rewind();
    void advance();
    bool is_eof() const;
    bool is_identifier() const;
    bool is_unsigned_integer() const;
    bool is_operator() const;
    char* current() const;
    int line_count() const;

private:
    CharFile m_cf;
    int m_type;
    int m_token_ix;
    char* m_token;
    int m_line_count;
    void skip_whitespace();
    void scan_identifier();
    void scan_unsigned_integer();
    void scan_operator();
    void clear_token();
    void add_to_token(char c);
};

#endif // _TOKEN_FILE_H_
