#ifndef STARTMENU_HH
#define STARTMENU_HH

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class StartMenu : public sf::Drawable {

private:
  float fWidth, fHeight;
  int fIndex;
  sf::Font fFont;
  sf::Text fText;
  std::vector<sf::Text> fMenu;
  std::string fOpt1, fOpt2, fOpt3;
  int fEntries;
  sf::Color fColor;

  bool fMenuState;
  bool fCloseMenu;
  bool fScores;
  bool fPlay;
  float fTime;
  float fCutOff;

public:
  StartMenu(float,float);
  ~StartMenu(){};
  void draw(sf::RenderTarget&, sf::RenderStates) const;
  void MoveUp();
  void MoveDown();
 
  void HandleMenu(float);

  int getPressedItem() { return fIndex; }

  bool getMenuState() { return fMenuState; }
  bool getMenuPlay() { return fPlay; }
  bool getMenuScores() { return fScores; }
  bool getMenuExit() { return fCloseMenu; }

  void setMenuState(bool state){ fMenuState = state;} 
  void setMenuScores(bool state){ fScores = state; }
  void setMenuPlay(bool state){ fPlay = state; }
};
#endif
