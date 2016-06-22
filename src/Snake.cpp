#include "../include/Snake.hh"

#include <iostream>
#include <cmath>

Snake::Snake(float x, float y){
  // Grab global window information:
  fDisplayx = x;
  fDisplayy = y;
  fRadius = 10.0;
  fOffset = 1.1;
  fVel = 2.0;

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
    
    temp.setPosition(fDisplayx/2.0 - i*fRadius*fOffset, fDisplayy/2.0 );
    temp.setFillColor( fColors[i] );
    fSnake.push_back( temp );
  }
}

void Snake::ArrowMovement(){
  // There needs to be a check to see if the Snake is moving 
  // out of the screen, if so then kill:

  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ){
    MoveSnake(0);
  }
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){
    MoveSnake(1);
  }
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){
    MoveSnake(2);
  }
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){
    MoveSnake(3);
  }
}

void Snake::MoveSnake(int direction){
  sf::Vector2f nhat(0,0);
  // Get the Appropriate Direction:
  switch(direction){
  case 0: nhat = sf::Vector2f(0,-1);
    break;
  case 1: nhat = sf::Vector2f(0,1);
    break;
  case 2: nhat = sf::Vector2f(1,0);
    break;
  case 3: nhat = sf::Vector2f(-1,0);
    break;
  default:
    break;
  }
  // Only the Head of the Snake should be moved, all other parts move to the next
  // position in the line
  sf::Vector2f move_head = fVel*nhat;

  for(int i=0; i<fSnake.size(); i++){
    if(i==0){
      fSnake[i].move( move_head );
    } else{
      // Position of next circle:
	sf::Vector2f diff = fSnake[i-1].getPosition() - fSnake[i].getPosition();
	float mag = sqrt(pow(diff.x,2) + pow(diff.y,2));
	sf::Vector2f hat = diff/mag*fVel;
	
	if(mag>=fRadius*fOffset) {
	  fSnake[i].move(hat);   
	}
    }
  }
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates) const {
  std::vector<sf::CircleShape>::const_reverse_iterator cit;
  for(cit=fSnake.rbegin(); cit!=fSnake.rend(); cit++){
    target.draw( *cit );
  }
}
