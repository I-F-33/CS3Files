#include "poly.h"
#include "../../includes/array_functions/array_functions.h"
#include "term.h"
#include <iomanip>
#include <iostream>
using namespace std;
Poly::Poly()
{
  _order = 0;
  _coefs = new double[1];
  _coefs[0] = 0.0;
}
Poly::Poly(double *coefs, int order)
{
  _coefs = copy_array(coefs, order + 1);
  _order = order;
  this->fix_order();
}

// BIG 3
Poly::Poly(const Poly &other)
{
  _coefs = copy_array(other._coefs, other._order + 1);
  _order = other._order;
}
Poly &Poly::operator=(const Poly &rhs)
{
  this->_order = rhs._order;
  this->_coefs = copy_array(rhs._coefs, rhs._order + 1);

  return *this;
}
Poly::~Poly()
{
  delete[] _coefs;
}

bool operator==(const Poly &lhs, const Poly &rhs)
{
  if (lhs._order != rhs._order)
    return false;
  else
  {
    bool same = true;
    for (int i = 0; i < lhs._order && same == true; i++)
    {
      if (lhs[i] == rhs[i])
        same = true;
      else
        same = false;
    }
    return same;
  }
}
bool operator!=(const Poly &lhs, const Poly &rhs)
{
  if (lhs == rhs)
    return false;
  else
    return true;
}
bool operator>(const Poly &lhs, const Poly &rhs)
{
  if (lhs._order > rhs._order)
    return true;
  else if (lhs._order < rhs._order)
    return false;
  else
  {
    bool large = false;
    for (int i = 0; i < lhs._order && large == false; i++)
    {
      if (lhs[i] > rhs[i])
        large = true;
      else if (lhs[i] < rhs[i])
      {
        break;
      }
      else
        i++;
    }
    return large;
  }
}
bool operator<(const Poly &lhs, const Poly &rhs)
{
  if (lhs == rhs || lhs > rhs)
    return false;
  else
    return true;
}

Term Poly::operator[](int order) const
{
  double *walker = this->_coefs;
  walker += order;
  Term term(*walker, order);

  return term;
}
// p[2]: +6.0X^2
// q[5]: +9.0X^5

Poly operator+(const Poly &lhs, const Term &t)
{
  Poly lhs_copy(lhs);
  if (lhs._order < t._exp)
  {
    lhs_copy._order = t._exp;
    lhs_copy._coefs = reallocate(lhs_copy._coefs, t._exp + 1, t._exp + 1);

    for (int i = 0; i < lhs_copy._order - lhs._order; i++)
      *(lhs_copy._coefs + lhs._order + i + 1) = 0.0;
  }

  Term temp = lhs_copy[t._exp] + t;

  lhs_copy._coefs[t._exp] = temp._coef;
  lhs_copy.fix_order();
  // lhs_copy.set_precision();
  return lhs_copy; //=================================================delete
} // p + t1   : [+2.0X^5 +4.0X^4 +0.0X^3 +6.0X^2 +5.0X +8.0^0  ]

Poly operator+(const Poly &lhs, const Poly &rhs)
{

  Poly add(lhs);

  if (lhs._order < rhs._order)
  {
    add._order = rhs._order;
    add._coefs = reallocate(add._coefs, add._order + 1, add._order + 1);

    for (int i = 0; i < add._order - lhs._order; i++)
      *(add._coefs + lhs._order + i + 1) = 0.0;
  }

  for (int i = 0; i < rhs._order + 1; i++)
  {
    add = add + rhs[i];
  }
  add.fix_order();
  // add.set_precision();
  return add;
}
//[+9.0X^5 +5.0X^4 +0.0X^3 +9.0X^2 +12.0X +10.0^0  ]

Poly operator-(const Poly &p)
{
  Poly n(p);

  // double* walker = n._coefs;
  for (int i = 0; i < p._order + 1; i++)
  {
    double *walker = n._coefs + i;
    Term temp = p[i];
    if (temp._coef != 0)
      *walker = -(temp._coef);
  }
  n.fix_order();
  // n.set_precision();
  return n;
}
Poly operator-(const Poly &lhs, const Poly &rhs)
{
  // Poly sub(lhs);

  Poly n_rhs(-rhs);
  Poly sub = lhs + n_rhs;
  sub.fix_order();
  // sub.set_precision();
  return lhs + n_rhs; //+ n_rhs;
}
//[-9.0X^5 +3.0X^4 +0.0X^3 +3.0X^2 -2.0X +6.0^0  ]

Poly operator*(const Poly &lhs, const Term &t)
{
  // double coef[] = { 0.0 };
  // Poly product(coef, 0);

  if (t._coef == 0.0)
  {
    return Poly();
  }
  Poly product(lhs);
  product._order = lhs._order + t._exp;
  product._coefs = reallocate(product._coefs, product._order + 1, product._order + 1);

  for (int i = 0; i < product._order + 1; i++)
    *(product._coefs + i) = 0.0;

  for (int i = 0; i < lhs._order + 1; i++)
  {
    Term temp = lhs[i] * t;
    product = product + temp;
  }
  product.fix_order();
  // product.set_precision();
  return product;

} //[+8.0X^9 +0.0X^8 +12.0X^7 +10.0X^6 +16.0X^5 +0.0X^4 +0.0X^3 +0.0X^2 +0.0X +0.0^0  ]
Poly operator*(const Poly &lhs, const Poly &rhs)
{
  Poly product(lhs);
  product._order = lhs._order + rhs._order;
  product._coefs = reallocate(product._coefs, product._order + 1, product._order + 1);

  for (int i = 0; i < product._order + 1; i++)
    *(product._coefs + i) = 0.0;

  for (int i = 0; i < rhs._order + 1; i++)
  {
    Term temp_t = rhs[i];

    Poly temp_p = lhs * temp_t;
    product = product + temp_p;
  }
  product.fix_order();
  // product.set_precision();
  return product;
}
//[+36.0X^9 +4.0X^8 +54.0X^7 +63.0X^6 +105.0X^5 +34.0X^4 +57.0X^3 +71.0X^2 +66.0X +16.0^0  ]

Poly operator/(const Poly &lhs, const Poly &rhs)
{
  Poly quotient;
  if (lhs._order < rhs._order)
  {
    return quotient;
  }

  else
  {
    Poly lhs_c(lhs);
    Poly rhs_c(rhs);
    Term temp(0.0, 0);
    int dOfPow = lhs_c._order - rhs_c._order;
    quotient._coefs = new double[dOfPow + 1];
    for (int i = 0; i < dOfPow + 1; i++)
      *(quotient._coefs + i) = 0;
    quotient._order = dOfPow;

    while (lhs_c._order >= rhs_c._order)
    {

      temp._exp = lhs_c._order - rhs_c._order;

      temp._coef = *(lhs_c._coefs + lhs_c._order) / *(rhs_c._coefs + rhs_c._order);
      quotient._coefs[temp._exp] = temp._coef;
      if (lhs_c._order == 0)
      {
        quotient.fix_order();
        // quotient.set_precision();
        return quotient;
      }
      Term temp2 = -temp;
      lhs_c = lhs_c + rhs_c * temp2;
    }
    quotient.fix_order();
    // quotient.set_precision();
    return quotient; // rhs_c2 destructor===============================================================
  }
}
Poly operator%(const Poly &lhs, const Poly &rhs)
{

  Poly div = lhs / rhs;

  if (div.get_coefs()[0] == 0.0 && div.order() == 0)
    return Poly();
  // Poly m = lhs - div * rhs;
  // m.fix_order();
  // m.set_precision();
  return lhs - div * rhs;
}

ostream &operator<<(ostream &outs, const Poly &p)
{

  outs << "[ ";
  for (int i = p._order; i >= 0; i--)
  {
    double *walker = p._coefs + i;
    Term term(*walker, i);
    outs << term << " ";
  }
  outs << " ]";

  return outs;
}
// double coefs1[] = {8.0,5.0,6.0,0.0,4.0};
// double coefs2[] = {2.0,7.0,3.0,0.0,1.0,9.0};
// Poly p(coefs1, 4);
// Poly q(coefs2, 5);
// p: [+4.0X^4 +0.0X^3 +6.0X^2 +5.0X +8.0^0  ]
// q: [+9.0X^5 +1.0X^4 +0.0X^3 +3.0X^2 +7.0X +2.0^0  ]

istream &operator>>(istream &ins, Poly &p)
{
  Term term(0.0, 0);
  do
  {
    ins >> term;
    p._coefs[term._exp] = term._coef;
  } while (term._exp >= 0);

  return ins;
}

double *Poly::get_coefs() const
{
  return this->_coefs;
}
// int order() const { return _order; }
void Poly::set_order(int new_order)
{
  this->_order = new_order;
}
void Poly::fix_order() // get rid of highest terms with zero coefs
{
  double *walker = this->_coefs + this->_order;
  while (*walker == 0)
  {
    this->_order--;
    walker--;
    // cout << "fix order" << endl;
  }
  this->_coefs = reallocate(this->_coefs, this->_order + 1, this->_order + 1);
}
