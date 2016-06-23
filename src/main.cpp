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

const float gDisplayx = 500;
const float gDisplayy = 500;

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
    //Drawing:
    window.clear(sf::Color::Black);
    window.draw(walls);
    window.draw(snake);

    //Updating:
    snake.MoveSnake();
    snake.ArrowMovement();
    snake.SnakeEatsFood();

    window.display();      
  }
  return 0;
}
