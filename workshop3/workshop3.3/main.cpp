#include "events.h"
#include "line.h"

int main()
{

    sf::VertexArray line(sf::Lines, 2);
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Line");
    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        createLine(line, mousePosition);
        pollEvents(window, mousePosition);
        redrawFrame(window, line);
    }
}