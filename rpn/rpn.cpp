#include "rpn.h"

RPN::RPN()
{
}

RPN::RPN(Queue<Token *> &tokens) : _tokens(tokens){};

void RPN::set_input(Queue<Token *> &tokens)
{
    _tokens = tokens;
}

double RPN::operator()(double x)
{
    Stack<Token *> stack;
    Queue<Token *> result_queue;

    while (!_tokens.empty())
    {
        Token *token = _tokens.pop(); 

        cout << *token << " ";

        if (token->TypeOf() == INTEGER)
        {
            stack.push(token);
        }
        else if (token->TypeOf() == OPERATOR)
        {
            cout << static_cast<Operator*>(token)->get_prec() << endl;
            if(static_cast<Operator*>(token)->get_prec() == 4)
            {
                stack.push(new Integer(x));
            }
            
            Token *rightvar = stack.pop();
            Token *leftvar = stack.pop();

            Token *result = static_cast<Operator *>(token)->eval(leftvar, rightvar);

            stack.push(result);
        }
        else if (token->TypeOf() == FUNCTION)
        {
            if (static_cast<Function *>(token)->get_function() == "X")
            {
                stack.push(new Integer(x));
            }
            /*  else if (static_cast<Function *>(token)->get_function() == "sin")
             {
                 stack.push(new Integer(sin(static_cast<Integer *>(token)->get_value())));
             }
             else if(static_cast<Function *>(token)->get_function() == "cos")
             {
                 stack.push(new Integer(cos(static_cast<Integer *>(token)->get_value())));
             } */
        }
    }

    return static_cast<Integer *>(stack.pop())->get_value();
}