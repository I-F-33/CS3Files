#include "Graph_info.h"
#include <cmath>


Graph_info::Graph_info(const string &equation, const sf::Vector2f &windowInfo, const sf::Vector2f &graphOrigin, const sf::Vector2f &domain, int points)
{
    _equation = equation;
    window_info = windowInfo;
    graph_origin = graphOrigin;
    _domain = domain;
    _points = points;
    _origin = sf::Vector2f(0,0);
    _axis_interval = WORK_PANEL / (_domain.y - _domain.x);
    num_of_lines = _domain.y*2;
}

Graph_info::Graph_info()
{
    _equation = "";
    window_info = sf::Vector2f();
    graph_origin = sf::Vector2f();
    _domain = sf::Vector2f();
    _points = 1;
    _axis_interval = WORK_PANEL / (_domain.y - _domain.x);
    _origin = sf::Vector2f();
    _scale = 0;


}

void Graph_info::set_equation(const string &equation)
{
    _equation = equation;
}

void Graph_info::set_window_info(const sf::Vector2f &windowInfo)
{
    window_info = windowInfo;
}

void Graph_info::set_graph_origin(const sf::Vector2f &graphOrigin)
{
    graph_origin = graphOrigin;
}


void Graph_info::set_domain(const sf::Vector2f &domain)
{
    _domain = domain;
}

void Graph_info::set_points(int points)
{
    _points = points;
}


sf::Vector2f& Graph_info::get_window_info() 
{
    return window_info;
}

sf::Vector2f& Graph_info::get_graph_origin() 
{
    return graph_origin;
}

sf::Vector2f& Graph_info::get_domain() 
{
    return _domain;
}


int& Graph_info::get_points() 
{
    return _points;
}

string& Graph_info::get_equation() 
{
    return _equation;
}  

double& Graph_info::get_axis_interval() 
{
    return _axis_interval;
}

sf::Vector2f& Graph_info::get_origin() 
{
    return _origin;
}

double& Graph_info::get_scale() 
{
    return _scale;
}

int& Graph_info::get_num_of_lines() 
{
    return num_of_lines;
}

void Graph_info::set_grid(bool _grid)
{
    grid = _grid;
}

bool Graph_info::get_grid()
{
    return grid;
}

void Graph_info::set_help(bool _help)
{
    help = _help;
}

bool Graph_info::get_help()
{
    return help;
}

void Graph_info::set_new_eq_entered(bool new_eq)
{
    new_eq_entered = new_eq;
}

bool Graph_info::get_new_eq_entered()
{
    return new_eq_entered;
}