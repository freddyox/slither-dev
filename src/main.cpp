//    ************************************************************
//    *                         Slither                          *
//    *                        June 2016                         *
//    ************************************************************
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "../include/Walls.hh"
#include "../include/Snake.hh"

const float gDisplayx = 1000;
const float gDisplayy = 1000;

int main() {

  sf::RenderWindow window(sf::VideoMode(gDisplayx,gDisplayy), "Snake");
  window.setFramerateLimit(60);

  //////////////////////////////////////////////////////
  //                   Initialize                     //
  //////////////////////////////////////////////////////
  Walls walls( window.getSize().x, window.getSize().y );
  Snake snake( window.getSize().x, window.getSize().y );

  while( window.isOpen() ) {

    sf::Event event;
    while( window.pollEvent(event) ) {
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	window.close();
      }
    }
    window.clear(sf::Color::Black);
    window.draw(walls);
    window.draw(snake);
    window.display();      
  }
  return 0;
}
