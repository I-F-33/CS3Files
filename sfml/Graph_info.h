#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "constants.h"
#include <vector>
using namespace std;

class Graph_info
{

public:
    Graph_info();

    Graph_info(const string &equation, const sf::Vector2f &windowInfo, const sf::Vector2f &graphOrigin, const sf::Vector2f &domain, int points);

    void set_equation(const string &equation);

    void set_window_info(const sf::Vector2f &windowInfo);

    void set_graph_origin(const sf::Vector2f &graphOrigin);

    void set_scale(const sf::Vector2f &scale);

    void set_domain(const sf::Vector2f &domain);

    void set_points(int points);

    void set_range(const sf::Vector2f &range);

    sf::Vector2f& get_window_info() ;

    sf::Vector2f& get_graph_origin() ;

    sf::Vector2f& get_origin() ;

    sf::Vector2f& get_domain() ;

    int& get_points() ;

    string& get_equation() ;

    double& get_axis_interval() ;

    double& get_scale() ;

    int& get_num_of_lines() ;

    void set_grid(bool want_grid);

    bool get_grid();

    void set_help(bool want_help);

    bool get_help();

    void set_new_eq_entered(bool new_eq);

    bool get_new_eq_entered();

private:
    string _equation;

    sf::Vector2f window_info;

    sf::Vector2f graph_origin;

    sf::Vector2f _domain;

    sf::Vector2f _origin;

    int _points;

    double _axis_interval;

    double _scale;

    int num_of_lines;

    bool grid = true;

    bool help = false;

    bool new_eq_entered = false;
};

#endif // GRAPH_INFO_H