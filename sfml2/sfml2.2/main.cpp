#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
float toDegrees(float radius)
{
    return float(double(radius) * 180.0 / M_PI);
}
int main()
{
    constexpr int pointCount = 200;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Polar Rose");
    sf::Clock clock;
    sf::ConvexShape ellipse;
    ellipse.setPosition({400, 320});
    ellipse.setFillColor(sf::Color(0xFF, 0x09, 0x80));
    sf::Vector2f position = {0, 0};
    float time = 0;
    float speedY = 20.f;
    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            100 * std::sin(6 * angle) * std::sin(angle),
            100 * std::sin(6 * angle) * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        const float dt = clock.restart().asSeconds();
        time = time + dt;
        const float wavePhase = time * float(2 * M_PI);
        float x = 300 + round(200 * cos(time));
        float y = 300 + round(200 * sin(time));
        if (y + 200 >= WINDOW_HEIGHT / 2)
        {
            speedY = -speedY;
        }
        sf::Vector2f offset = {x, y};
        ellipse.setPosition(position + offset);
        window.clear();
        window.draw(ellipse);
        window.display();
    }
}