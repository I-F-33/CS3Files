#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <string>
using namespace std;

class Rational
{
public:
    Rational();
    Rational(int num, int denom);
    Rational(int w);        //whole number

    //mutators / setters
    void set(int num, int denom);
    void set_num(int n);
    void set_denom(int d);
  
    //accessors / getters
    int get_num() const;
    int get_denom() const;

    //error handling routines
    int error() const;      //return error state
    string error_description() const;   
                            //return a descriptive error message
  
    void reset();           //resets number to 0/1 and clears error state

    //will return object whose error state is set 
    //   if one of the operands is in error. 
    friend Rational operator +(const Rational &num1, const Rational &num2) {

        int error_1 = num1.is_error();
        int error_2 = num2.is_error();

        if(error_1 == 0 && error_2 == 0) {
            
            //numerators from two refrenced rationals
            int numerator_one = num1.get_num();
            int numerator_two = num2.get_num();

            //denominators from two refrenced rationals
            int denominator_one = num1.get_denom();
            int denominator_two = num2.get_denom();

            //new numerators multiplied with the other denominators
            int new_numerator_one = numerator_one * denominator_two;
            int new_numerator_two = numerator_two * denominator_one;

            //sum of numerators with common denominator
            int sum_numerator = new_numerator_one + new_numerator_two;

            //product of two denominators
            int sum_denominator = denominator_one * denominator_two;

            return Rational(sum_numerator, sum_denominator);

        } else return Rational(1,0);
        

    }

    friend Rational operator -(const Rational &num1, const Rational &num2) {

            int error_1 = num1.is_error();
        int error_2 = num2.is_error();

        if(error_1 == 0 && error_2 == 0) {
            
            //numerators from two refrenced rationals
            int numerator_one = num1.get_num();
            int numerator_two = num2.get_num();

            //denominators from two refrenced rationals
            int denominator_one = num1.get_denom();
            int denominator_two = num2.get_denom();

            //new numerators multiplied with the other denominators
            int new_numerator_one = numerator_one * denominator_two;
            int new_numerator_two = numerator_two * denominator_one;

            //difference of numerators with common denominator
            int diff_numerator = new_numerator_one - new_numerator_two;

            //product of two denominators
            int diff_denominator = denominator_one * denominator_two;

            return Rational(diff_numerator, diff_denominator);

        }else return Rational(1,0);
        
    }

    friend Rational operator *(const Rational &num1, const Rational &num2) {

        int error_1 = num1.is_error();
        int error_2 = num2.is_error();

        if(error_1 == 0 && error_2 == 0) {
            
            //numerators from two refrenced rationals
            int numerator_one = num1.get_num();
            int numerator_two = num2.get_num();

            //denominators from two refrenced rationals
            int denominator_one = num1.get_denom();
            int denominator_two = num2.get_denom();

            //sum of numerators with common denominator
            int product_numerator = numerator_one * numerator_two;

            //product of two denominators
            int product_denominator = denominator_one * denominator_two;

            return Rational(product_numerator, product_denominator);

        }else return Rational(1,0);
        
    }

    friend Rational operator /(const Rational &num1, const Rational &num2) {

        int error_1 = num1.is_error();
        int error_2 = num2.is_error();

        int error_3 = num2.get_num() == 0 ? 1 : 0;

        if(error_1 == 0 && error_2 == 0 && error_3 == 0) {
            
            //numerators from two refrenced rationals
            int numerator_one = num1.get_num();
            int numerator_two = num2.get_num();

            //denominators from two refrenced rationals
            int denominator_one = num1.get_denom();
            int denominator_two = num2.get_denom();

            //quotient numerator
            int sum_numerator = numerator_one * denominator_two;

            //product of two denominators
            int sum_denominator = denominator_one * numerator_two;

            return Rational(sum_numerator, sum_denominator);

        }else return Rational(1,0);
        
    }
    
    //will print UNDEFINED if num is in error.
    friend ostream& operator <<(ostream &outs, const Rational &num) {
        
        int error = num.is_error();

        if(error == 1) {
            outs << "UNDEFINED";
            return outs;
        }

        outs << num.get_num() << "/" << num.get_denom() << endl;
        return outs;
    }

    friend istream& operator >>(istream &ins, Rational &num) {
        int n, d;
        ins >> n >> d;
        num = Rational(n,d);

        return ins;
    }

private:
    int is_error() const;   //checks for error cond and returns error code     
    int _n;                 //numerator
    int _d;                 //denominator
    int _error;             //error code
};

#endif