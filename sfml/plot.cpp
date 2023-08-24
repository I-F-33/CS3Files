#include "plot.h"
#include <cmath>

Plot::Plot()
{
    // ctor
}
Plot::Plot(Graph_info *info) : _info(info){};

void Plot::set_info(Graph_info *info)
{
    _info = info;

    // tokenize the equation input by user
    Queue<Token *> infix = _tokenizer.tokenize(_info->get_equation());

    // pass tokenized expression into shunting yard
    ShuntingYard sy(infix);
    Queue<Token *> postfix = sy.postfix();

    // pass postfix expression into rpn
    _rpn.set_input(postfix);
}

vector<sf::Vector2f> Plot::get_points()
{
    // yvalues to be plotted: [equation outputs given domain]
    double y_value = 0;

    vector<sf::Vector2f> coordinates;

    // translate the graph coordinates
    Coord_translation translator(_info);

    // will evaluate equation at each x and receive y_value
    // then will push pair of coordinates into vector
    for (double x_value = _info->get_domain().x; x_value <= _info->get_domain().y; x_value += 0.005)
    {
        coordinates.push_back(translator.translate(sf::Vector2f(x_value, _rpn(x_value))));
    }


    return coordinates;
}
