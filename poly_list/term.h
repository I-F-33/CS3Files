#ifndef TERM_H
#define TERM_H
#include <iomanip>
#include <iostream>
using namespace std;

bool double_equals(double left, double right);

struct Term
{
    double _coef;
    int _exp;

    Term();
    Term(double coef, int order);

    Term &operator+=(const Term &rhs)
    {
        // if the exponents are the same, add the coefficients
        if (_exp == rhs._exp)
        {
            _coef += rhs._coef;
        }
        return *this;
    }

    Term &operator-=(const Term &rhs)
    {

        // if the exponents are the same, subtract the coefficients
        if (_exp == rhs._exp)
        {
            _coef -= rhs._coef;
        }

        return *this;
    }

    Term &operator*=(const Term &rhs)
    {
        // multiply the coefficients
        _coef *= rhs._coef;

        // add the exponents
        _exp += rhs._exp;

        return *this;
    }
    Term &operator/=(const Term &rhs)
    {
        // divide the coefficients
        _coef = _coef / rhs._coef;

        // subtract the exponents
        _exp -= rhs._exp;

        return *this;
    }
    Term operator-() const // unary operator
    {
        return Term(-_coef, _exp);
    }

    Term &operator=(const Term &RHS)
    {
        _coef = RHS._coef;
        _exp = RHS._exp;
        return *this;
    }

    friend bool operator==(const Term &lhs, const Term &rhs);
    friend bool operator!=(const Term &lhs, const Term &rhs);
    friend bool operator>(const Term &lhs, const Term &rhs);
    friend bool operator<(const Term &lhs, const Term &rhs);
    friend bool operator>=(const Term &lhs, const Term &rhs);
    friend bool operator<=(const Term &lhs, const Term &rhs);

    // used in Poly division operator
    friend Term operator+(const Term &lhs, const Term &rhs);
    friend Term operator-(const Term &lhs, const Term &rhs);
    friend Term operator*(const Term &lhs, const Term &rhs);
    friend Term operator/(const Term &lhs, const Term &rhs);

    friend ostream &operator<<(ostream &outs, const Term &t);
    friend istream &operator>>(istream &ins, Term &t);
};

#endif // TERM_H