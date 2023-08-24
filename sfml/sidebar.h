#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <vector>
#include <ostream>
#include <fstream>
#include "Graph_info.h"
#include "constants.h"

using namespace std;

class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow &window);
    string &operator[](int index);
    sf::RectangleShape &get_rect();

    bool save_equation(string equation);
    int fetch_index(sf::RenderWindow &window);

    void set_info(Graph_info *info);

    sf::RectangleShape &get_text_box();

    vector<sf::RectangleShape> get_text_boxes();

    sf::RectangleShape &get_graph_button();

    vector<sf::Text> get_text_box_text();

    sf::RectangleShape &get_grid_box();

    sf::Text &get_grid_txt();

    sf::RectangleShape &get_help_box();

    sf::Text &get_help_txt();

    sf::Text &get_sb_text();

    sf::RectangleShape &get_clr_scr_box();

private:
    sf::RectangleShape rect; // sidebar rectangle
    vector<string> items;    // strings to place on the sidebar
    sf::Font font;           // used to draw text

    sf::Text sb_text; // used to draw strings on the window object
    sf::RectangleShape text_box;

    sf::Text graph_button_text;
    sf::RectangleShape graph_button;

    sf::Text grid_txt;
    sf::RectangleShape grid_box;

    sf::Text help_txt;
    sf::RectangleShape help_box;

    sf::Text clr_scr_txt;
    sf::RectangleShape clr_scr_box;

    vector<sf::RectangleShape> text_boxes;
    vector<sf::Text> text_box_text;

    

    string equation;

    float _left;
    float _width;

    Graph_info *_info;
};

#endif // SIDEBAR_H
