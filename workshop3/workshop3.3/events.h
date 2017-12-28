#pragma once
#include "constance.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);
void onMouseMove(sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);
void redrawFrame(sf::RenderWindow &window, sf::VertexArray(&lines));