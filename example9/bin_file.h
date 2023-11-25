//
// bin_file.h
//

#ifndef _BIN_FILE_H_
#define _BIN_FILE_H_

class BinFile
{
public:
    BinFile(const char* file_name);
    ~BinFile();
    void rewind();
    void advance();
    char current() const;
    unsigned short get_unsigned_short();
    int get_int();
    float get_float();
    bool is_eof() const;

private:
    int m_pos;
    int m_size;
    char* m_buf;
};

#endif // _BIN_FILE_H_
