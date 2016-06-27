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
#include "../include/StartMenu.hh"
#include "../include/HighScores.hh"
#include "../include/EndScreen.hh"

const float gDisplayx = 500;
const float gDisplayy = 500;

int main() {
  sf::ContextSettings setting;
  setting.antialiasingLevel = 10;
  sf::RenderWindow window(sf::VideoMode(gDisplayx,gDisplayy), "Snake", sf::Style::Default, setting);
  window.setFramerateLimit(60);

  //////////////////////////////////////////////////////
  //                   Initialize                     //
  //////////////////////////////////////////////////////
  StartMenu startmenu(window.getSize().x, window.getSize().y);
  HighScores scores(window.getSize().x, window.getSize().y);
 
  Walls walls( window.getSize().x, window.getSize().y );
  Snake snake( window.getSize().x, window.getSize().y );

  EndScreen endscreen( window.getSize().x, window.getSize().y );

  float elapsed = 0.0;
  float game_elapsed = 0.0;

  while( window.isOpen() ) {

    sf::Event event;
    while( window.pollEvent(event) ) {
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	window.close();
      }
    }
    // Handling Menu Options:
    if( startmenu.getMenuState() ) {
      window.clear();
      sf::Clock menuclock;
      startmenu.HandleMenu(menuclock.restart().asSeconds());
      window.draw(walls);
      window.draw(startmenu); 
    }
    // Handle High Scores:
    scores.GoBack();
    if( startmenu.getMenuScores() && scores.getScoreState() ) {
      window.clear();
      window.draw(walls);
      window.draw(scores);
    }
    if( !scores.getScoreState() ){
      startmenu.setMenuState(true);
      startmenu.setMenuScores(false);
      scores.setScoreState(true);
    }
    if( startmenu.getMenuExit() ) { window.close(); }
    // Handle Game:
    if( startmenu.getMenuPlay() ) {
      sf::Clock GameClock;

      //Drawing:
      window.clear();
      window.draw(walls);
      window.draw(snake);

      //Updating:
      snake.MoveSnake();
      snake.ArrowMovement();
      snake.SnakeEatsFood();
      snake.MakeFoodMove();
      game_elapsed += GameClock.restart().asSeconds();
      snake.GetGameTime(game_elapsed);

      // Snake Death:
      bool death = snake.IsSnakeDead();
      if( death ) {
	sf::Clock Clock;
	elapsed+=Clock.restart().asSeconds();
	snake.MakeSnakeDead(elapsed);
      } else { elapsed = 0.0; }

      // Get End Screen Bool:
      if( snake.getEndState() ) {
	endscreen.setEndState(true);
	startmenu.setMenuState(false);
	startmenu.setMenuPlay(false);
      }
    }
   
    // Handle End screen:
    if( endscreen.getEndState() ) {
      window.clear();
      endscreen.HandleEndScreen();
      window.draw(walls);
      window.draw(endscreen);
    }
    if( endscreen.getReadyToQuit() ){ window.close(); }

    if( endscreen.getReadyToPlay() ){
      // Set all Booleans back to Initial Values:   
      endscreen.setEndState(false);
      endscreen.setReadyToPlay(false);
      endscreen.setReadyToQuit(false);

      startmenu.setMenuState(true);
      startmenu.setMenuPlay(false);
      startmenu.setMenuScores(false);

      snake.setEndState(false);

      scores.setScoreState(true);
    }
    
    window.display();      
  }
  return 0;
}
