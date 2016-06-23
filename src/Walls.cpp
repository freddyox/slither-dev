#include "../include/Walls.hh"
#include <iostream>

Walls::Walls(float x, float y) {

  displayx = x; 
  displayy = y;
  width = 10.0;
  sf::Color WallColor = sf::Color(51,0,102);

  sf::Vector2f VerticalSize( width, displayy ); 
  Wall.setSize( VerticalSize );
  Wall.setFillColor( WallColor );
  Wall.setPosition( 0, 0);
  WallVec.push_back( Wall );
  Wall.setPosition( displayx-width, 0 );
  WallVec.push_back( Wall );

  sf::Vector2f HorizontalSize( displayx - 2*width, width );
  Wall.setSize( HorizontalSize );
  Wall.setPosition( width, 0 );
  WallVec.push_back( Wall );
  Wall.setPosition( width, displayy-width );
  WallVec.push_back( Wall );

  lines = sf::VertexArray(sf::LinesStrip,2);

  // Load up a background:
  if(!texture.loadFromFile("pics/bg.jpeg")) {
    std::cerr << "Error loading background texture!" << std::endl;
  }
  bg.setTexture(texture);
  bg.setPosition(0,0);
}

void Walls::draw(sf::RenderTarget& target, sf::RenderStates) const {
  target.draw(bg);

  std::vector<sf::RectangleShape>::const_iterator cit;
  for( cit = WallVec.begin(); cit != WallVec.end(); cit++ )
    target.draw(*cit);

  std::vector<sf::VertexArray>::const_iterator cit1;
  for(cit1=grid.begin(); cit1 != grid.end(); cit1++) {
    target.draw(*cit1);
  }
}
