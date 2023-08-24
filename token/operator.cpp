#include "operator.h"
#include "tk_constants.h"
#include <iostream>
#include "integer.h"
#include <cmath>

using namespace std;

Operator::Operator(const string &str) : Token(OPERATOR, str), _operator(str), _type(OPERATOR)
{
    precedence = get_prec();
}

void Operator::int_only()
{
    cout << "Hello form integer" << endl;
}
int Operator::get_prec()
{
    if (_operator == "+" || _operator == "-")
        return 1;
    else if (_operator == "*" || _operator == "/")
        return 2;
    else if (_operator == "^")
        return 3;
    else if(_operator == "X")
        return 4;
    else 
        return 0;
}

Token *Operator::eval(Token *left, Token *right)
{

    if (_operator == "+")
        return new Integer(static_cast<Integer *>(left)->get_value() + static_cast<Integer *>(right)->get_value());
    else if (_operator == "-")
        return new Integer(static_cast<Integer *>(left)->get_value() - static_cast<Integer *>(right)->get_value());
    else if (_operator == "*")
        return new Integer(static_cast<Integer *>(left)->get_value() * static_cast<Integer *>(right)->get_value());
    else if (_operator == "/")
        return new Integer(static_cast<Integer *>(left)->get_value() / static_cast<Integer *>(right)->get_value());
    else if (_operator == "^")
        return new Integer(pow(static_cast<Integer *>(left)->get_value(), static_cast<Integer *>(right)->get_value()));
    else
        return 0;
}


