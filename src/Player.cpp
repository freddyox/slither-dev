#include "../include/Player.hh"

Player::Player(float x, float y){
  fWidth = x;
  fHeight = y;
  fPlayerState = true;
  fTime = 0.0;

  if( !fFont.loadFromFile("fonts/bubble.ttf") ) {
    std::cerr << "Error loading font within EndMenu!" << std::endl;
  }

  float fsize = 45.0;
  fLine1 = "Enter Player Name,";
  fLine2 = "then press ENTER:";
 
  fColor = sf::Color(0,170,170);

  fText.setFont(fFont);
  fText.setColor(fColor);
  fText.setString(fLine1);
  fText.setCharacterSize(fsize);
  sf::FloatRect textRect = fText.getLocalBounds();
  sf::Vector2f pos(fWidth/2.0 - textRect.width/2.0, textRect.height );
  fText.setPosition( pos );
  fTextV.push_back( fText );

  fText.setString(fLine2);
  textRect = fText.getLocalBounds();
  pos = sf::Vector2f(fWidth/2.0 - textRect.width/2.0, 2.0*textRect.height );
  fText.setPosition( pos );
  fTextV.push_back( fText );

  fInputText.setFont(fFont);
  fInputText.setColor(sf::Color::Red);
  fInputText.setCharacterSize(fsize+5.0);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates) const {
  std::vector<sf::Text>::const_iterator cit;
  for(cit=fTextV.begin(); cit!=fTextV.end(); cit++){
    target.draw(*cit);
  }
  target.draw(fInputText);
}

void Player::HandleInput(sf::Event event){

  if ( event.type == sf::Event::TextEntered ) {
    if( !(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) ) {
      
      int textSize = fInput.size();
      unsigned short unicode = event.text.unicode;
      // Handle keyboard input:
      if( textSize < 11 ) { 
	if(unicode < 128 && unicode != 8) {
	  fInput += static_cast<char>(event.text.unicode);
	}
      }
      // Delete key:
      if( unicode == 8 ) {
	if(textSize > 0) {
	  fInput.erase(textSize - 1, 1);
	}
      }
      // Display:
      fInputText.setString(fInput);
      sf::FloatRect textRect = fInputText.getLocalBounds();
      sf::Vector2f pos(fWidth/2.0 - textRect.width/2.0, fHeight/2.0 );
      fInputText.setPosition( pos );
      sf::sleep((sf::milliseconds(120)));
    }
  }
}

void Player::HandleEnter(float time){
  fTime += time;
  if(fTime>0.01) {
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ) {
      fPlayerState = false;
      fTime = 0.0;
    }
  }
}

void Player::Clear(){
  fInput.clear();
  fTime = 0.0;
  fInputText.setString(fInput);
}
