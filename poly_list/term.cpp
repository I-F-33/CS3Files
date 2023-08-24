#include "term.h"
#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;

bool double_equals(double left, double right)
{
    return fabs(left - right) < 0.001 ? true : false;
}

Term::Term()
{
    _coef = 0;
    _exp = 0;
}
Term::Term(double coef, int order)
{
    _coef = coef;
    _exp = order;
}

bool operator==(const Term &lhs, const Term &rhs)
{
    return double_equals(lhs._coef, rhs._coef) && lhs._exp == rhs._exp;
}

bool operator!=(const Term &lhs, const Term &rhs)
{
    return lhs._coef != rhs._coef || lhs._exp != rhs._exp;
}
bool operator>(const Term &lhs, const Term &rhs)
{
    return lhs._exp > rhs._exp;
}
bool operator<(const Term &lhs, const Term &rhs)
{
    return lhs._exp < rhs._exp;
}

bool operator>=(const Term &lhs, const Term &rhs)
{
    return lhs._exp >= rhs._exp;
}
bool operator<=(const Term &lhs, const Term &rhs)
{
    return lhs._exp <= rhs._exp;
}

// used in Poly division operator
Term operator+(const Term &lhs, const Term &rhs)
{
    Term temp = Term();

    // if the exponents are the same, add the coefficients
    if (lhs._exp == rhs._exp)
    {
        temp._coef = lhs._coef + rhs._coef;
        temp._exp = lhs._exp;
    }

    // return the new term or the default if exponent is different
    return temp;
}
Term operator-(const Term &lhs, const Term &rhs)
{
    Term temp = Term();

    // if the exponents are the same, subtract the coefficients
    if (lhs._exp == rhs._exp)
    {
        temp._coef = lhs._coef - rhs._coef;
        temp._exp = lhs._exp;
    }

    // return the new term or the default if exponent is different
    return temp;
}
Term operator*(const Term &lhs, const Term &rhs)
{
    Term temp = Term();

    // multiply the coefficients
    temp._coef = lhs._coef * rhs._coef;
    // add the exponents
    temp._exp = lhs._exp + rhs._exp;

    // return the new term
    return temp;
}
Term operator/(const Term &lhs, const Term &rhs)
{

    Term temp = Term();

    // divide the coefficients
    temp._coef = lhs._coef / rhs._coef;

    // subtract the exponents
    temp._exp = lhs._exp - rhs._exp;

    // return the new term
    return temp;
}

ostream &operator<<(ostream &outs, const Term &t)
{
    if (t._exp > 1)
    {
        outs << showpos << fixed << setprecision(1) << t._coef << noshowpos << "x^" << t._exp;
    }
    else if (t._exp == 1)
    {
        outs << showpos << fixed << setprecision(1) << t._coef << noshowpos << "x";
    }

    else
    {
        outs << showpos << fixed << setprecision(1) << t._coef;
    }

    return outs;
}

istream &operator>>(istream &ins, Term &t)
{
    return ins >> t._coef >> t._exp;
}