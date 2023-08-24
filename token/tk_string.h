#ifndef TK_String_H
#define TK_String_H
#include <string>
#include <vector>
#include <iostream>
#include "../../includes/token/token.h"
#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/rpn/rpn.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/function.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/rightparen.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/tk_constants.h"
using namespace std;

class Tokenizer
{
public:
    Tokenizer();

    Tokenizer(string input);

    void set_input(string input);

    Queue<Token *> tokenize(string input);

private:
    string _input;
};

#endif // TOKENIZER_H