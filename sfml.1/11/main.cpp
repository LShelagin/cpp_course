#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rectangles and circle");
    window.clear();
    sf::RectangleShape shape1;
    shape1.setSize({300, 100});
    shape1.setRotation(90);
    shape1.setPosition({200, 120});
    shape1.setFillColor(sf::Color(0x750, 0x50, 0x50));
    window.draw(shape1);
    sf::CircleShape shape2(40);
    shape2.setPosition({110, 120});
    shape2.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape2);
    sf::CircleShape shape3(40);
    shape3.setPosition({110, 220});
    shape3.setFillColor(sf::Color(0xFF, 0x8C, 0x0));
    window.draw(shape3);
    sf::CircleShape shape4(40);
    shape4.setPosition({110, 320});
    shape4.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape4);
    window.display();
    sf::sleep(sf::seconds(5));
}