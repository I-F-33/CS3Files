#include "tk_string.h"

Tokenizer::Tokenizer(){};

Tokenizer::Tokenizer(string input) : _input(input){};

void Tokenizer::set_input(string input)
{
    _input = input;
}


Queue<Token *> Tokenizer::tokenize(string _input)
{

    string input = _input;

    int string_length = input.length();

    Queue<Token *> _output;

    for (int i = 0; i < string_length; i++)
    {
        bool implied_mult = false;

        if (input[i + 1] != 0)
        {
            if (isdigit(input[i-1]) && input[i] == 'x')
            {
                implied_mult = true;

            }
        }

        if (isdigit(input[i]))
        {
            string str = "";
            str.push_back(input[i]);
            i++;
            while(isdigit(input[i]))
            {
                str.push_back(input[i]);
                i++;
            }
            _output.push(new Integer(str));
            i--;
        }
        else if (input[i] == '*' || input[i] == '/' || input[i] == '+' || input[i] == '-' || input[i] == '^')
        {
            string str = "";
            str.push_back(input[i]);
            _output.push(new Operator(str));
        }
        else if (input[i] == '(')
        {
            _output.push(new LeftParen());
        }
        else if (input[i] == ')')
        {
            _output.push(new RightParen());
        }
        else if(input[i] == 'x')
        {
             if (implied_mult)
            {
                _output.push(new Operator("*"));
            }
            _output.push(new Function("x"));
        }
        else if (input[i] == 's' && input[i + 1] == 'i' && input[i + 2] == 'n')
        {
            _output.push(new Function("sin"));
            i += 2;
        }
        else if (input[i] == 'c' && input[i + 1] == 'o' && input[i + 2] == 's')
        {
            _output.push(new Function("cos"));
            i += 2;
        }
        else if (input[i] == 't' && input[i + 1] == 'a' && input[i + 2] == 'n')
        {
            _output.push(new Function("tan"));
            i += 2;
        }
        else if (input[i] == 'l' && input[i + 1] == 'n')
        {
            _output.push(new Function("ln"));
            i += 1;
        }
        else if (input[i] == 'l' && input[i + 1] == 'o' && input[i + 2] == 'g')
        {
            _output.push(new Function("log"));
            i += 2;
        }
        }

        return _output;
}