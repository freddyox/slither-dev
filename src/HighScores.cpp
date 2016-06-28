#include "../include/HighScores.hh"
#include <fstream>
#include <sstream>

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

  fsize = 35.0;
  fText.setFont(fFont);
  fText.setCharacterSize(fsize);
  fText1.setFont(fFont);
  fText1.setCharacterSize(25.0);
  fText1.setColor( sf::Color(0,170,170) );
  fText1.setString("Push SPACE to go back.");
  sf::FloatRect textRect1 = fText1.getLocalBounds();
  fText1.setPosition(sf::Vector2f((fWidth-textRect1.width )/2.0, fHeight-2.0*textRect1.height));

  UpdateScores();
}

void HighScores::draw(sf::RenderTarget &target, sf::RenderStates) const {
  std::vector<sf::Text>::const_iterator cit;
  for(cit=fScores.begin(); cit!=fScores.end(); cit++){
    target.draw(*cit);
  }
  for(cit=fNames.begin(); cit!=fNames.end(); cit++){
    target.draw(*cit);
  }
  target.draw(fText1);
}

void HighScores::GoBack(){
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) {
    fScoreState = false;
  }
}

void HighScores::UpdateScores(){
  fScoreState = true;
 
  std::ifstream highscore;
  std::string line;
  highscore.open("scores.dat");
  int count = 0;
  
  std::string score,name;

  if( highscore.is_open()){
    while( std::getline(highscore, line) ){
      std::stringstream first(line);
      first >> score >> name;
      fText.setString( score );
      fText.setColor(fColors[count%fColors.size()]);
      fScores.push_back(fText);

      fText.setString( name );
      fNames.push_back( fText );
      
      count++;
    }
  }else std::cerr << "Error opening high scores!" << std::endl;
  
  highscore.close();
 
  // Need to position the scores:
  for(int i=0; i<fScores.size(); i++){
    sf::FloatRect textRect = fScores[i].getLocalBounds();
    float x = fWidth/2.0 - 130.0;
    float y = 1.5*textRect.height + i*fsize;
    fScores[i].setPosition(sf::Vector2f(x,y));

    x = fWidth/2.0 - 30.0;
    fNames[i].setPosition(sf::Vector2f(x,y));
  }
}
