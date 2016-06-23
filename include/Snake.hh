#ifndef SNAKE_HH
#define SNAKE_HH

#include <SFML/Graphics.hpp>
#include <vector>

class Snake : public sf::Drawable, public sf::Transformable {
private:
  float fDisplayx, fDisplayy;
  float fRadius;
  float fHeadRadius;
  float fOffset;
  int fWallThick;
  int fSnakeLength;

  std::vector<sf::CircleShape> fSnake;
  sf::CircleShape fSnakeParts;
  sf::CircleShape fSnakeHead;
  float fVel; 
  float fAccel;
  sf::Vector2f fHeadDirection;

  float fFoodRad;
  sf::CircleShape fFood;
  std::vector<sf::CircleShape> fFoodVec;

public:
  Snake(float,float); //displayx,y
  ~Snake() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;

  // Snake Properties:
  void InitializeSnake();
  void ArrowMovement();
  void MoveSnakeKeyboard(int);
  void MoveSnake();
 
  void MakeFood();
  void SnakeEatsFood();

  // +/- x and +/- y directions. Argument is int (0-3) corresponding
  // to these directions:
  sf::Vector2f GetDirection(int);
  
  // Color Scheme = Rainbow:
  std::vector<sf::Color> fColors;
  std::vector<sf::CircleShape>::iterator vit;
};

#endif
