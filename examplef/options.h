//
// options.h
//

#ifndef _OPTIONS_H_
#define _OPTIONS_H_

class Options
{
public:
    Options(int argc, char* argv[]);
    ~Options();

    bool wire_frame() const;
    const char* file_name() const;
private:
    bool m_wire_frame;
    char m_file_name[256];
};

#endif // _OPTIONS_H_
