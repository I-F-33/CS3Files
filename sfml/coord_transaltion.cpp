#include "coord_translation.h"

Coord_translation::Coord_translation()
{
}

Coord_translation::Coord_translation(Graph_info *info)
{
    _info = info;
}

sf::Vector2f Coord_translation::translate(sf::Vector2f coords)
{
    sf::Vector2f translated_coords(0, 0);


    //(x,y) = (x_origin, y_origin)
    double x_origin = _info->get_origin().x;
    double y_origin = _info->get_origin().y;

    //scale factor[] = WORK_PANEL / (domain.y - domain.x)
    double interval = _info->get_axis_interval();

    //scale factor used to adjust cartesian coordinates to screen coordinates
    double scale = WORK_PANEL / (_info->get_domain().y - _info->get_domain().x);

    // translate the x and y values to be centered at screen
    translated_coords.x += _info->get_graph_origin().x;
    translated_coords.y += _info->get_graph_origin().y;

    // scale the x and y values
    translated_coords.x += coords.x * scale + x_origin * interval;
    translated_coords.y -= coords.y * scale - y_origin * interval;


    return translated_coords;
}