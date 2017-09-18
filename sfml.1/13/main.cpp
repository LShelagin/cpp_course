#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
int main()
{
    sf::RectangleShape shape1;
    shape1.setFillColor(sf::Color(0x64, 0x02, 0x0C));
    shape1.setPosition({700, 200});
    shape1.setRotation(90);
    shape1.setSize({200, 400});
    sf::RectangleShape shape2;
    shape2.setFillColor(sf::Color(0, 0, 0));
    shape2.setPosition({350, 250});
    shape2.setRotation(0);
    shape2.setSize({80, 150});
    sf::RectangleShape shape3;
    shape3.setFillColor(sf::Color(0x57, 0x50, 0x50));
    shape3.setPosition({600, 80});
    shape3.setRotation(0);
    shape3.setSize({30, 70});
    sf::RectangleShape shape4;
    shape4.setFillColor(sf::Color(0x57, 0x50, 0x50));
    shape4.setPosition({575, 50});
    shape4.setRotation(0);
    shape4.setSize({80, 50});
    sf::ConvexShape trapeze;
    trapeze.setFillColor(sf::Color(0x33, 0, 0x19));
    trapeze.setPosition(400, 100);
    trapeze.setPointCount(4);
    trapeze.setPoint(0, {10, 0});
    trapeze.setPoint(1, {+200, 0});
    trapeze.setPoint(2, {+330, 100});
    trapeze.setPoint(3, {-120, 100});
    sf::CircleShape shape5(20);
    shape5.setPosition(600, 20);
    shape5.setFillColor(sf::Color(0x83, 0x7D, 0x7E));
    sf::CircleShape shape6(20);
    shape6.setPosition(620, 10);
    shape6.setFillColor(sf::Color(0x83, 0x7D, 0x7E));
    sf::CircleShape shape7(20);
    shape7.setPosition(630, 10);
    shape7.setFillColor(sf::Color(0x83, 0x7D, 0x7E));
    sf::CircleShape shape8(20);
    shape8.setPosition(640, 10);
    shape8.setFillColor(sf::Color(0x83, 0x7D, 0x7E));
    sf::RenderWindow window(sf::VideoMode({1000, 600}), "Convex Shape");
    window.clear();
    window.draw(shape1);
    window.draw(shape2);
    window.draw(shape5);
    window.draw(shape6);
    window.draw(shape7);
    window.draw(shape8);
    window.draw(trapeze);
    window.draw(shape3);
    window.draw(shape4);
    window.display();
    sf::sleep(sf::seconds(5));
}