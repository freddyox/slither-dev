#ifndef PLAYER_HH
#define PLAYER_HH

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

class Player : public sf::Drawable{
private:
  float fWidth, fHeight;
  bool fPlayerState;
  std::string fLine1, fLine2;
  std::string fInput;
  sf::Text fInputText;
  float fTime;

public:
  Player(float,float);
  ~Player(){};
  void draw(sf::RenderTarget&, sf::RenderStates) const;

  sf::Font fFont;
  sf::Text fText,fText1;

  sf::Color fColor;
  std::vector<sf::Text> fTextV;

  void setPlayerState(bool state){ fPlayerState = state; }
  bool getPlayerState(){ return fPlayerState; }

  std::string getPlayerName() { return fInput; }

  void HandleInput(sf::Event);
  void HandleEnter(float);

  void Clear();
};
#endif
