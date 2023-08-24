#include "token.h"
#include "tk_constants.h"
#include <iostream>
using namespace std;

Token::Token( TOKEN_TYPES type, string value) : _value(value), _type(type){};



