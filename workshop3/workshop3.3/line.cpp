#include "line.h"

void createLine(sf::VertexArray(&line), sf::Vector2f mousePosition)
{
    line[0].position = mousePosition;
    line[1].position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;
}