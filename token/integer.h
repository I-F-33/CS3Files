#ifndef INTEGER_H
#define INTEGER_H
#include "token.h"
#include <iostream>
#include <iomanip>
using namespace std;

class Integer : public Token
{
public:
    Integer(double i) : _value(i), Token(INTEGER, to_string(i)){};
    Integer(string i) : _value(stoi(i)), Token(INTEGER, i){};

    virtual void Print(ostream &outs = cout) const
    {

        outs << setprecision(1)  << get_value() << " ";
    }

    virtual TOKEN_TYPES TypeOf()
    {
        return INTEGER;
    }
    double get_value() const { return _value; }

private:
    double _value;
};

#endif