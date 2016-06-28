//    ************************************************************
//    *                         Slither                          *
//    *                        June 2016                         *
//    ************************************************************
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <string>

#include "../include/Walls.hh"
#include "../include/Snake.hh"
#include "../include/StartMenu.hh"
#include "../include/Player.hh"
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
  StartMenu startmenu( window.getSize().x, window.getSize().y );
  HighScores scores( window.getSize().x, window.getSize().y );
  Player player( window.getSize().x, window.getSize().y );
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
    bool x = endscreen.getEndState();
    bool x1 = endscreen.getReadyToPlay();
    bool x2 = endscreen.getReadyToQuit();
    bool x3 = endscreen.getReadyToRestart();
      
    bool x4 = startmenu.getMenuState();
    bool x5 = startmenu.getMenuPlay();
    bool x6 = startmenu.getMenuScores();

    bool x7 = snake.getEndState();

    bool x8 = scores.getScoreState();

    bool x9 = player.getPlayerState();

    if( startmenu.getMenuState() ) {
      window.clear();
      sf::Clock menuclock;

      startmenu.HandleMenu(menuclock.restart().asSeconds());
      window.draw(walls);
      window.draw(startmenu);

      if( startmenu.getMenuExit() ) { window.close(); }
    }
    // Handle High Scores:
    if( startmenu.getMenuScores() && scores.getScoreState() ) {
      scores.GoBack();
      window.clear();
      window.draw(walls);
      window.draw(scores);
    }
    if( !scores.getScoreState() ){
      startmenu.setMenuState(true);
      startmenu.setMenuScores(false);
      startmenu.setMenuPlay(false);
      scores.setScoreState(true);
    }
   
    // Handle Game:
    if( startmenu.getMenuPlay() ) {
      if( player.getPlayerState() ){
	sf::Clock delay;
	window.clear();
	window.draw(walls);
	window.draw(player);
	player.HandleInput(event);
	player.HandleEnter(delay.restart().asSeconds());
      } else {
       
	sf::Clock GameClock;
	//Drawing:
	window.clear();
	window.draw(walls);
	window.draw(snake);

	//Updating:
	snake.drawPlayerName(player.getPlayerName());
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
    }
   
    // Handle End screen:
    if( endscreen.getEndState() ) {
      sf::Clock endclock;
      window.clear();
      endscreen.DrawGameOver(player.getPlayerName(),snake.getFinalScore());
      endscreen.HandleEndScreen(endclock.restart().asSeconds());
      window.draw(walls);
      window.draw(endscreen);

      if( endscreen.getReadyToQuit() ){ window.close(); }

      if( endscreen.getReadyToPlay() ){ 
	endscreen.setEndState(false);
	endscreen.setReadyToPlay(false);
	endscreen.setReadyToQuit(false);
	endscreen.setReadyToRestart(false);

	startmenu.setMenuState(true);
	startmenu.setMenuPlay(false);
	startmenu.setMenuScores(false);

	player.setPlayerState(false);

	snake.setEndState(false);

	scores.setScoreState(true);
      }
      if( endscreen.getReadyToRestart() ){
	// Set all Booleans back to Initial Values:   
	endscreen.setEndState(false);
	//endscreen.setReadyToPlay(false);
	endscreen.setReadyToQuit(false);
	endscreen.setReadyToRestart(false);

	startmenu.setMenuState(true);
	startmenu.setMenuPlay(false);
	startmenu.setMenuScores(false);

	snake.setEndState(false);

	scores.setScoreState(true);

	player.setPlayerState(true);
	player.Clear();
      }
    }
    
    window.display();      
  }
  return 0;
}
