#include "../include/Snake.hh"

#include <iostream>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

Snake::Snake(float x, float y){
  // Grab global window information:
  fDisplayx = x;
  fDisplayy = y;
  fWallThick = 10;
  fRadius = 10.0;
  fHeadRadius =  1.2*fRadius;

  fOffset = 1.1;
  fVel = 2.0;
  fAccel = 4.0*fVel;

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

  fSnakeHead.setRadius( fHeadRadius );
  origin = fSnakeHead.getLocalBounds();
  fSnakeHead.setOrigin( 0.5*origin.width, 0.5*origin.height );

  // Initialize Food and Snake:
  srand(time(NULL));
  fHeadDirection = GetDirection(rand()%4);
  MakeFood();
  InitializeSnake();
  fSnakeLength = fSnake.size();
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

void Snake::MoveSnake(){

  // Checking for wall collisions before I move the snake:
  bool did_snake_hit_wall = false;

  sf::Vector2f head = fSnake[0].getPosition();
  if( head.x - fHeadRadius < 1.1*fWallThick ) {
    did_snake_hit_wall = true;
  }
  if( head.x + fHeadRadius > fDisplayx-1.1*fWallThick ) {
    did_snake_hit_wall = true;
  }
  if( head.y - fHeadRadius < 1.1*fWallThick ) {
    did_snake_hit_wall = true;
  }
  if( head.y + fHeadRadius > fDisplayy-1.1*fWallThick ){
    did_snake_hit_wall = true;
  }

  if( !did_snake_hit_wall ) {
    for(int i=0; i<fSnake.size(); i++){
      if(i==0){
	fSnake[i].move( fVel*fHeadDirection );
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
  } else {
    // Handle death:
  }
}

void Snake::ArrowMovement(){
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ){
    MoveSnakeKeyboard(0);
  }
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){
    MoveSnakeKeyboard(1);
  }
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){
    MoveSnakeKeyboard(2);
  }
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){
    MoveSnakeKeyboard(3);
  }
  if( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ){
    fVel = fAccel;
  } else{
    fVel = 2.0;
  }
}

void Snake::MoveSnakeKeyboard(int direction){
  sf::Vector2f nhat = GetDirection(direction);

  // Only the Head of the Snake should be moved, all other parts move to the next
  // position in the line
  fHeadDirection = nhat;

  for(int i=0; i<fSnake.size(); i++){
    if(i==0){
      fSnake[i].move( fHeadDirection );
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
  std::vector<sf::CircleShape>::const_iterator cit1;
  for(cit1=fFoodVec.begin(); cit1!=fFoodVec.end(); cit1++){
    target.draw( *cit1 );
  }
  std::vector<sf::CircleShape>::const_reverse_iterator cit;
  for(cit=fSnake.rbegin(); cit!=fSnake.rend(); cit++){
    target.draw( *cit );
  }
}

sf::Vector2f Snake::GetDirection(int direction){
  sf::Vector2f nhat(0,0);
  switch(direction){
  case 0: nhat = sf::Vector2f(0,-1);
    break;
  case 1: nhat = sf::Vector2f(0,1);
    break;
  case 2: nhat = sf::Vector2f(1,0);
    break;
  case 3: nhat = sf::Vector2f(-1,0);
    break;
  default: std::cerr << "GetDirection routine came across an error!" << std::endl;
    break;
  }
  return nhat;
}

void Snake::MakeFood(){
  // Generate a color, radius, location:
  srand(time(NULL)); 
  fFoodRad = rand()%4 + 5;
  fFood.setRadius( fFoodRad );
   sf::FloatRect origin = fFood.getLocalBounds();
  fFood.setOrigin( 0.5*origin.width, 0.5*origin.height );
  fFood.setFillColor( fColors[rand()%fColors.size()] );

  // // Place it randomly away from the snake:
  // sf::Vector2f headpos = fSnake[0].getPosition();
  // sf::Vector2f tailpos = fSnake[fSnake.size()-1].getPosition();
  // float x = headpos.x - tailpos.x;
  // float y = headpos.y - tailpos.y;

  // // Find center position
  // sf::Vector2f center = headpos + sf::Vector2f(x,y);

  int tempx = rand()%(int(fDisplayx)-3*fWallThick) + 2*fWallThick;
  int tempy = rand()%(int(fDisplayy)-3*fWallThick) + 2*fWallThick;
  fFood.setPosition(tempx,tempy);
  fFoodVec.push_back(fFood);
}

void Snake::SnakeEatsFood(){
  // 1. Need to check to see if snake head overlaps with food
  // 2. Need to remove food, then regenerate food
  // 3. Need to make snake bigger

  sf::Vector2f headpos = fSnake[0].getPosition();
  sf::Vector2f foodpos = fFoodVec[0].getPosition();
  sf::Vector2f d = headpos - foodpos;
  float mag = sqrt( pow(d.x,2) + pow(d.y,2) );
  if( mag<=fOffset*fHeadRadius ) {

    fFoodVec.erase( fFoodVec.begin() );
    
    int index = fSnakeLength % fColors.size();
    fSnakeParts.setFillColor( fColors[index] );
    
    // Need to generate a position
    sf::Vector2f next2last = fSnake[fSnake.size()-2].getPosition();
    sf::Vector2f last = fSnake[fSnake.size()-1].getPosition();
    sf::Vector2f dis = last - next2last;
    float dmag = sqrt( pow(dis.x,2) + pow(dis.y,2) );
    sf::Vector2f pos = last + (dis / dmag) * fRadius * fOffset ;
    fSnakeParts.setPosition(pos);
    fSnake.push_back(fSnakeParts);

    fSnakeLength++;
    MakeFood();
  }
}
