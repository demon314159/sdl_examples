//
// qa.h
//

#ifndef _QA_H_
#define _QA_H_

class Qa
{
public:
    Qa();

    void sqrt_test();
    void sqrt_test_pass();
    void heavy_test();
    void heavy_test_pass();
    void iteration();
    void report();

protected:
    static int m_iterations;
    static int m_sqrt_test;
    static int m_sqrt_test_pass;
    static int m_heavy_test;
    static int m_heavy_test_pass;
};

#endif // _QA_H_

