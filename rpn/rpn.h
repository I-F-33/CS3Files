#ifndef RPN_H
#define RPN_H
#include "../../includes/token/token.h"
#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/rightparen.h"
#include "../../includes/token/function.h"

using namespace std;

class RPN
{
    public:

        RPN();

        RPN(Queue<Token*> &tokens);

        void set_input(Queue<Token*> &tokens);

        double operator()(double x = 0);

    private:
    
            Queue<Token*> _tokens;
};
#endif // RPN_H