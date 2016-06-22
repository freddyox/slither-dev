#ifndef SNAKE_HH
#define SNAKE_HH

#include <SFML/Graphics.hpp>
#include <vector>

class Snake : public sf::Drawable, public sf::Transformable {
private:
  float fDisplayx, fDisplayy;
  float fRadius;
  std::vector<sf::CircleShape> fSnake;
  sf::CircleShape fSnakeParts;
  sf::CircleShape fSnakeHead;
  float fVx, fVy, fAx, fAy; // velocity and acceleration components

public:
  Snake(float,float); //displayx,y
  ~Snake() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;

  // Snake Properties:
  void InitializeSnake();
  void MoveSnake();

  // Color Scheme = Rainbow:
  std::vector<sf::Color> fColors;
};

#endif
