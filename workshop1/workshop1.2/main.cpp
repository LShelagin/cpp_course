#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float &deltaTime)
{
    const sf::Vector2f delta = mousePosition - arrow.getPosition();
    float angle = atan2(delta.y, delta.x);
    sf::Vector2f direction = (delta / hypotf(delta.x, delta.y));
    float speed = 20.f;
    if ((delta.x, delta.y) != 0.f)
    {
        arrow.setPosition(arrow.getPosition() + direction * deltaTime * speed);
    }
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    angle = toDegrees(angle);
    const float maxRotation = 90 * deltaTime;
    const float rotation = std::abs(angle - arrow.getRotation());
    if (angle != arrow.getRotation())
    {
        if (angle > arrow.getRotation())
        {
            if ((angle - 180) > arrow.getRotation())
            {
                arrow.setRotation(arrow.getRotation() - std::min(maxRotation, rotation));
            }
            else
            {
                arrow.setRotation(arrow.getRotation() + std::min(maxRotation, rotation));
            }
        }

        else
        {
            if ((angle + 180) < arrow.getRotation())
            {
                arrow.setRotation(arrow.getRotation() + std::min(maxRotation, rotation));
            }
            else
            {
                arrow.setRotation(arrow.getRotation() - std::min(maxRotation, rotation));
            }
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear();
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow ", sf::Style::Default, settings);

    sf::ConvexShape arrow;

    arrow.setPosition({400, 300});
    arrow.setPointCount(7);
    arrow.setPoint(0, {60, 0});
    arrow.setPoint(1, {20, -40});
    arrow.setPoint(2, {20, -20});
    arrow.setPoint(3, {-40, -20});
    arrow.setPoint(4, {-40, 20});
    arrow.setPoint(5, {20, 20});
    arrow.setPoint(6, {20, 40});
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0));
    arrow.setOutlineColor(sf::Color::Black);
    arrow.setOutlineThickness(3);
    arrow.setRotation(-60);

    sf::Clock clock;
    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float deltaTime = clock.restart().asSeconds();
        update(mousePosition, arrow, deltaTime);
        redrawFrame(window, arrow);
    }
}