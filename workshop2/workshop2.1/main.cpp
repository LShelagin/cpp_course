#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

using namespace sf;
using namespace std;

struct Ball
{
    CircleShape ball;
    Vector2f speed;
};

void redrawFrame(RenderWindow &window, Ball (&balls)[5])
{
    window.clear();
    for (int i = 0; i < size(balls); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

void update(Ball (&balls)[5], const float deltaTime, const unsigned WINDOW_WIDTH = 800, const unsigned WINDOW_HEIGHT = 600, const unsigned BALL_SIZE = 30)
{
    for (int i = 0; i < size(balls); i++)
    {
        Vector2f position = balls[i].ball.getPosition();
        position += balls[i].speed * deltaTime;

        if (position.x + 2 * BALL_SIZE >= WINDOW_WIDTH)
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if (position.x <= 0)
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if (position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT)
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if (position.y <= 0)
        {
            balls[i].speed.y = -balls[i].speed.y;
        }

        balls[i].ball.setPosition(position);
    }
}

int main()
{
    Clock clock;

    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned BALL_SIZE = 30;

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Balls ", Style::Default, settings);

    Ball balls[5];
    for (int i = 0; i < size(balls); ++i)
    {
        balls[i].ball.setPosition(75.f * i, 100.f);
        balls[i].ball.setFillColor(sf::Color(50 * i, 255, 100));
        balls[i].speed = {50.f * i, 100.f};
        balls[i].ball.setRadius(BALL_SIZE);
    }

    while (window.isOpen())
    {
        Event event;
        const float deltaTime = clock.restart().asSeconds();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        update(balls, deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT, BALL_SIZE);
        redrawFrame(window, balls);
    }
}