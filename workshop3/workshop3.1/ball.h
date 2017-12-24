#pragma once
#include <SFML/Graphics.hpp>
#include "constance.h"

class Initials : public sf::Drawable
{
public:
  void update(float delataTime);
  void init();

private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void text(sf::Vector2f position);

  sf::Vector2f speed = startSpeed;
  sf::Vector2f position = startPosition;
  sf::Vector2f textPosition = startTextPosition;

  sf::CircleShape ball;
  sf::Text initText;
  sf::Font font;
};