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
    outs<<"["<<i<<"]";
}
