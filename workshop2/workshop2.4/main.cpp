#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <cassert>

using namespace sf;
using namespace std;

struct Ball
{
    CircleShape ball;
    Vector2f speed;
    Vector2f position;
};

struct PRNG
{
    mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    random_device device;
    generator.engine.seed(device());
}

float getRandomFloat(PRNG &generator)
{
    uniform_real_distribution<float> distribution(100, 200);
    return distribution(generator.engine);
}

unsigned getRandomColor(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 255);
    return distribution(generator.engine);
}

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
        balls[i].position = balls[i].ball.getPosition();
        balls[i].position += balls[i].speed * deltaTime;

        if (balls[i].position.x + 2 * BALL_SIZE >= WINDOW_WIDTH)
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if (balls[i].position.x <= 0)
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if (balls[i].position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT)
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if (balls[i].position.y <= 0)
        {
            balls[i].speed.y = -balls[i].speed.y;
        }

        balls[i].ball.setPosition(balls[i].position);
    }
    for (int fi = 0; fi < size(balls); ++fi)
    {
        for (int si = fi + 1; si < size(balls); ++si)
        {
            Vector2f deltaPosition = balls[si].position - balls[fi].position;
            Vector2f deltaSpeed = balls[si].speed - balls[fi].speed;
            float distance = sqrt(pow(deltaPosition.x, 2) + pow(deltaPosition.y, 2));
            float changeSpeed = ((deltaPosition.x * deltaSpeed.x) + (deltaPosition.y * deltaSpeed.y)) / pow(distance, 2);
            if (distance <= (2 * BALL_SIZE))
            {
                balls[fi].speed = balls[fi].speed + changeSpeed * deltaPosition;
                balls[si].speed = balls[si].speed - changeSpeed * deltaPosition;
            }
        }
    }
}

int main()
{
    PRNG generator;
    initGenerator;
    Clock clock;
    Color color;

    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned BALL_SIZE = 30;

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Balls ");

    Ball balls[5];
    for (int i = 0; i < size(balls); ++i)
    {
        balls[i].ball.setPosition(120.f * i + 30, 100.f * i);
        float red = getRandomColor(generator);
        float green = getRandomColor(generator);
        float blue = getRandomColor(generator);
        float speedX = getRandomFloat(generator);
        float speedY = getRandomFloat(generator);
        balls[i].ball.setFillColor(sf::Color(red, green, blue));
        balls[i].speed = {speedX, speedY};
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