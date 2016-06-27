#ifndef ENDSCREEN_HH
#define ENDSCREEN_HH

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class EndScreen : public sf::Drawable{

private:
  float fWidth, fHeight;
  int fIndex;
  sf::Font fFont;
  sf::Text fText,fText1;
  std::vector<sf::Text> fOptions;
  std::string fOpt1, fOpt2;
  int fEntries;
  sf::Color fColor;

  // Status Flags:
  bool fEndState;
  bool fReadyToPlay;
  bool fReadyToQuit;

public:
  EndScreen(float,float);
  ~EndScreen(){};
  void draw(sf::RenderTarget&, sf::RenderStates) const;
  void MoveUp();
  void MoveDown();
  int getPressedItem() { return fIndex; }
  void HandleEndScreen();
  bool getEndState(){ return fEndState; }
  void setEndState(bool state) { fEndState = state; }

  bool getReadyToPlay(){ return fReadyToPlay; }
  void setReadyToPlay(bool state) { fReadyToPlay = state; }

  bool getReadyToQuit(){ return fReadyToQuit; }
  void setReadyToQuit(bool state) { fReadyToQuit = state; }
};
#endif
