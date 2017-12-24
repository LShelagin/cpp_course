#include "events.h"
#include "ball.h"

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void redrawFrame(sf::RenderWindow &window, Initials &initials)
{
    window.clear();
    window.draw(initials);
    window.display();
}

void createWindow(sf::RenderWindow &window)
{
    sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    const std::string title = "Initials";
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(videoMode, title, sf::Style::Default, settings);
}