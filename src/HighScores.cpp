#include "../include/HighScores.hh"
#include <fstream>

HighScores::HighScores(float x, float y){
  fWidth = x;
  fHeight = y;

  if( !fFont.loadFromFile("fonts/bubble.ttf") ) {
    std::cerr << "Error loading font within HighScores!" << std::endl;
  }
  fScoreState = true;

  fColors.push_back( sf::Color::Red );
  fColors.push_back( sf::Color(255, 127, 0) );
  fColors.push_back( sf::Color(255, 255, 0) );
  fColors.push_back( sf::Color(0, 255, 0) );
  fColors.push_back( sf::Color(0, 0, 255) );
  fColors.push_back( sf::Color(75, 0, 130) );
  fColors.push_back( sf::Color(148,0,211) );

  float fsize = 35.0;
  fText.setFont(fFont);
  fText.setCharacterSize(fsize);

  // Open up high scores:
  // This should be done in a function, so HS gets updated at the end
  // of each game...
  std::ifstream highscore;
  std::string line;
  highscore.open("scores.dat");
  int count = 0;
  if( highscore.is_open()){
    while( std::getline(highscore, line) ){
      fText.setString(line);
      fText.setColor(fColors[count%fColors.size()]);
      fScores.push_back(fText);
      count++;
    }
  }else std::cerr << "Error opening high scores!" << std::endl;
  highscore.close();
 
  // Need to position the scores:
  for(int i=0; i<fScores.size(); i++){
    sf::FloatRect textRect = fScores[i].getLocalBounds();
    float x = (fWidth-textRect.width )/2.0;
    float y = textRect.height + i*fsize;
    fScores[i].setPosition(sf::Vector2f(x,y));
  }
}

void HighScores::draw(sf::RenderTarget &target, sf::RenderStates) const {
  std::vector<sf::Text>::const_iterator cit;
  for(cit=fScores.begin(); cit!=fScores.end(); cit++){
    target.draw(*cit);
  }
}

void HighScores::GoBack(){
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) {
    fScoreState = false;
  }
}
