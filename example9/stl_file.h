//
// stl_file.h
//

#ifndef _STL_FILE_H_
#define _STL_FILE_H_

#include "bin_file.h"
#include "float3.h"
#include "int3.h"

class StlFile
{
public:
    StlFile(const char* file_name);
    ~StlFile();
    bool file_is_valid() const;
    const char* error_message() const;
    int facets() const;
    Float3 facet_v1(int facet_ix) const;
    Float3 facet_v2(int facet_ix) const;
    Float3 facet_v3(int facet_ix) const;

private:
    bool m_file_is_valid;
    bool m_pass2;
    BinFile m_bf;
    char m_error_message[256];
    int m_facet_count;
    Float3* m_v1;
    Float3* m_v2;
    Float3* m_v3;

    bool parse();
};

#endif // _STL_FILE_H_
