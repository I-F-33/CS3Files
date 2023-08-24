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
    outs<<"[["<<d<<"]]";
}
