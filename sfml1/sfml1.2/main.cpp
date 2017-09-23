#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 600}), "Rectangles and circle");
    window.clear();
    sf::RectangleShape shape1;
    shape1.setSize({150, 50});
    shape1.setRotation(0);
    shape1.setPosition({200, 120});
    shape1.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape1);
    sf::RectangleShape shape2;
    shape2.setSize({200, 50});
    shape2.setRotation(90);
    shape2.setPosition({200, 120});
    shape2.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape2);
    sf::RectangleShape shape3;
    shape3.setSize({150, 50});
    shape3.setRotation(0);
    shape3.setPosition({200, 270});
    shape3.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape3);
    sf::RectangleShape shape4;
    shape4.setSize({150, 50});
    shape4.setRotation(90);
    shape4.setPosition({350, 270});
    shape4.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape4);
    sf::RectangleShape shape5;
    shape5.setSize({200, 50});
    shape5.setRotation(0);
    shape5.setPosition({150, 420});
    shape5.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape5);
    sf::RectangleShape shape6;
    shape6.setSize({350, 50});
    shape6.setRotation(90);
    shape6.setPosition({420, 120});
    shape6.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape6);
    sf::RectangleShape shape7;
    shape7.setSize({100, 50});
    shape7.setRotation(0);
    shape7.setPosition({420, 420});
    shape7.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape7);
    sf::RectangleShape shape8;
    shape8.setSize({400, 50});
    shape8.setRotation(120);
    shape8.setPosition({770, 120});
    shape8.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape8);
    sf::RectangleShape shape9;
    shape9.setSize({400, 50});
    shape9.setRotation(60);
    shape9.setPosition({750, 100});
    shape9.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape9);
    shape3.setSize({200, 50});
    shape3.setRotation(0);
    shape3.setPosition({650, 270});
    shape3.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape3);
    window.display();
    sf::sleep(sf::seconds(5));
}