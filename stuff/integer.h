#ifndef INTEGER_H
#define INTEGER_H
#include <string>
#include "token.h"
using namespace std;

class Integer : public token
{
public:
    Integer();
    Integer(int value);
    Integer(string value);

    void Print(ostream &outs=cout) const ;
    TOKEN_TYPES TypeOf(){return INTEGER;}
    int IntegerOnly(){return i;} //example of a function present in a child
private:
    int i;
};

#endif // INTEGER_H
