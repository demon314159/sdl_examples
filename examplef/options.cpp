//
// options.cpp
//

#include "options.h"
#include <string.h>

Options::Options(int argc, char* argv[])
{
    m_wire_frame = false;
    strcpy(m_file_name, "default.stl");
    for (int i = 1; i < argc; i++) {
        char *s = argv[i];
        if (s[0] == '-') {
            if (s[1] == 'w') {
                m_wire_frame = true;
            }
        } else {
            strcpy(m_file_name, s);
            if (strchr(s, '.') == NULL) {
                strcat(m_file_name, ".stl");
            }
        }
    }
}

Options::~Options()
{
}

bool Options::wire_frame() const
{
    return m_wire_frame;
}

const char* Options::file_name() const
{    return m_file_name;
}
