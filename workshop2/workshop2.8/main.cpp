#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <cmath>
#include <cassert>
#include <random>

using namespace sf;
using namespace std;

struct Ball
{
    CircleShape ball;
    Vector2f speed;
    Vector2f position;
    float timeOfDeath = 10;
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

bool areCloseAbsolute(float firstArgument, float secondArgument, float tolerance)
{
    return std::abs(firstArgument - secondArgument) < tolerance;
}

bool areCloseRelative(float firstArgument, float secondArgument, float tolerance)
{
    return std::abs((firstArgument - secondArgument) / secondArgument) < tolerance;
}

bool areFuzzyEqual(float firstArgument, float secondArgument, float tolerance)
{
    if (std::abs(secondArgument) > 1.f)
    {
        return areCloseRelative(firstArgument, secondArgument, tolerance);
    }
    return areCloseAbsolute(firstArgument, secondArgument, tolerance);
}

float getImpuls(vector<Ball> &balls, const float BALL_SIZE)
{
    float impuls;
    for (int i = 1; i < size(balls); ++i)
    {
        impuls += pow(BALL_SIZE, 3) * sqrt(pow(balls[i].speed.x, 2) + pow(balls[i].speed.y, 2));
    }
    return impuls;
}

float getEnergy(vector<Ball> &balls, const float BALL_SIZE)
{
    float energy;
    for (int i = 1; i < size(balls); ++i)
    {
        energy += pow(BALL_SIZE, 3) * (pow(balls[i].speed.x, 2) + pow(balls[i].speed.y, 2));
    }
    return energy;
}

bool removeBalls(Ball ball)
{
    return (ball.timeOfDeath <= 0);
}

removeDeathBalls(vector<Ball> &balls)
{
    auto iterator = remove_if(balls.begin(), balls.end(), removeBalls);
    balls.erase(iterator, balls.end());
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
    Vector2f mousePosition = {float(event.x) - 15, float(event.y) - 15};
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
        createNewBall(balls, colors, generator);
        newBall.ball.setPosition(mousePosition);
        newBall.ball.setRadius(BALL_SIZE);
        float speedX = getRandomFloat(generator);
        float speedY = getRandomFloat(generator);
        newBall.speed = {speedX, speedY};
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
    float tolerance = 0.1f;
    float oldEnergy = getEnergy(balls, BALL_SIZE);
    float oldImpuls = getImpuls(balls, BALL_SIZE);
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
    float newEnergy = getEnergy(balls, BALL_SIZE);
    float newImpuls = getImpuls(balls, BALL_SIZE);
    assert(areFuzzyEqual(newEnergy, oldEnergy, tolerance));
    assert(areFuzzyEqual(newImpuls, oldImpuls, tolerance));
}

void update(vector<Ball> &balls, const float deltaTime, const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, const unsigned BALL_SIZE)
{
    removeDeathBalls(balls);
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
        balls[i].timeOfDeath -= deltaTime;
    }

    ballCollision(balls, BALL_SIZE);
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned BALL_SIZE = 30;
    constexpr unsigned numberOfInterval = 10;

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
        const float deltaTime = clock.restart().asSeconds() / numberOfInterval;
        pollEvents(balls, window, BALL_SIZE, colors);
        for (int i = 1; i < numberOfInterval; ++i)
        {
            update(balls, deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT, BALL_SIZE);
        }
        redrawFrame(window, balls);
    }
}