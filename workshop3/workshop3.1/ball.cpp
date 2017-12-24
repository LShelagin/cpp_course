#include "ball.h"

void Initials::init()
{
    font.loadFromFile("./arial.ttf");

    ball.setRadius(BALL_SIZE);
    ball.setPosition(position);
    ball.setFillColor(sf::Color::Yellow);
    ball.setOutlineThickness(OUTLINE_SIZE);
    ball.setOutlineColor(sf::Color::Red);

    initText.setFont(font);
    initText.setString("SLA");
    initText.setFillColor(sf::Color::Black);
    initText.setPosition(textPosition);
}

void Initials::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(ball, states);
    target.draw(initText, states);
}

void Initials::update(float deltaTime)
{
    if (position.y + 2 * BALL_SIZE > WINDOW_HEIGHT)
    {
        speed.y = -speed.y;
    }

    speed.y += accelerationOfGravity * deltaTime;
    position += speed * deltaTime;
    textPosition += speed * deltaTime;
    initText.setPosition(textPosition);
    ball.setPosition(position);
}