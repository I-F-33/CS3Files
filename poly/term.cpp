#include "term.h"
// CTOR
Term::Term(double coef, int exp)
{
    _coef = coef;
    _exp = exp;
}

// compare exponent
bool operator ==(const Term& lhs, const Term& rhs)
{
    if ((fabs(lhs._exp - rhs._exp) < 0.00001) && lhs._exp == rhs._exp)
        return true;
    else 
        return false;
}
bool operator !=(const Term& lhs, const Term& rhs)
{
    if (lhs._coef != rhs._coef || lhs._exp != rhs._exp)
        return true;
    else 
        return false;
}
bool operator >(const Term& lhs, const Term& rhs)
{
    if (lhs._exp > rhs._exp)
        return true;
    else if (lhs._exp < rhs._exp)
        return false;
    else
    {
        if(lhs._coef > rhs._coef)
            return true;
        else 
            return false;
    }
}
bool operator <(const Term& lhs, const Term& rhs)
{
    if (lhs._exp < rhs._exp)
        return true;
    else if (lhs._exp > rhs._exp)
        return false;
    else
    {
        if(lhs._coef < rhs._coef)
            return true;
        else 
            return false;
    }
}

Term operator + (const Term& lhs, const Term& rhs)
{
    Term temp_t(lhs);
    if (lhs._exp == rhs._exp)
        temp_t._coef = lhs._coef + rhs._coef;
    
    return temp_t;
}
Term operator * (const Term& lhs, const Term& rhs)
{
    Term temp_t(lhs);
    temp_t._coef = lhs._coef * rhs._coef;
    temp_t._exp = lhs._exp + rhs._exp;
    
    return temp_t;
}
Term operator - (const Term& t)
{
    Term temp_t (t);
    temp_t._coef = - t._coef;
    return temp_t;
}
Term operator - (const Term& lhs, const Term& rhs)
{
    Term temp_t(lhs);
    if (lhs._exp == rhs._exp)
        temp_t._coef = lhs._coef - rhs._coef;
    
    return temp_t;
}
// //used in Poly division operator
Term operator / (const Term& lhs, const Term& rhs)
{
    Term temp_t(lhs);
    if (rhs._coef !=0)
    {
        temp_t._coef = lhs._coef / rhs._coef;
        temp_t._exp = lhs._exp - rhs._exp;
    }
    return temp_t;
}

ostream& operator <<(ostream& outs, const Term& t)
{
    outs.setf(ios::fixed);
    outs.setf(ios::showpoint);
    outs.precision(1);
    //outs.setf(ios:: showpos);
    // if(t._coef == 0)
    //     outs << "0";
    if (t._exp == 0)
        outs << t._coef << "^0";
    else if (t._exp == 1)
        outs << std::showpos << t._coef << "X";
    else
        outs << std::showpos << t._coef << "X^" << std::noshowpos <<t._exp;
    
    return outs;
}
//  t1: +2.0X^5
//  t2: +3.0X^5
//  t3: -6.0X^8
// -t1: -2.0X^5
// -t2: -3.0X^5
// -t3: +6.0X^8
istream& operator >>(istream& ins, Term& t)
{
    int order;
    double coef;
    char x;
    char pow;

     t._coef = coef;
     t._exp = order;

    return ins;
}