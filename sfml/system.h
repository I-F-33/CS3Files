#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include "Graph_info.h"
#include <SFML/Graphics.hpp>
using namespace std;

class System
{
    public:

        System();
        System(Graph_info* info);

        void Step(int command, Graph_info* info);
        void set_info(Graph_info* info);
        void Draw(sf::RenderWindow& window);
        
    private:
        Graph_info* _info;
        sf::CircleShape shape;
        int command;
        sf::VertexArray x_axis;
        sf::VertexArray y_axis;
        int interval = 0;
        
};

#endif // SYSTEM_H
