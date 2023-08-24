#include "sidebar.h"
#include "constants.h"
Sidebar::Sidebar()
{
}

void Sidebar::set_info(Graph_info *info)
{
    _info = info;
}

Sidebar::Sidebar(float left, float width) : _left(left), _width(width)
{
    cout << "Sidebar CTOR: TOP" << endl;
    items.reserve(50);

    // set up the sidebar rectangle:
    rect.setFillColor(sf::Color(255, 100, 100)); // light red
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout << "Sidebar CTOR: about to load font." << endl;

    // text box for user to enter equation
    text_box.setPosition(sf::Vector2f(left + 20, 50));
    text_box.setSize(sf::Vector2f(250, 80));
    text_box.setFillColor(sf::Color::White);
    text_box.setOutlineThickness(2);
    text_box.setOutlineColor(sf::Color::Black);

    // graph button text for user to graph equation
    graph_button_text = sf::Text("GRAPH", font, 20);
    graph_button_text.setFillColor(sf::Color::Black);
    graph_button_text.setStyle(sf::Text::Bold);
    graph_button_text.setPosition(sf::Vector2f(left + 100, 157));

    // graph button for user to graph equation
    graph_button.setOutlineThickness(2);
    graph_button.setOutlineColor(sf::Color::Black);
    graph_button.setPosition(sf::Vector2f(left + 75, 150));
    graph_button.setSize(sf::Vector2f(130, 40));
    graph_button.setFillColor(sf::Color::White);

    // grid button for user to turn grid on or off
    grid_box.setOutlineColor(sf::Color::Black);
    grid_box.setOutlineThickness(2);
    grid_box.setPosition(sf::Vector2f(left + 10, 195));
    grid_box.setSize(sf::Vector2f(85, 40));
    grid_box.setFillColor(sf::Color::White);

    // grid button text
    grid_txt = sf::Text("GRID", font, 20);
    grid_txt.setFillColor(sf::Color::Black);
    grid_txt.setStyle(sf::Text::Bold);
    grid_txt.setPosition(sf::Vector2f(left + 25, 202));

    // help button for user to turn help on or off
    help_box.setOutlineColor(sf::Color::Black);
    help_box.setOutlineThickness(2);
    help_box.setPosition(sf::Vector2f(left + grid_box.getGlobalBounds().width + 10, 195));
    help_box.setSize(sf::Vector2f(85, 40));
    help_box.setFillColor(sf::Color::White);

    // help button text
    help_txt = sf::Text("HELP", font, 20);
    help_txt.setFillColor(sf::Color::Black);
    help_txt.setStyle(sf::Text::Bold);
    help_txt.setPosition(sf::Vector2f(left + grid_box.getGlobalBounds().width + 25, 202));

    // clear screen button for user to clear screen
    clr_scr_box.setOutlineColor(sf::Color::Black);
    clr_scr_box.setOutlineThickness(2);
    clr_scr_box.setPosition(sf::Vector2f(left + help_box.getGlobalBounds().width + 100, 195));
    clr_scr_box.setSize(sf::Vector2f(85, 40));
    clr_scr_box.setFillColor(sf::Color::White);

    clr_scr_txt = sf::Text("CLEAR", font, 20);
    clr_scr_txt.setFillColor(sf::Color::Black);
    clr_scr_txt.setStyle(sf::Text::Bold);
    clr_scr_txt.setPosition(sf::Vector2f(left + help_box.getGlobalBounds().width + 105, 202));

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // the font file must be in the "working directory"
    //  check projects->run->working directory
    //       [Make sure it's not pointing to the app file]

    if (!font.loadFromFile("../../Roboto-Thin.ttf"))
    {
        cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout << "Sidebar CTOR: loaded font." << endl;

    cout << "Sidebar CTOR: Text object initialized." << endl;

    // text settings
    sb_text.setFont(font);
    sb_text.setCharacterSize(20);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setFillColor(sf::Color::Yellow);

    ////this is how you would position text on screen:
    // sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-sb_text.getLocalBounds().height-5));

    items.push_back("");
    // Fill the items vector with empty strings so that we can use [] to read them:
    for (int i = 0; i < 30; i++)
    {
        items.push_back("");
    }
    cout << "Sidebar: CTOR: Exit." << endl;
}

void Sidebar::draw(sf::RenderWindow &window)
{
    const double VERTICAL_LINE_SPACING = 10.0;
    const double LEFT_MARGIN = 0;

    // draw sidebar
    window.draw(rect);
    window.draw(text_box);
    window.draw(graph_button);
    window.draw(graph_button_text);
    window.draw(grid_box);
    window.draw(grid_txt);
    window.draw(help_box);
    window.draw(help_txt);
    window.draw(clr_scr_box);
    window.draw(clr_scr_txt);

    float height = 250;
    float sb_height = 260;

    sf::RectangleShape eq_box;

    // open file to fetch equations
    ifstream inFile("equ.txt");

    if (inFile.is_open())
    {
        for (int i = 2; i < 25; i++)
        {
            getline(inFile, items[i]);
        }

        inFile.close();
    }

    for (vector<string>::iterator it = items.begin(); it != items.end(); it++)
    {
        bool blank = false;
        if (it->length() == 0)
        {
            // do not draw these empty rows
            blank = true;
            sb_text.setString("BLANK");
        }
        else
        {
            sb_text.setString(it->c_str());
            eq_box.setPosition(sf::Vector2f(_left + 30, height));
            eq_box.setSize(sf::Vector2f(210, 60));
            eq_box.setFillColor(sf::Color::White);
            eq_box.setOutlineThickness(2);
            eq_box.setOutlineColor(sf::Color::Black);

            sb_text.setPosition(sf::Vector2f(_left + 80, sb_height));
            sb_text.setFillColor(sf::Color::Black);
        }

        height += eq_box.getLocalBounds().height + VERTICAL_LINE_SPACING;
        sb_height += eq_box.getGlobalBounds().height + VERTICAL_LINE_SPACING;

        if (!blank)
        {
            //if new equation entered then add to vector
            if (it == items.begin() && _info->get_new_eq_entered())
            {
                text_boxes.push_back(eq_box);
                text_box_text.push_back(sb_text);
                cout << "new equation entered" << sb_text.getString().toAnsiString() << endl;
                _info->set_new_eq_entered(false);
            }
            text_boxes.push_back(eq_box);
            text_box_text.push_back(sb_text);
            window.draw(eq_box);
            window.draw(sb_text);
        }
    }
}

string &Sidebar::operator[](int index)
{
    return items[index];
}

sf::RectangleShape &Sidebar::get_rect()
{
    return rect;
}

bool Sidebar::save_equation(string equation)
{
    // open a running file to save the equations

    // create file to save equations
    ofstream outFile("equ.txt");

    if (outFile.fail())
    {
        cout << "Error opening file." << endl;
        return false;
    }

    // update items array to make space for new equation
    for (int i = 25; i > 1; i--)
    {
        items[i + 1] = items[i];
    }

    // 4 and beyond is equation
    items[2] = equation;

    for (int i = 2; i < 25; i++)
    {
        // print the equations to the file
        // prints to screen
        outFile << items[i] << endl;
    }

    outFile.close();

    return true;
}

sf::RectangleShape &Sidebar::get_text_box()
{
    return text_box;
}

vector<sf::RectangleShape> Sidebar::get_text_boxes()
{
    return text_boxes;
}

sf::RectangleShape &Sidebar::get_graph_button()
{
    return graph_button;
}

vector<sf::Text> Sidebar::get_text_box_text()
{
    return text_box_text;
}

sf::RectangleShape &Sidebar::get_grid_box()
{
    return grid_box;
}

sf::Text &Sidebar::get_grid_txt()
{
    return grid_txt;
}

sf::RectangleShape &Sidebar::get_help_box()
{
    return help_box;
}

sf::Text &Sidebar::get_help_txt()
{
    return help_txt;
}

sf::Text &Sidebar::get_sb_text()
{
    return sb_text;
}

sf::RectangleShape &Sidebar::get_clr_scr_box()
{
    return clr_scr_box;
}