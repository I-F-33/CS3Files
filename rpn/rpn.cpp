#include "rpn.h"

RPN::RPN()
{
}

RPN::RPN(Queue<Token *> &tokens) : _tokens(tokens){};

void RPN::set_input(Queue<Token *> &tokens)
{
    _tokens = tokens;
}

float RPN::operator()(double x)
{
    Stack<Token *> stack;
    Queue<Token *> result_queue;

    Queue<Token *> tokens = _tokens;

    while (!tokens.empty())
    {
        Token *token = tokens.pop();

        if (token->TypeOf() == INTEGER)
        {
            stack.push(token);
        }
        else if (token->TypeOf() == FUNCTION)
        {
            if (static_cast<Function *>(token)->get_function() == "x")
            {
                stack.push(new Integer(x));
            }
            else if (static_cast<Function *>(token)->get_function() == "sin")
            {
            
                    stack.push(new Integer(sinf(static_cast<Integer *>(stack.pop())->get_value())));
                
            }
            else if (static_cast<Function *>(token)->get_function() == "cos")
            {
                    stack.push(new Integer(cosf(static_cast<Integer *>(stack.pop())->get_value())));
                
            }
            else if (static_cast<Function *>(token)->get_function() == "tan")
            {
            
                    stack.push(new Integer(tanf(static_cast<Integer *>(stack.pop())->get_value())));
                
            }
            else if (static_cast<Function *>(token)->get_function() == "log")
            {
                    stack.push(new Integer(log10f(static_cast<Integer *>(stack.pop())->get_value())));
                
            }
            else if (static_cast<Function *>(token)->get_function() == "ln")
            {
              
                    stack.push(new Integer(logf(static_cast<Integer *>(stack.pop())->get_value())));
                
            }
            else if (static_cast<Function *>(token)->get_function() == "sqrt")
            {
           
                    stack.push(new Integer(sqrtf(static_cast<Integer *>(stack.pop())->get_value())));
                
            }
        }
        else if (token->TypeOf() == OPERATOR)
        {
            Token *rightvar = stack.pop();
            Token *leftvar = stack.pop();

            Token *result = static_cast<Operator *>(token)->eval(leftvar, rightvar);

            stack.push(result);
        }
    }
    return static_cast<Integer *>(stack.pop())->get_value();
    
}

void RPN::set_tokens(Queue<Token *> tokens)
{
    _tokens = tokens;

}