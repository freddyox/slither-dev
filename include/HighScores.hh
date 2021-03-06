#ifndef HIGHSCORES_HH
#define HIGHSCORES_HH

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

class HighScores : public sf::Drawable {

private:
  float fWidth, fHeight;
  sf::Font fFont;
  sf::Text fText,fText1;
  float fsize;
  std::vector<sf::Text> fScores, fNames;
  std::vector<sf::Color> fColors;
  bool fScoreState;

public:
  HighScores(float,float);
  ~HighScores(){};
  void draw(sf::RenderTarget&, sf::RenderStates) const;
  bool getScoreState() { return fScoreState; }
  void setScoreState(bool state){ fScoreState = state;}
  void GoBack();
  void UpdateScores();
};
#endif
