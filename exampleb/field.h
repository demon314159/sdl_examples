//
// field.h
//

#ifndef _FIELD_H_
#define _FIELD_H_

struct Field {
    int value;
    bool flash;
    bool blank;
    bool leading_zeroes;
    int first_digit;
    int last_digit;
};

#endif // _FIELD_H_
