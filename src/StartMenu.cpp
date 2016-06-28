#include "../include/StartMenu.hh"

StartMenu::StartMenu(float x, float y){
  fWidth = x;
  fHeight = y;

  if( !fFont.loadFromFile("fonts/bubble.ttf") ) {
    std::cerr << "Error loading font within StartMenu!" << std::endl;
  }
  fIndex = 0;

  float fsize = 50.0;
  fOpt1 = "Play";
  fOpt2 = "High Scores";
  fOpt3 = "Exit";
  fEntries = 3;
  fMenuState = true;
  fCloseMenu = false;
  fPlay = false;
  fScores = false;
  fTime = 7e-6;
  fCutOff = 7e-6;

  fColor = sf::Color(0,170,170);
  
  fText.setFont(fFont);
  fText.setColor(fColor);
  fText.setString(fOpt1);
  fText.setCharacterSize(fsize);
  sf::FloatRect textRect = fText.getLocalBounds();
  fMenu.push_back( fText );
  fMenu[0].setPosition( sf::Vector2f( (fWidth-textRect.width )/2.0, (fHeight-textRect.height)/(fEntries + 1)*1 ) );

  fText.setColor(sf::Color::White);
  fText.setString(fOpt2);
  textRect = fText.getLocalBounds();
  fMenu.push_back( fText );
  fMenu[1].setPosition( sf::Vector2f( (fWidth-textRect.width)/2.0, (fHeight-textRect.height)/(fEntries + 1)*2 ) );

  fText.setColor(sf::Color::White);
  fText.setString(fOpt3);
  textRect = fText.getLocalBounds();
  fMenu.push_back( fText );
  fMenu[2].setPosition( sf::Vector2f( (fWidth-textRect.width)/2.0, (fHeight-textRect.height)/(fEntries + 1)*3 ) );
}

void StartMenu::draw(sf::RenderTarget &target, sf::RenderStates) const {
  std::vector<sf::Text>::const_iterator cit;
  for(cit=fMenu.begin(); cit!=fMenu.end(); cit++){
    target.draw(*cit);
  }
}

void StartMenu::MoveUp(){
  if( fIndex - 1 >= 0 ) {
    fMenu[ fIndex ].setColor( sf::Color::White );
    fIndex--;
    fMenu[ fIndex ].setColor( fColor );
  }
}

void StartMenu::MoveDown(){
  if( fIndex + 1 < fMenu.size() ) {
    fMenu[ fIndex ].setColor( sf::Color::White );
    fIndex++;
    fMenu[ fIndex ].setColor( fColor );
  }
}

void StartMenu::HandleMenu(float time){
  
  fTime+=time;
  if(fTime>fCutOff){
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
      MoveUp();
      fTime = 0.0;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
      MoveDown();
      fTime = 0.0;
    }
  
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ) {
      switch( fIndex ) {
      case 0:
	fMenuState = false;
	fPlay = true;
	break;
      case 1:
	fMenuState = false;
	fScores = true;
	break;
      case 2:
	fMenuState = false;
	fCloseMenu = true;
	break;
	fTime = 0.0;
      }
    }
  }
}

