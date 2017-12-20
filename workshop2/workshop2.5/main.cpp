#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

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
    uniform_real_distribution<float> distribution(-200, 200);
    return distribution(generator.engine);
}

size_t getRandomIndex(PRNG &generator, size_t size)
{
    std::uniform_int_distribution<size_t> distribution(0, size - 1);
    return distribution(generator.engine);
}

Color getRandomColor(PRNG &generator, vector<Color> &colors)
{
    const unsigned colorIndex1 = getRandomIndex(generator, colors.size());
    const unsigned colorIndex2 = getRandomIndex(generator, colors.size());

    Color firstColor = colors[colorIndex1];
    Color secondColor = colors[colorIndex2];

    Color randomColor;
    randomColor.r = firstColor.r + secondColor.r;
    randomColor.g = firstColor.g + secondColor.g;
    randomColor.b = firstColor.b + secondColor.b;

    return randomColor;
}

void redrawFrame(RenderWindow &window, vector<Ball> &balls)
{
    window.clear();
    for (int i = 0; i < size(balls); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

void createNewBall(vector<Ball> &balls, vector<Color> &colors, PRNG &generator)
{
    for (int i = 0; i < size(balls); ++i)
    {
        balls[i].ball.setFillColor(getRandomColor(generator, colors));
    }
}

void initNewBall(Event::MouseButtonEvent &event, vector<Ball> &balls, const unsigned BALL_SIZE, vector<Color> &colors)
{
    Vector2f mousePosition = {float(event.x), float(event.y)};
    bool canInitBall = true;
    for (int i = 0; i < size(balls); ++i)
    {
        Vector2f delta = mousePosition - balls[i].ball.getPosition();
        float length = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
        if (length < 2 * BALL_SIZE)
        {
            canInitBall = false;
        }
    }
    if (canInitBall)
    {
        PRNG generator;
        initGenerator;
        Color color;

        Ball newBall;
        newBall.ball.setPosition(mousePosition);
        newBall.ball.setRadius(BALL_SIZE);
        float speedX = getRandomFloat(generator);
        float speedY = getRandomFloat(generator);
        newBall.speed = {speedX, speedY};
        createNewBall(balls, colors, generator);
        balls.push_back(newBall);
    }
}

void pollEvents(vector<Ball> &balls, RenderWindow &window, const float BALL_SIZE, vector<Color> &colors)
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        case Event::MouseButtonPressed:
            initNewBall(event.mouseButton, balls, BALL_SIZE, colors);
            break;
        default:
            break;
        }
    }
}

void ballCollision(vector<Ball> &balls, const unsigned BALL_SIZE)
{
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

void update(vector<Ball> &balls, const float deltaTime, const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, const unsigned BALL_SIZE)
{
    for (int i = 0; i < size(balls); ++i)
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

        ballCollision(balls, BALL_SIZE);
    }
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned BALL_SIZE = 30;

    PRNG generator;

    initGenerator(generator);

    vector<Ball> balls;
    vector<Color> colors = {
        {255, 30, 49},
        {57, 98, 175},
        {44, 79, 54},
        {214, 145, 185},
        {39, 158, 216},
        {76, 75, 245},
        {87, 65, 96}};

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(
        VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Balls ");
    Clock clock;

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(balls, window, BALL_SIZE, colors);
        update(balls, deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT, BALL_SIZE);
        redrawFrame(window, balls);
    }
}