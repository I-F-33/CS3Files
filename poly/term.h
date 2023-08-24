#ifndef TERM_H
#define TERM_H

#include "../array_functions/array_functions.h"
#include <cmath>

using namespace std;

struct Term
{
  // variables
  double _coef;
  int _exp;

  // CTOR
  Term(double coef, int exp);

  // compare exponent
  friend bool operator ==(const Term& lhs, const Term& rhs);
  friend bool operator !=(const Term& lhs, const Term& rhs);
  friend bool operator >(const Term& lhs, const Term& rhs);
  friend bool operator <(const Term& lhs, const Term& rhs);

  friend Term operator + (const Term& lhs, const Term& rhs);
  friend Term operator * (const Term& lhs, const Term& rhs);
  friend Term operator - (const Term& t);
  friend Term operator - (const Term& lhs, const Term& rhs);
  //used in Poly division operator
  friend Term operator / (const Term& lhs, const Term& rhs);
  
  friend ostream& operator <<(ostream& outs, const Term& t);
  friend istream& operator >>(istream& ins, Term& t);
};



#endif