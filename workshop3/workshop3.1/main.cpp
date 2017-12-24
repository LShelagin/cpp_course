#include "events.h"
#include "ball.h"

int main()
{
    sf::RenderWindow window;
    createWindow(window);
    sf::Clock clock;

    Initials initials;
    initials.init();

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(window);
        initials.update(deltaTime);
        redrawFrame(window, initials);
    }
}