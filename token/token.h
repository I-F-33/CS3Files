#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>
using namespace std;
#include "constants.h"

class Token
{
public:
    Token();
    Token(TOKEN_TYPES type, string value = "i");

    friend ostream &operator<<(ostream &outs, const Token &token)
    {
        outs << token.get_value() << " ";
        return outs;
    }
    virtual void Print(ostream &outs = cout) const
    {
    }
    virtual TOKEN_TYPES TypeOf()
    {
        return _type;
    }
    string get_value() const { return _value; }

private:
    TOKEN_TYPES _type;
    string _value;
};

#endif // TOKEN_H
