#include "animate.h"
#include "constants.h"
#include <iostream>
using namespace std;
#include "system.h"

animate::animate() : sidebar(WORK_PANEL, SIDE_BAR)
{

    cout << "animate CTOR: TOP" << endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graphing Calculator");

    // VideoMode class has functions to detect screen size etc.
    // RenderWindow constructor has a third argumnet to set style
    // of the window: resize, fullscreen etc.

    // System will be implemented to manage a vector of objects to be animated.
    //   at that point, the constructor of the System class will take a vector
    //   of objects created by the animate object.
    //   animate will

    // Instantiating the graph info
    // This instance will be used by the entire project to maipulate elements of the graph
    // and allow for features such as zooming and panning
    _info = new Graph_info("", sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT), sf::Vector2f(WORK_PANEL / 2, SCREEN_HEIGHT / 2), sf::Vector2f(-10, 10), 25000);
    _system = System(_info);
    sidebar.set_info(_info);
    window.setFramerateLimit(60);

    mouseIn = true;

    // mousePoint red dot:
    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);
    mousePoint.setOutlineThickness(2);
    // The entered equation will contain the equation that the user enters
    // This is equation is a string and will be used to create the tokens necessary for the shunting yard algorithm
    entered_equation = sf::Text("", font);
    entered_equation.setCharacterSize(20);
    entered_equation.setStyle(sf::Text::Italic);
    entered_equation.setFillColor(sf::Color::Black);
    entered_equation.setPosition(sf::Vector2f(WORK_PANEL + 30, 60));

    cout << "Geme CTOR. preparing to load the font." << endl;
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder

    // font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("../../arial.ttf"))
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    // Instructions for the user
    // will float above lower left corner
    myTextLabel = sf::Text("{Arrow Keys to pan} \n Press [Z] or Scroll Up to Zoom in \n Press [X] or Scroll Down to Zoom Out \n Press [R] to Reset \n Press [F] to insert new function \n Press [C] to clear screen \n [ESC] to Exit", font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Italic);
    myTextLabel.setFillColor(sf::Color::Red);
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - myTextLabel.getLocalBounds().height - 5));

    cout << "animate instantiated successfully." << endl;
}

void animate::Draw()
{

    // Drawing origins and axes for the graph
    graph.set_info(_info);
    graph.draw(window);

    if (mouseIn)
    {
        window.draw(mousePoint);
    }

    // Draw the sidebar
    sidebar.draw(window);

    // assist the iser with input, direct them to area of screen where they can enter the equation
    sf::Text enterEq = sf::Text("Enter f(x): ", font);
    enterEq.setCharacterSize(20);
    enterEq.setStyle(sf::Text::Bold);
    enterEq.setFillColor(sf::Color::Black);
    enterEq.setPosition(sf::Vector2f(WORK_PANEL + 20, 10));
    window.draw(enterEq);

    window.draw(entered_equation);

    // if user wants help show user the keypad shortcuts
    if (_info->get_help())
    {
        window.draw(myTextLabel);
    }
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update()
{
    // cause changes to the data for the next frame
    _system.Step(command, _info);
    command = 0;
    if (mouseIn)
    {
        // mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5,
                               sf::Mouse::getPosition(window).y - 5);

        // mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);

        // when user hovers over graph, help and grid button is turns yellow
        sidebar.get_graph_button().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ? sidebar.get_graph_button().setFillColor(sf::Color::Yellow) : sidebar.get_graph_button().setFillColor(sf::Color::White);

        sidebar.get_grid_box().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ? sidebar.get_grid_box().setFillColor(sf::Color::Yellow) : sidebar.get_grid_box().setFillColor(sf::Color::White);

        sidebar.get_help_box().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ? sidebar.get_help_box().setFillColor(sf::Color::Yellow) : sidebar.get_help_box().setFillColor(sf::Color::White);

        sidebar.get_clr_scr_box().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) ? sidebar.get_clr_scr_box().setFillColor(sf::Color::Yellow) : sidebar.get_clr_scr_box().setFillColor(sf::Color::White);
    }
}

void animate::render()
{
    window.clear();
    Draw();
    window.display();
}

void animate::processEvents()
{

    // Event processing
    // depending on the user input there will be different commands sent to the system
    // the system will then update the graph accordingly

    sf::Event event;
    float mouseX, mouseY;
    while (window.pollEvent(event)) // or waitEvent
    {
        // check the type of the event...
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:

            // if user clicks on graph text box it allows user to enter the equation
            if (sidebar.get_text_box().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
            {
                sidebar[SB_KEY_PRESSED] = "f: ENTER EQ";
                text_entered = true;
                equation = "";
                entered_equation.setString("");
            }

            // if user clicks on the graph button it graphs the equation
            if (sidebar.get_graph_button().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
            {
                sidebar[SB_KEY_PRESSED] = "f: GRAPH";
                if (!equation.empty())
                {
                    _info->set_equation(equation);
                    sidebar.save_equation(equation);
                    equation = "";
                    _info->set_new_eq_entered(true);
                }

                text_entered = false;
            }

            // if user clicks the grid button it either turns it off or on
            if (sidebar.get_grid_box().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
            {
                _info->get_grid() ? _info->set_grid(false) : _info->set_grid(true);
            }

            // if user clicks on the help button it either turns it off or on
            if (sidebar.get_help_box().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
            {
                _info->get_help() ? _info->set_help(false) : _info->set_help(true);
            }

            if (sidebar.get_clr_scr_box().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
            {
                command = 8;
            }
            
            for (int i = 0; i < 10; i++)
            {
                if (sidebar.get_text_boxes()[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
                {
                    _info->set_equation(sidebar.get_text_box_text()[i].getString().toAnsiString());
                }
            }
                break;
            // mouse wheel scrolled
            // allows user to zoom in and out with mouse scroll
            case sf::Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.delta > 0)
                {
                    command = 1;
                }
                else if (event.mouseWheelScroll.delta < 0)
                {
                    command = 2;
                }
                break;
            case sf::Event::TextEntered:
                if (event.text.unicode == 102)
                {

                    sidebar[SB_KEY_PRESSED] = "f: ENTER EQ";
                    text_entered = true;
                    equation = "";
                    entered_equation.setString("Enter f(x): ");
                }
                else if (event.text.unicode == 8)
                {
                    if (equation.size() > 0)
                    {
                        equation.pop_back();
                    }
                }
                else if (text_entered)
                {
                    equation += event.text.unicode;
                }
                entered_equation.setString(equation);
                break;
            // key pressed
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    if (!text_entered)
                    {
                        sidebar[SB_KEY_PRESSED] = "Get Me Out of Here!";
                        window.close();
                    }
                    break;
                case sf::Keyboard::Up:
                    if (!text_entered)
                    {
                        sidebar[SB_KEY_PRESSED] = "UP WE GO";
                        command = 4;
                    }
                    break;
                case sf::Keyboard::Down:
                    if (!text_entered)
                    {
                        sidebar[SB_KEY_PRESSED] = "DOWN WE GO";
                        command = 5;
                    }
                    break;
                case sf::Keyboard::Left:
                    if (!text_entered)
                    {
                        sidebar[SB_KEY_PRESSED] = "LEFT WE GO";
                        command = 6;
                    }
                    break;
                case sf::Keyboard::Right:
                    if (!text_entered)
                    {
                        sidebar[SB_KEY_PRESSED] = "RIGHT WE GO";
                        command = 7;
                    }
                    break;
                case sf::Keyboard::Z:
                    if (!text_entered)
                    {
                        sidebar[SB_KEY_PRESSED] = "MAGNIFY";
                        command = 1;
                    }
                    break;
                case sf::Keyboard::X:
                    if (!text_entered)
                    {
                        sidebar[SB_KEY_PRESSED] = "MINIFY";
                        command = 2;
                    }
                    break;
                case sf::Keyboard::R:
                    if (!text_entered)
                    {
                        sidebar[SB_KEY_PRESSED] = "RESET";
                        command = 3;
                    }
                    break;
                case sf::Keyboard::C:
                    if (!text_entered)
                    {
                        sidebar[SB_KEY_PRESSED] = "CLEAR SCREEN";
                        command = 8;
                    }
                    break;
                case sf::Keyboard::Enter:
                    sidebar[SB_KEY_PRESSED] = "ENTER";
                    if (!equation.empty())
                    {
                        _info->set_equation(equation);
                        sidebar.save_equation(equation);
                        equation = "";
                        _info->set_new_eq_entered(true);
                    }
                    text_entered = false;
                    break;
                    break;
                }
            case sf::Event::MouseEntered:
                mouseIn = true;
                break;

            case sf::Event::MouseLeft:
                mouseIn = false;
                break;

            case sf::Event::MouseMoved:
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
                break;
            default:
                break;
            }
        }
    }
    void animate::run()
    {
        while (window.isOpen())
        {
            processEvents();
            update();
            render(); // clear/draw/display
        }
        cout << endl
             << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
    }

    string mouse_pos_string(sf::RenderWindow & window)
    {
        return "(" +
               to_string(sf::Mouse::getPosition(window).x) +
               ", " +
               to_string(sf::Mouse::getPosition(window).y) +
               ")";
    }
