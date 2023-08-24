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
