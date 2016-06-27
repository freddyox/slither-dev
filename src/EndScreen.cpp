#include "../include/EndScreen.hh"

EndScreen::EndScreen(float x, float y){
  fWidth = x;
  fHeight = y;

  if( !fFont.loadFromFile("fonts/bubble.ttf") ) {
    std::cerr << "Error loading font within EndMenu!" << std::endl;
  }
  fIndex = 0;

  float fsize = 45.0;
  fOpt1 = "Play Again";
  fOpt2 = "Quit";
  fEntries = 2;
  fColor = sf::Color(0,170,170);

  fText.setFont(fFont);
  fText.setColor(fColor);
  fText.setString(fOpt1);
  fText.setCharacterSize(fsize);
  sf::FloatRect textRect = fText.getLocalBounds();
  fText.setPosition( sf::Vector2f( (fWidth-textRect.width)/2.0, fHeight/2.0-textRect.height));
  fOptions.push_back( fText );

  fText.setColor(sf::Color::White);
  fText.setString(fOpt2);
  textRect = fText.getLocalBounds();
  fText.setPosition( sf::Vector2f( (fWidth-textRect.width)/2.0, fHeight/2.0+textRect.height/2.0));
  fOptions.push_back( fText );

  fText1.setFont(fFont);
  fText1.setCharacterSize(55);
  fText1.setColor(sf::Color::Red);
  fText1.setString("GAME OVER");
  textRect = fText1.getLocalBounds();
  fText1.setPosition( sf::Vector2f( (fWidth-textRect.width)/2.0, textRect.height*1.5));

  // Initialize EndScreen booleans:
  fEndState = false;
  fReadyToPlay = false;
  fReadyToQuit = false;
}

void EndScreen::draw(sf::RenderTarget &target, sf::RenderStates) const {
  target.draw(fText1);
  std::vector<sf::Text>::const_iterator cit;
  for(cit=fOptions.begin(); cit!=fOptions.end(); cit++){
    target.draw(*cit);
  }
}

void EndScreen::MoveUp(){
  if( fIndex - 1 >= 0 ) {
    fOptions[ fIndex ].setColor( sf::Color::White );
    fIndex--;
    fOptions[ fIndex ].setColor( fColor );
  }
}

void EndScreen::MoveDown(){
  if( fIndex + 1 < fOptions.size() ) {
    fOptions[ fIndex ].setColor( sf::Color::White );
    fIndex++;
    fOptions[ fIndex ].setColor( fColor );
  }
}

void EndScreen::HandleEndScreen(){
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
    MoveUp();
  }
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
    MoveDown();
  }
  
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ) {
    switch( fIndex ) {
    case 0:
      fEndState = false;
      fReadyToPlay = true;
      break;
    case 1:
      fEndState = false;
      fReadyToQuit = true;
      break;
    }
  }
}

