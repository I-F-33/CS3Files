#ifndef POLY_H
#define POLY_H
#include "../node/node.h"
#include "../list_sorted/list_sorted.h"
#include "term.h"
#include <iostream>
#include <vector>

using namespace std;

class Poly
{
public:
    Poly()
    {
        _poly = List<Term>(false, true);
        _order = 0;
    }

    Poly(double *term_array, int order) : _order(order), _poly(List<Term>(false, true))
    {

        for (int i = 0; i < order + 1; i++)
        {
            Term temp(term_array[i], i);

            _poly.insert(temp);
        }
    }

    Poly(const vector<double> &terms)
    {
        _poly = List<Term>(false, true);

        // find the highest degree term
        // set order to the highest non zero term

        int highest_degree = terms.size() - 1;
        while (highest_degree >= 0 && terms[highest_degree] == 0)
        {

            highest_degree--;
        }

        _order = highest_degree;

        for (int i = 0; i < terms.size(); i++)
        {
            _poly.insert(Term(terms[i], i));
        }
    }
    // big three?

    void remove_zeros()
    {
        if (_poly.empty())
            return;

        List<Term>::Iterator it = _poly.begin();

        // remove all terms with a zero coefficient
        while (it != _poly.end())
        {
            if (it->_coef == 0)
            {
                // remove the term
                _poly.Delete(it);

                // reset the iterator
                it = _poly.begin();
            }
            else
            {
                it++;
            }
        }

        if (!_poly.empty())
        {
            _order = _poly.begin()->_exp;
        }
        else
        {
            _order = 0;
        }
    }

    Poly &operator+=(const Term &t)
    {
        // add the new term to the polynomial, if a term of same exponent is already there, add the coefficients
        // if there is not term with matching exp then add to list
        List<Term>::Iterator it;

        // add the new term to the polynomial, if a term of same exponent is already there, add the coefficients
        for (it = _poly.begin(); it != _poly.end(); it++)
        {
            if (it->_exp == t._exp)
            {
                *it += t;
                return *this;
            }
        }

        // if there is not term with matching exp then add to list
        _poly.insert(t);

        return *this;
    }
    Poly &operator*=(const Term &t)
    {
        if (t._coef == 0)
        {
            _poly.~List();
            _poly = List<Term>(false, true);
            _order = 0;
            _poly.insert(Term(0, 0));
            return *this;
        }
        // iterator for the polynomial
        List<Term>::Iterator it;

        // multiply the coefficients with the new term
        for (it = _poly.begin(); it != _poly.end(); it++)
        {
            // multiply the term with the new term
            *it *= t;
        }

        // return the polynomial
        return *this;
    }

    Poly &operator+=(const Poly &RHS)
    {
        List<Term>::Iterator right;

        // add the new polynomial to the polynomial, if a term of same exponent is already there, add the coefficients
        for (right = RHS._poly.begin(); right != RHS._poly.end(); right++)
        {
            *this += *right;
        }

        return *this;
    }

    Poly &operator*=(const Poly &RHS)
    {
        // iterator for the polynomial
        List<Term>::Iterator right;

        // multiply the coefficients with the new term
        Poly temp = *this;

        Poly product = Poly();

        // multiply the term with each term from the RHS polynomial
        for (right = RHS._poly.begin(); right != RHS._poly.end(); right++)
        {

            Poly product_portion = temp * *right;

            product += product_portion;
        }

        *this = product;
        // return the polynomial
        return *this;
    }

    Poly &operator-=(const Poly &RHS)
    {
        List<Term>::Iterator right;
        // add the new  negative polynomial to the polynomial, if a term of same exponent is already there, add the coefficients
        for (right = RHS._poly.begin(); right != RHS._poly.end(); right++)
        {
            *this += -*right;
        }

        return *this;
    }

    Poly operator-() const
    {
        Poly result = Poly();

        List<Term>::Iterator src;

        // create a new polynomial
        for (src = _poly.begin(); src != _poly.end(); src++)
        {
            result._poly.insert(-*src);
        }

        return result;
    }

    friend bool operator==(const Poly &left, const Poly &right)
    {
        return left._order == right._order;
    }

    friend bool operator!=(const Poly &left, const Poly &right)
    {
        // if the orders are not the same then return true
        // if any term is not equal then return true
        return !(left == right);
    }

    friend Poly operator+(const Poly &left, const Poly &right)
    {
        // temp poly
        Poly temp = left;

        // add the new polynomial to the polynomial, if a term of same exponent is already there, add the coefficients
        temp += right;

        // return the polynomial
        return temp;
    }

    friend Poly operator-(const Poly &left, const Poly &right)
    {
        // temp poly
        Poly temp = left;

        // add the new polynomial to the polynomial, if a term of same exponent is already there, add the coefficients
        temp -= right;

        // return the polynomial
        return temp;
    }

    friend Poly operator*(const Poly &left, const Poly &right)
    {
        Poly temp;

        if (right._order == 0 && right._poly.begin()->_coef == 0 || left._order == 0 && left._poly.begin()->_coef == 0)
        {
            temp._poly.insert(Term(0, 0));
            return temp;
        }
        // temp poly
        temp = left;

        // multiply the coefficients with each term from hte polynomial
        temp *= right;

        // return the polynomial
        return temp;
    }

    friend Poly operator/(const Poly &left, const Poly &right)
    {
/*         Poly result;
        Poly dividend(left);
        Poly zero;


        while (dividend._order >= right._order && dividend != zero)
        {
            Term temp;

            temp = *(dividend._poly.begin()) / *(right._poly.begin());
            result += temp;
            Poly tp = right * temp;
            dividend -= (tp);
        }

        return result; */
           if (right._order > left._order)
               {
                   return Poly();
               }

               if (right._poly.begin() == nullptr || (right._poly.begin()->_coef == 0.0 && right._poly.begin()->_exp == 0))
               {
                   return Poly();
               }

               // temp poly
               Poly temp = left;
               Poly quotient = Poly();

               // Iterator for the polynomials
               List<Term>::Iterator temp_it = temp._poly.begin();

               List<Term>::Iterator right_it = right._poly.begin();

               while (*temp_it >= *right_it)
               {
                   if (right_it->_coef == 0.0)
                   {
                       right_it++;
                   }
                   else if (temp_it->_coef != 0.0)
                   {
                       // get the leading term of the divisor poly
                       Term leading_div = *right_it;
                       Term leading_divid = *temp_it;

                       // get multiple to add to quotient
                       Term multiple = leading_divid / leading_div;

                       // add multiple to quotient
                       quotient._poly.insert(multiple);

                       // multiply the divisor poly by the multiple
                       Poly right_multiple = right * multiple;

                       // subtract the product from the dividend poly
                       temp -= right_multiple;
                   }
                   else if (temp_it->_coef == 0.0 && temp_it->_exp == 0)
                   {
                       break;
                   }
                   else
                   {
                       temp_it++;
                   }
               }
               List<Term>::Iterator quotient_it = quotient._poly.begin();
               quotient._order = quotient_it->_exp;
               return quotient; 
    }
    friend Poly operator%(const Poly &left, const Poly &right)
    {
        Poly temp;

        // get the quotient
        Poly div = left / right;

        // multiply the divisor poly by the quotient
        temp = left - (div * right);

        // if temp is empty, return a zero polynomial
        if (temp._poly.begin() == nullptr)
        {
            temp._order = 0;
            temp._poly.insert(Term(0.0, 0));

            return temp;
        }

        temp.remove_zeros();

        return temp;
    }

    friend Poly operator+(const Poly &left, const Term &t)
    {
        // temp poly
        Poly temp = left;

        // add the new term to the polynomial, if a term of same exponent is already there, add the coefficients
        temp += t;

        // return the polynomial
        return temp;
    }
    friend Poly operator*(const Poly &left, const Term &t)
    {
        // temp poly
        Poly temp = left;

        // multiply the coefficients with the new term
        temp *= t;

        // return the polynomial
        return temp;
    }

    friend ostream &operator<<(ostream &outs, const Poly &print_me)
    {
        // print out the polynomial
        print_me._poly.Print();
        return outs;
    }

    friend istream &operator>>(istream &ins, Poly &read_me)
    {
        List<Term>::Iterator it;

        // read in the terms
        for (it = read_me._poly.begin(); it != read_me._poly.end(); it++)
        {
            // read in the term
            ins >> *it;
        }

        return ins;
    }

    const Term &operator[](const int exp) const
    {
        List<Term>::Iterator it = _poly.begin();
        for (; it != _poly.end(); it++)
        {
            if (it->_exp == exp)
            {
                return *it;
            }
        }
    }

    Term &operator[](const int exp)
    {
        List<Term>::Iterator it = _poly.begin();
        for (; it != _poly.end(); it++)
        {
            if (it->_exp == exp)
            {
                return *it;
            }
        }
    }
    List<Term> list() const { return _poly; }

    int order() const { return _order; }

private:
    List<Term> _poly; // descending sorted list
    int _order;
};
#endif // POLY_H