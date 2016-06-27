#ifndef SNAKE_HH
#define SNAKE_HH

#include <SFML/Graphics.hpp>
#include <vector>

class Snake : public sf::Drawable, public sf::Transformable {
private:
  float fDisplayx, fDisplayy;
  int fWallThick;
  float fGameTime;

  // Snake Properties:
  float fRadius;
  float fHeadRadius;
  float fOffset;
  bool fDead;
  float fDeathTime;

  sf::CircleShape fSnakeParts;
  sf::CircleShape fSnakeHead;
  std::vector<sf::CircleShape> fSnake;

  float fVel, fVelOld; 
  float fAccel;
  sf::Vector2f fHeadDirection;

  // Food:
  int fNFood;
  float fFoodRad;
  sf::CircleShape fFood;
  float fFoodDeg;
  std::vector<sf::CircleShape> fFoodVec;

  // Score:
  sf::Font fFont;
  sf::Text fTitle;
  char fBuff[50];

  bool fReadyForEndState;

public:
  Snake(float,float); //displayx,y
  ~Snake() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;

  // Snake Properties:
  void InitializeSnake();
  void ArrowMovement();
  void MoveSnakeKeyboard(int); //direction
  void MoveSnake();
 
  void MakeFood();
  void SnakeEatsFood();
  void MakeFoodMove();

  void MakeSnakeFaster();
  void MakeSnakeFasterTime();
  void MakeSnakeDead(float);

  void DidSnakeHitWall();
  void DidSnakeHitItself();

  sf::Vector2f GetSnakeDirection(int); //direction

  // Some Get Methods:
  bool IsSnakeDead(){ return fDead; }
  void GetGameTime(float t){ fGameTime = t;}
  
  // Updating:
  void UpdateScore();

  // Cleanup:
  void ClearFood();
  void ClearGame();

  // Misc:
  std::vector<sf::Color> fColors;
  std::vector<sf::CircleShape>::iterator vit;
  void HighScore();

  bool getEndState(){ return fReadyForEndState;}
  void setEndState(bool state){ fReadyForEndState = state; }
};

#endif
