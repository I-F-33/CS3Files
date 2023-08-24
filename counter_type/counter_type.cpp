#include "counter_type.h"
#include <iostream>
#include <iomanip>

using namespace std;

Counter_Type::Counter_Type() {
    _count = 0;
    _error = false;
}
Counter_Type::Counter_Type(int n) {  //set initial value of the counter
    _count = n;
    _error = is_error();
}        
bool Counter_Type::inc() { //increment by one

    if(_error){
        return false;
    }
    _count++;
    return true;
}                    
bool Counter_Type::dec(){
    _count--;
    _error = is_error();
    
    return _error;
}                     //decrement by one
bool Counter_Type::is_error() const{
    if(_count < 0) {
        return true;
    } else {
        return false;
    }
}          //true: the object is in error (underflow)
bool Counter_Type::reset(){
    _count = 0;
    _error = false;
    return true;
}                 //reset _count to zero and _error to false
int Counter_Type::count() const{
    return _count;
}             //retrieve the _count

