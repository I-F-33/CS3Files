#ifndef DOUBLE_H
#define DOUBLE_H
#include <iostream>
#include <string>
#include "token.h"
using namespace std;
class Double : public token
{
public:
    Double();
    Double(double value);
    Double(string value);

    void Print(ostream& outs=cout) const;
    TOKEN_TYPES TypeOf(){return DOUBLE;}

    double DoubleOnly(){return d;}
private:
    double d;
};

#endif // DOUBLE_H
