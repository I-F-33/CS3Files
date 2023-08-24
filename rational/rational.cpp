#include "rational.h"
#include <iostream>
#include <iomanip>
using namespace std;

    Rational::Rational() {
        _n = 0;
        _d = 1;
        _error = 0;
    }
    Rational::Rational(int num, int denom) {
        _n = num;
        _d = denom;
        _error = is_error();
    }
    Rational::Rational(int w) {       //whole number
        _n = w;
        _d = 1;
        _error = 0;
    }

    //mutators / setters
    void Rational::set(int num, int denom) {
        _n = num;
        _d = denom;
    }

    void Rational::set_num(int n) {
        _n = n;
    }
    void Rational::set_denom(int d) {
        _d = d;
        _error = is_error();
    }
  
    //accessors / getters
    int Rational::get_num() const {
            return _n;
    }
    int Rational::get_denom() const {
            return _d;
    }

    //error handling routines
    int Rational::error() const {     //return error state
        return _error;
    }
    string Rational::error_description() const { //return a descriptive error message
        switch(_error) {
            case 1: 
                    return "ILLEGAL ACTION: The denominator was set to 0";
            default: 
                    return "There is no Error";
        }
    }
                           
  
    void Rational::reset() {           //resets number to 0/1 and clears error state
        _n = 0;
        _d = 1;
        _error = 0;
    }

    int Rational::is_error() const { //checks for error cond and returns error code     
        if(_d == 0) {
            return 1;
        }
        return 0;
    }  
