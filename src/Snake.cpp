#include "../include/Snake.hh"

#include <iostream>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <set>
#include <sstream>
#include <map>

Snake::Snake(float x, float y){
  // Grab global window information:
  fDisplayx = x;
  fDisplayy = y;
  fWallThick = 10;            // boarder thickness
  fRadius = 10.0;             // radius of snake part
  fHeadRadius =  1.2*fRadius; // radius of snake head

  fOffset = 1.25;              // place snakeparts radius*offset
  fVel = 2.0;                 // snake v
  fVelOld = fVel;             // previous snake vel
  fAccel = 3.0*fVel;          // snake spacebar speed
  fDead = false;              // Snake dead or not?
  fDeathTime = 0.000035;       // Time it takes to dissolve dead snake

  // Color Vector:
  fColors.push_back( sf::Color::Red );
  fColors.push_back( sf::Color(255, 127, 0) );
  fColors.push_back( sf::Color(255, 255, 0) );
  fColors.push_back( sf::Color(0, 255, 0) );
  fColors.push_back( sf::Color(0, 0, 255) );
  fColors.push_back( sf::Color(75, 0, 130) );
  fColors.push_back( sf::Color(148,0,211) );

  // Make Snake Parts & Head
  fSnakeParts.setRadius( fRadius );
  sf::FloatRect origin = fSnakeParts.getLocalBounds();
  fSnakeParts.setOrigin( 0.5*origin.width, 0.5*origin.height );

  fSnakeHead.setRadius( fHeadRadius );
  origin = fSnakeHead.getLocalBounds();
  fSnakeHead.setOrigin( 0.5*origin.width, 0.5*origin.height );

  // Initialize Food and Snake:
  srand(time(NULL));
  int temp = rand()%3;
  if(temp==3){ temp = 1;};
  fHeadDirection = GetSnakeDirection(temp); // don't let it go left, or it dies by self collision
  fFoodDeg = 0.0;                           // rotate food
  fNFood = 0;                               // number of food eaten
  MakeFood();                               // make some food
  InitializeSnake();                        // initialize the snake

  // Initialize the Score:
  if( !fFont.loadFromFile("fonts/arial.ttf")) {
    std::cerr << "ERROR: Font did not load properly." << std::endl;
  }
  fTitle.setFont(fFont);
  sprintf(fBuff,"%d",int(fSnake.size()));
  fTitle.setString(fBuff);
  fTitle.setCharacterSize(20);
  fTitle.setColor(sf::Color::White);
  sf::FloatRect recttemp = fTitle.getLocalBounds();
  fTitle.setPosition( fDisplayx-recttemp.width - 1.4*fWallThick, 
		      fDisplayy-recttemp.height - 2.1*fWallThick);

  fPlayer.setFont(fFont);
  fPlayer.setCharacterSize(20);
  fPlayer.setColor(sf::Color::White);

  // Initialize EndScreen Boolean:
  fReadyForEndState = false;
}

void Snake::InitializeSnake() {
  fDead = false;
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
  // Check collisions before moving snake head:
  DidSnakeHitWall();

  DidSnakeHitItself();

  if( !fDead ) {
    for(int i=0; i<fSnake.size(); i++){
      if(i==0){
	fSnake[i].move( fVel*fHeadDirection );
      } else{
	// Position of next circle:
	sf::Vector2f diff = fSnake[i-1].getPosition() - fSnake[i].getPosition();
	float mag = sqrt(pow(diff.x,2) + pow(diff.y,2));
	sf::Vector2f vel = diff/mag*fVel;
	if(mag>=fRadius*fOffset) {
	  fSnake[i].move(vel);   
	} 
      }
    }
  } 
}

void Snake::ArrowMovement(){

  int direction = -1;
  if( !fDead ) {
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ){
      direction = 0;
    }
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){
      direction = 1;
    }
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){
      direction = 2;
    }
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){
      direction = 3;
    }
    if( direction!=-1 ) {
      fHeadDirection = GetSnakeDirection(direction);
    }
    
    // Handle Acceleration: 
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ){
      fVel = fAccel;
    } else{
      fVel = fVelOld;
    }
  }
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates) const {
  target.draw(fTitle);
  target.draw(fPlayer);
  std::vector<sf::CircleShape>::const_iterator cit1;
  for(cit1=fFoodVec.begin(); cit1!=fFoodVec.end(); cit1++){
    target.draw( *cit1 );
  }
  std::vector<sf::CircleShape>::const_reverse_iterator cit;
  for(cit=fSnake.rbegin(); cit!=fSnake.rend(); cit++){
    target.draw( *cit );
  }
}

sf::Vector2f Snake::GetSnakeDirection(int direction){
  // 0 = -y, 1 = +y, 2 = +x, 3 = -x
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
  default: std::cerr << "GetSnakeDirection routine came across an error!" << std::endl;
    break;
  }
  return nhat;
}

void Snake::MakeFood(){
  // Generate a color, radius, location:
  srand(time(NULL)); 
  fFoodRad = rand()%5 + 5;
 
  fFood.setRadius( fFoodRad );
   sf::FloatRect origin = fFood.getLocalBounds();
  fFood.setOrigin( 0.5*origin.width, 0.5*origin.height );
  fFood.setFillColor( fColors[rand()%fColors.size()] );
  fFood.setOutlineThickness(0.5);
  fFood.setOutlineColor(sf::Color::White);

  int tempx = rand()%(int(fDisplayx)-6*fWallThick) + 3*fWallThick;
  int tempy = rand()%(int(fDisplayy)-6*fWallThick) + 3*fWallThick;
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
 
    fSnakeParts.setFillColor( fColors[int(fSnake.size()) % fColors.size()] );
    
    // Need to generate a position
    sf::Vector2f next2last = fSnake[fSnake.size()-2].getPosition();
    sf::Vector2f last = fSnake[fSnake.size()-1].getPosition();
    sf::Vector2f dis = last - next2last;
    float dmag = sqrt( pow(dis.x,2) + pow(dis.y,2) );
    sf::Vector2f pos = last + (dis / dmag) * fRadius * fOffset ;
    fSnakeParts.setPosition(pos);
    fSnake.push_back(fSnakeParts);

    if(fFoodRad>7){
      fSnakeParts.setFillColor( fColors[int(fSnake.size()) % fColors.size()] );
      fSnake.push_back(fSnakeParts);
    }
    if(fFoodRad>8){
      fSnakeParts.setFillColor( fColors[int(fSnake.size()) % fColors.size()] );
      fSnake.push_back(fSnakeParts);
    }
    // Updates:
    fNFood++;
    if( fNFood>0 && fNFood%6==0) MakeSnakeFaster();
    UpdateScore();
    MakeFood();
    ClearFood();
  }
}

void Snake::DidSnakeHitWall(){
  sf::Vector2f head = fSnake[0].getPosition();
  if( head.x - fHeadRadius < 1.1*fWallThick ) {
    fDead = true;
  }
  if( head.x + fHeadRadius > fDisplayx-1.1*fWallThick ) {
    fDead = true;
  }
  if( head.y - fHeadRadius < 1.1*fWallThick ) {
    fDead = true;
  }
  if( head.y + fHeadRadius > fDisplayy-1.1*fWallThick ){
    fDead = true;
  }
}

void Snake::DidSnakeHitItself(){
  sf::Vector2f head = fSnake[0].getPosition();
  // Ignore head and first from head:
  for(vit=fSnake.begin()+2; vit!=fSnake.end(); vit++){
    sf::Vector2f parts = vit->getPosition();
    sf::Vector2f d = parts - head;
    float mag = sqrt( pow(d.x,2)+pow(d.y,2) );
    if( fabs(mag) < 0.7*fRadius ){ fDead = true; }
  }
}

void Snake::UpdateScore(){
  sprintf(fBuff,"%d",int(fSnake.size()));
  fTitle.setString(fBuff);
  fTitle.setCharacterSize(20);
  fTitle.setColor(sf::Color::White);
  sf::FloatRect recttemp = fTitle.getLocalBounds();
  fTitle.setPosition( fDisplayx-recttemp.width - 1.4*fWallThick, 
		      fDisplayy-recttemp.height - 2.1*fWallThick);
}

void Snake::MakeFoodMove(){
  if( !fFoodVec.empty() ){
    fFoodDeg+=0.1;
    fFoodVec[0].move( 0.1*fFoodRad*cos(fFoodDeg),
		      0.1*fFoodRad*sin(fFoodDeg) );
  }
}

void Snake::ClearFood(){
  fFoodDeg = 0.0;
}

void Snake::ClearGame(){
  fSnake.clear();
  fFoodVec.clear();
  fVel = 2.0;
  fVelOld = fVel;
  fAccel = 3.0*fVel;
}

void Snake::MakeSnakeFaster(){
  fVel += 0.3;
  fVelOld = fVel;
  fAccel = 3.0*fVel;
}

void Snake::MakeSnakeDead(float elapsed){
  float ratio = 1 - elapsed / fDeathTime;
  // Mutate the snake:
  for( vit=fSnake.begin(); vit!=fSnake.end(); vit++ ){
    sf::Color current = vit->getFillColor();
    sf::Color dissolve = sf::Color(current.r,current.g,current.b,255*ratio);
    sf::Vector2f posnow = vit->getPosition();
    vit->setFillColor( dissolve );

    float r = vit->getRadius();
    float R = 1.01*r;
    vit->setRadius( ratio*(r-R)+R );
    sf::FloatRect origin = vit->getLocalBounds();
    vit->setOrigin( 0.5*origin.width, 0.5*origin.height );
    vit->setPosition(posnow);
  }
  // Restart the Snake:
  if( ratio <= 0.05 ) {
    // Set the End Screen Flag:
    fDead = false;
    fReadyForEndState = true;
 
    HighScore();
    ClearGame();

    srand(time(NULL));
    fHeadDirection = GetSnakeDirection(rand()%3);
    InitializeSnake();

    MakeFood();
    UpdateScore();
  }
}

void Snake::HighScore(){
  fFinal = fSnake.size();

  std::ifstream highscore;
  std::string line;
  highscore.open("scores.dat");

  std::multimap<int,std::string> list;

  // Is our new score even in the running:
  bool is_it_new = false;
  int count = 1;

  if( highscore.is_open()){
    while( std::getline(highscore, line) ){
      int score;
      std::string name;
      std::stringstream first(line);
      first >> score >> name;

      list.insert(std::pair<int,std::string>(score,name));

      if( fFinal >= score || count<=10 ) { 
	is_it_new = true; 
      }
      count++;
    }
  } else std::cerr << "Error opening high scores!" << std::endl;
  highscore.close();

  // Insert the new score:
  if(is_it_new){
    list.insert(std::pair<int,std::string>(fSnake.size(),fPlayer.getString()));

    std::ofstream newscores;
    newscores.open("scores.dat");
    // Update the highscore:
    std::multimap<int,std::string>::reverse_iterator rit;
    count = 1;
    for(rit=list.rbegin(); rit!=list.rend(); rit++){
      if( count<=10 ){
	newscores << rit->first << "   " << rit->second << std::endl;
      }
      count++;
    }
  }
}

void Snake::drawPlayerName(std::string player){
  fPlayer.setString(player);
  sf::FloatRect recttemp = fPlayer.getLocalBounds();
  fPlayer.setPosition( 1.4*fWallThick, 
		       fDisplayy-recttemp.height - 2.1*fWallThick);
}
