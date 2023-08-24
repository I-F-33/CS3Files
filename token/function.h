#ifndef FUNCTION_H
#define FUNCTION_H
#include "token.h"
#include "operator.h"
#include <iostream>
#include <string>
using namespace std;

class Function : public Operator
{
public:
    Function(string fx) : Operator(fx),  _function(fx){};

    string get_function() const { return _function; }

    void Print(ostream &outs = cout) const
    {
        Print(outs);
    }

     virtual TOKEN_TYPES TypeOf()
    {
        return FUNCTION;
    }

private:

    string _function;

};

#endif // FUNCTION_H