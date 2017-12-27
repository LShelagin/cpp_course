#pragma once
#include <SFML/Graphics.hpp>

static const float accelerationOfGravity = 100;
static const float WINDOW_WIDTH = 800;
static const float WINDOW_HEIGHT = 600;
static const float BALL_SIZE = 100;
static const float OUTLINE_SIZE = 3;
static const sf::Vector2f startPosition = {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 2.1 * (BALL_SIZE + OUTLINE_SIZE)};
static const sf::Vector2f startSpeed = {0, 200};
static const sf::Vector2f startTextPosition = {WINDOW_WIDTH / 2 + BALL_SIZE / 1.4, WINDOW_HEIGHT - 1.3 * BALL_SIZE - OUTLINE_SIZE};