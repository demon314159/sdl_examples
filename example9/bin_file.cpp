//
// bin_file.cpp
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "bin_file.h"

#define notVERBOSE

BinFile::BinFile(const char* file_name)
    : m_pos(0)
    , m_size(0)
    , m_buf(nullptr)
{
#ifdef VERBOSE
    printf("BinFile(%s)\n", file_name);
#endif

    FILE* ffi = fopen(file_name, "rb");
    if (ffi == NULL) {
#ifdef VERBOSE
        printf("<<< Error opening file '%s' >>>\n", file_name);
#endif
        return;
    }

    struct stat file_status;
    if (stat(file_name, &file_status) < 0) {
#ifdef VERBOSE
        printf("<<< Error getting file status '%s' >>>\n", file_name);
#endif
        return;
    }
    m_size = file_status.st_size;
    if (m_size == 0) {
#ifdef VERBOSE
        printf("<<< File is empty '%s' >>>\n", file_name);
#endif
        return;
    }

    m_buf = new char[m_size];
#ifdef VERBOSE
    printf("Size of file = %d\n", m_size);
#endif

    int n = fread(m_buf, 1, m_size, ffi);
    fclose(ffi);
    if (n != m_size) {
#ifdef VERBOSE
        printf("<<< Expecting %d bytes but read %d bytes >>>\n", m_size, n);
#endif
        m_size = 0;
        return;
    } else {
#ifdef VERBOSE
    printf("Bytes read = %d\n", n);
#endif
    }
}

BinFile::~BinFile()
{
#ifdef VERBOSE
    printf("~BinFile()\n");
#endif
    if (m_buf != NULL) {
        delete [] m_buf;
    }
}

void BinFile::rewind()
{
    m_pos = 0;
}

void BinFile::advance()
{
    if (m_pos < m_size) {
        ++m_pos;
    }
}

char BinFile::current() const
{
    if (m_pos < m_size) {
        return m_buf[m_pos];
    } else {
        return 0;
    }
}

bool BinFile::is_eof() const
{
    return m_pos >= m_size;
}

unsigned short BinFile::get_unsigned_short()
{
    if (m_pos < (m_size - 1)) {
        unsigned short* v = (unsigned short*) &m_buf[m_pos];
        m_pos += 2;
        return *v;
    } else {
        printf("\n<<< BinFile::get_unsigned_short() past end of file should never happen >>>\n");
        return 0;
    }
}

int BinFile::get_int()
{
    if (m_pos < (m_size - 3)) {
        int* v = (int*) &m_buf[m_pos];
        m_pos += 4;
        return *v;
    } else {
        printf("\n<<< BinFile::get_int() past end of file should never happen >>>\n");
        return 0;
    }
}

float BinFile::get_float()
{
    if (m_pos < (m_size - 3)) {
        float* v = (float*) &m_buf[m_pos];
        m_pos += 4;
        return *v;
    } else {
        printf("\n<<< BinFile::get_float() past end of file should never happen >>>\n");
        return 0;
    }
}


