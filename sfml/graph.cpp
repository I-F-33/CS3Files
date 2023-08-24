#include "graph.h"

Graph::Graph()
{
}
Graph::Graph(Graph_info *info) : _info(info){};

void Graph::set_info(Graph_info *info)
{
    _info = info;
}
void Graph::update(Graph_info *info)
{
    _info = info;
}
void Graph::draw(sf::RenderWindow &window)
{
    //graph background color
    window.clear(sf::Color::White);

    //if user wants to see grid
    if (_info->get_grid())
    {
        double num_of_lines = _info->get_num_of_lines();

        // gridlines, are sized to be increments of one
        sf::VertexArray x_grid(sf::Lines, 2 * num_of_lines);
        sf::VertexArray y_grid(sf::Lines, 2 * num_of_lines);
        sf::VertexArray x_axis_grid(sf::Lines, 2);
        sf::VertexArray y_axis_grid(sf::Lines, 2);

        // main x - axis grid
        x_axis_grid[0].position = sf::Vector2f(0, SCREEN_HEIGHT / 2);
        x_axis_grid[0].color = sf::Color(0, 0, 0, 20);
        x_axis_grid[1].position = sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT / 2);
        x_axis_grid[1].color = sf::Color(0, 0, 0, 20);

        // main y - axis grid
        y_axis_grid[0].position = sf::Vector2f(WORK_PANEL / 2, 0);
        y_axis_grid[0].color = sf::Color(0, 0, 0, 20);
        y_axis_grid[1].position = sf::Vector2f(WORK_PANEL / 2, SCREEN_HEIGHT);
        y_axis_grid[1].color = sf::Color(0, 0, 0, 20);

        // target is the distance between each line
        double target = (WORK_PANEL / num_of_lines);

        // origin is the point where the x and y axis intersect
        double y_origin = _info->get_graph_origin().y;
        double y_origin2 = _info->get_graph_origin().y;

        double x_origin = _info->get_graph_origin().x;
        double x_origin2 = _info->get_graph_origin().x;

        for (int i = 0; i < 2 * num_of_lines; i += 4)
        {
            x_grid[i].color = sf::Color(0, 0, 0, 20);
            x_grid[i].position = sf::Vector2f(0, y_origin - target);
            x_grid[i + 1].color = sf::Color(0, 0, 0, 20);
            x_grid[i + 1].position = sf::Vector2f(WORK_PANEL, y_origin - target);

            x_grid[i + 2].color = sf::Color(0, 0, 0, 20);
            x_grid[i + 2].position = sf::Vector2f(0, y_origin2 + target);
            x_grid[i + 3].color = sf::Color(0, 0, 0, 20);
            x_grid[i + 3].position = sf::Vector2f(WORK_PANEL, y_origin2 + target);

            y_origin -= target;
            y_origin2 += target;

            y_grid[i].color = sf::Color(0, 0, 0, 25);
            y_grid[i].position = sf::Vector2f(x_origin - target, 0);
            y_grid[i + 1].color = sf::Color(0, 0, 0, 25);
            y_grid[i + 1].position = sf::Vector2f(x_origin - target, SCREEN_HEIGHT);

            y_grid[i + 2].color = sf::Color(0, 0, 0, 25);
            y_grid[i + 2].position = sf::Vector2f(x_origin2 + target, 0);
            y_grid[i + 3].color = sf::Color(0, 0, 0, 25);
            y_grid[i + 3].position = sf::Vector2f(x_origin2 + target, SCREEN_HEIGHT);

            x_origin -= target;
            x_origin2 += target;
        }

        window.draw(x_grid);
        window.draw(y_grid);
        window.draw(x_axis_grid);
        window.draw(y_axis_grid);
    }
    
    //if there is no equations then graph nothing
    if (_info->get_equation() != "")
    {
        _plotter.set_info(_info); // fetching screen coords
        _points = _plotter.get_points(); // fetching points

        // Graph the coordinates to the screen
        for (int i = 0; i < _points.size(); i++)
        {
            sf::CircleShape circle(1);
            circle.setFillColor(sf::Color::Red);
            circle.setPosition(_points[i]);
            window.draw(circle);
        }
    }
    // Drawing grid using two vertex arrays

    // Draw the axis using rectangle shapes
    // allows to manipulate the axis as a whole while only manipulating the origin(0,0)
    // and the interval between each point on the axis
    sf::RectangleShape y_axis(sf::Vector2f(SCREEN_HEIGHT, 1));
    sf::RectangleShape x_axis(sf::Vector2f(WORK_PANEL, 1));

    y_axis.setFillColor(sf::Color(0, 0, 255, 255));
    x_axis.setFillColor(sf::Color(0, 0, 255, 255));

    // rotate the axis to be vertical and horizontal
    y_axis.rotate(90);

    // rotate the x axis to be horizontal
    // The axis showing on screen is subject to movement due to increase/decrease in domain
    x_axis.rotate(180);

    // set the position of the axis
    y_axis.setPosition(_info->get_graph_origin().x + _info->get_axis_interval() * _info->get_origin().x, 0);
    x_axis.setPosition(WORK_PANEL, _info->get_graph_origin().y + _info->get_axis_interval() * _info->get_origin().y);

    window.draw(y_axis);
    window.draw(x_axis);
}