#include "../include/Snake.hh"

#include <iostream>

Snake::Snake(float x, float y){
  // Grab global window information:
  fDisplayx = x;
  fDisplayy = y;
  fRadius = 10.0;
  
  // Color Vector:
  fColors.push_back( sf::Color::Red );
  fColors.push_back( sf::Color(255, 127, 0) );
  fColors.push_back( sf::Color(255, 255, 0) );
  fColors.push_back( sf::Color(0, 255, 0) );
  fColors.push_back( sf::Color(0, 0, 255) );
  fColors.push_back( sf::Color(75, 0, 130) );
  fColors.push_back( sf::Color(148,0,211) );

  // Make Snake Parts:
  fSnakeParts.setRadius( fRadius );
  sf::FloatRect origin = fSnakeParts.getLocalBounds();
  fSnakeParts.setOrigin( 0.5*origin.width, 0.5*origin.height );

  fSnakeHead.setRadius( 1.2*fRadius );
  origin = fSnakeHead.getLocalBounds();
  fSnakeHead.setOrigin( 0.5*origin.width, 0.5*origin.height );

  // Initialize:
  InitializeSnake();
}

void Snake::InitializeSnake() {
  for( int i=0; i<fColors.size(); i++){
    sf::CircleShape temp;
    if(i==0){ temp = fSnakeHead; }
    else{ temp = fSnakeParts; }
    
    temp.setPosition(fDisplayx/2.0 - i*fRadius, fDisplayy/2.0 );
    temp.setFillColor( fColors[i] );
    fSnake.push_back( temp );
  }
}

void Snake::MoveSnake(){
  // There needs to be a check to see if the Snake is moving 
  // out of the screen, if so then kill:

  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ){
    
  }
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){

  }
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){

  }
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){

  }
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates) const {
  std::vector<sf::CircleShape>::const_reverse_iterator cit;
  for(cit=fSnake.rbegin(); cit!=fSnake.rend(); cit++){
    target.draw( *cit );
  }
}
