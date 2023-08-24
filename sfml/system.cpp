#include "system.h"

System::System()
{
    // ctor
}

System::System(Graph_info *info) : _info(info)
{
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command, Graph_info *info)
{

    _info = info;
    if (command == 1) // Zooooomin in
    {

        _info->get_domain().x++;
        _info->get_domain().y--;

        _info->get_num_of_lines()-=2;
    }
    if (command == 2) // Zoooooomin out
    {

        _info->get_domain().x--;
        _info->get_domain().y++;

        _info->get_num_of_lines()+=2;

    }
    if (command == 3) // Reset the domain
    {

        _info->get_origin().x = 0;
        _info->get_origin().y = 0;

        _info->get_domain().x = -10;
        _info->get_domain().y = 10;

        _info->get_num_of_lines() = 20;
    
    }
    if (command == 4) // Panning up the graph
    {
       double domain_scale = WORK_PANEL/_info->get_num_of_lines();;

        _info->get_origin().y--;
    }
    if (command == 5) // Panning down the graph
    {
       double domain_scale = WORK_PANEL/_info->get_num_of_lines();;

        _info->get_origin().y++;
    }
    if (command == 6) // Panning left the graph
    {

        double domain_scale = (_info->get_domain().y - _info->get_domain().x) * 0.05;
        

        _info->get_domain().x-=domain_scale;
        _info->get_domain().y-=domain_scale;

        _info->get_origin().x++;
    }
    if (command == 7) // Panning right the graph
    {

        double domain_scale = (_info->get_domain().y - _info->get_domain().x) * 0.05;

        _info->get_domain().x+=domain_scale;
        _info->get_domain().y+=domain_scale;

        _info->get_origin().x--;
    }
    if(command == 8)
    {
        _info->get_equation() = "";
        _info->get_origin().x = 0;
        _info->get_origin().y = 0;

        _info->get_domain().x = -10;
        _info->get_domain().y = 10;

        _info->get_num_of_lines() = 20;

    }
}

