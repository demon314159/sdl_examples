//
// qa.cpp
//

#include "qa.h"

#include <stdio.h>

int Qa::m_iterations = 0;
int Qa::m_light_test = 0;
int Qa::m_light_test_pass = 0;
int Qa::m_sqrt_test = 0;
int Qa::m_sqrt_test_pass = 0;
int Qa::m_heavy_test = 0;
int Qa::m_heavy_test_pass = 0;

Qa::Qa()
{
}

void Qa::light_test()
{
    ++m_light_test;
}

void Qa::light_test_pass()
{
    ++m_light_test_pass;
}

void Qa::sqrt_test()
{
    ++m_sqrt_test;
}

void Qa::sqrt_test_pass()
{
    ++m_sqrt_test_pass;
}

void Qa::heavy_test()
{
    ++m_heavy_test;
}

void Qa::heavy_test_pass()
{
    ++m_heavy_test_pass;
}

void Qa::iteration()
{
    ++m_iterations;
}

void Qa::report()
{
    printf("iterations = %d\n", m_iterations);
    if (m_iterations > 0) {
        printf("     light_test %d\n", m_light_test / m_iterations);
        printf("      sqrt_test %d\n", m_sqrt_test / m_iterations);
        printf("     heavy_test %d\n", m_heavy_test / m_iterations);
        printf("\n\n");
        printf("     light_test hit ratio %.6f\n", ((float) m_light_test_pass) / (float) m_light_test);
        printf("      sqrt_test hit ratio %.6f\n", ((float) m_sqrt_test_pass) / (float) m_sqrt_test);
        printf("     heavy_test hit ratio %.6f\n", ((float) m_heavy_test_pass) / (float) m_heavy_test);
    }
}
