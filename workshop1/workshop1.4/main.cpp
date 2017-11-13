#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <cmath>
struct Cat
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f scale;
    sf::Vector2f position;
};

struct Laser
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f scale;
    sf::Vector2f position;
};

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void init(Cat &cat, Laser &laser)
{
    cat.texture.loadFromFile("./cat.png");

    cat.sprite.setTexture(cat.texture);
    cat.sprite.setPosition(15, 15);
    cat.sprite.setScale(1, 1);

    laser.texture.loadFromFile("./laser.png");
    laser.sprite.setTexture(laser.texture);
}

void onMouseClick(sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition, Laser &laser)
{
    laser.scale = {1, 1};
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, Laser &laser)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, mousePosition, laser);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, Cat &cat, Laser &laser, float &deltaTime)
{
    const sf::Vector2f delta = mousePosition - cat.position;
    float angle = atan2(delta.y, delta.x);
    sf::Vector2f direction = (delta / hypotf(delta.x, delta.y));
    float speed = 100.f;
    if (hypotf(delta.x, delta.y) != 0.f)
    {
        cat.position += direction * speed * deltaTime;
        cat.sprite.setPosition(cat.position);
    }
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    angle = toDegrees(angle);
    if (((angle <= 90) && (angle >= 0)) || ((angle >= 270) && (angle <= 360)))
    {
        cat.sprite.setScale(1, 1);
    }
    else
    {
        cat.sprite.setScale(-1, 1);
    }

    laser.sprite.setPosition(mousePosition);
}

void redrawFrame(sf::RenderWindow &window, Cat &cat, Laser &laser)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(cat.sprite);
    window.draw(laser.sprite);
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
        "Cat ", sf::Style::Default, settings);

    sf::Clock clock;
    sf::Vector2f mousePosition;

    Cat cat;
    Laser laser;

    init(cat, laser);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition, laser);
        float deltaTime = clock.restart().asSeconds();
        update(mousePosition, cat, laser, deltaTime);
        redrawFrame(window, cat, laser);
    }
}