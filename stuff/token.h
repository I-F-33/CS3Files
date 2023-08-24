#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include "constants.h"

using namespace std;

class token
{
public:
    token();
    friend ostream& operator <<(ostream& outs, const token& token);
    virtual void Print(ostream& outs=cout) const;
    TOKEN_TYPES TypeOf(){}


};

#endif // TOKEN_H
