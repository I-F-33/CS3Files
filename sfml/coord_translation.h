#ifndef COORD_TRANSLATION_H
#define COORD_TRANSLATION_H
#include <SFML/Graphics.hpp>

#include "Graph_info.h"
#include "constants.h"
#include <iostream>

using namespace std;

class Coord_translation
{

public:
    Coord_translation();

    Coord_translation(Graph_info *info);

    sf::Vector2f translate(sf::Vector2f coords);

private:
    Graph_info *_info;
};

#endif // COORD_TRANSLATION_H