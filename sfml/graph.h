#ifndef GRAPH_H
#define GRAPH_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "plot.h"
#include "Graph_info.h"
#include "sidebar.h"
using namespace std;

class Graph
{

public:
    Graph();
    
    Graph(Graph_info *info);

    void set_info(Graph_info *info);

    void update(Graph_info *info);

    void draw(sf::RenderWindow &window);

private:
    Graph_info *_info;

    Plot _plotter;

    vector<sf::Vector2f> _points;
};

#endif // GRAPH_H