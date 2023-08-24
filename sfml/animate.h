#ifndef ANIMATE_H
#define ANIMATE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Graph_info.h"
#include "system.h"
#include "sidebar.h"
#include "graph.h"

#include <iostream>
using namespace std;

class animate
{
public:
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();

    void save_equation();
    void fetch_equation();

    void fill_sidebar();

private:
    Graph_info* _info;

    sf::RenderWindow window;
    sf::CircleShape mousePoint; // The little red dot
    sf::Font font;              // font to draw on main screen
    sf::Text myTextLabel;       // text to draw on main screen
    sf::Text entered_equation;

    System _system;             // The system that will be animated
    Sidebar sidebar;            // rectangular message sidebar
    Graph graph;

    bool text_entered = false;          // user is entering text
    int command;                // command to send to system
    bool mouseIn;               // mouse is in the screen
    string equation;
};

string mouse_pos_string(sf::RenderWindow &window);

#endif // GAME_H
