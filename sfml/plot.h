#ifndef PLOT_H
#define PLOT_H 
#include "../../includes/rpn/rpn.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/queue/MyQueue.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Graph_info.h"
#include "../../includes/token/token.h"
#include "../../includes/token/tk_string.h"
#include "coord_translation.h"

using namespace std;

class Plot {

    public:

        Plot();
        Plot(Graph_info* info);

        void set_info(Graph_info* info);

        vector<sf::Vector2f> get_points();


    private:

        Graph_info* _info;

        Tokenizer _tokenizer;

        RPN _rpn;


};





#endif // PLOT_H