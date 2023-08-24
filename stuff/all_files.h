#ifndef ALL_FILES_H
#define ALL_FILES_H
#ifndef CONSTANTS_H
#define CONSTANTS_H

//const int INTEGER = 0;
//const int DOUBLE = 1;

enum TOKEN_TYPES {INTEGER,
                  DOUBLE,
                  OPERATOR=10,
                  LPAREN};
#endif // CONSTANTS_H

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
    virtual void Print(ostream& outs) const;
    virtual TOKEN_TYPES TypeOf(){}


};

#endif // TOKEN_H

#include "token.h"

token::token()
{
}
ostream& operator <<(ostream& outs, const token& token){
    token.Print(outs);
    return outs;
}

void token::Print(ostream &outs) const{
    outs<<"TOKEN Print: DON't ^%#$# call me again!"<<endl;
    //Blank
}




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
    void Print(ostream& outs) const;
    TOKEN_TYPES TypeOf(){return DOUBLE;}
    double DoubleOnly(){return d;}
private:
    double d;
};

#endif // DOUBLE_H
#include "double.h"

Double::Double()
{
}

Double::Double(double value){
    d = value;
}

Double::Double(string value){
    d = atof(value.c_str());
}

void Double::Print(ostream& outs) const{
    outs<<d;
}








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

    void Print(ostream &outs) const ;
    TOKEN_TYPES TypeOf(){return INTEGER;}
    int IntegerOnly(){return i;} //example of a function present in a child
private:
    int i;
};

#endif // INTEGER_H

#include "integer.h"

Integer::Integer()
{
}

Integer::Integer(int value){
    i=value;
}

Integer::Integer(string value){
    i = atoi(value.c_str());
}

void Integer::Print(ostream& outs) const{
    outs<<i;
}







#include <iostream>
#include "container.h"
#include "token.h"
#include "integer.h"
#include "double.h"

using namespace std;
void f(token& t){
    cout<<t<<endl;
}

int main()
{

    Integer i(7);
    token t = i;
    f(i);
//    cout<<t<<endl;
//    cout<<static_cast<Integer>(t)<<endl;
    return 0;
    //container of pointers to parent class:
    Container<token*> c;

    //Adding pointers to child classes to the container:
    token* hold;
    hold = new Integer(54);
    c.Add(hold );
    c.Add(new Double("3.1415"));


    cout<<c.Length()<<endl;
    cout<<"elements in the container: ";
    for (int i=0; i<c.Length(); i++){
        cout<<*c[i]<<"    ";
        //calls << which calls the child's Print virtual function

        //calling virtual functions present in parent
        switch(c[i]->TypeOf()){
        case INTEGER: cout<<"Function from Integer: "<<
                static_cast<Integer*>(c[i])->IntegerOnly()<<endl;
            break;
        case DOUBLE: cout<<"Function from Double: "<<
                static_cast<Double*>(c[i])->DoubleOnly()<<endl;
            break;
        }
    }
    cout<<endl;





    cout <<endl<<endl<<endl<<"-------------------------------" << endl;
    return 0;
}












#endif // ALL_FILES_H
