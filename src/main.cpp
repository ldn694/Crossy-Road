#include "Application.hpp"

#include <stdexcept>
#include <iostream>


int main()
{
    try
    {
        sf::ContextSettings settings;
        // settings.antialiasingLevel = 16;
        Application app(settings);
        app.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "\nEXCEPTION: " << e.what() << std::endl;
    }
}
