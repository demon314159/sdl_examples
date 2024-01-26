//
// char_file.h
//

#ifndef _CHAR_FILE_H_
#define _CHAR_FILE_H_

class CharFile
{
public:
    CharFile(const char* file_name);
    ~CharFile();
    void rewind();
    void advance();
    char current() const;
    bool is_eof() const;
    bool is_eol() const;    // CR or LF
    bool is_eol1() const;   // LF
    bool is_eol2() const;   // CR
    bool is_blank() const;  // TAB or SPACE
    bool is_alpha() const;  // a-zA-Z_
    bool is_digit() const;  // 0-9
    bool is_symbol() const; // !"#$%&'()*+,-./:;<=>?@[\]^`{|}~

private:
    int m_pos;
    int m_size;
    char* m_buf;
};

#endif // _CHAR_FILE_H_
