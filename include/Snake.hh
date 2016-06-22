#ifndef SNAKE_HH
#define SNAKE_HH

#include <SFML/Graphics.hpp>
#include <vector>

class Snake : public sf::Drawable, public sf::Transformable {
private:
  float fDisplayx, fDisplayy;
  float fRadius;
  float fOffset;
  std::vector<sf::CircleShape> fSnake;
  sf::CircleShape fSnakeParts;
  sf::CircleShape fSnakeHead;
  float fVel; // velocity components
  float fAccel;

public:
  Snake(float,float); //displayx,y
  ~Snake() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;

  // Snake Properties:
  void InitializeSnake();
  void ArrowMovement();
  void MoveSnake(int);

  // Color Scheme = Rainbow:
  std::vector<sf::Color> fColors;
  std::vector<sf::CircleShape>::iterator vit;
};

#endif
