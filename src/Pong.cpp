//Pong is a classic two-player arcade game where each player controls a paddle, aiming to hit a ball back and forth across the screen. 
//The objective is to prevent the ball from passing your paddle while attempting to pass it to the opponent's side.
//Points are scored when a player fails to return the ball 

#include "Paddle.h"
#include "Ball.h"
#include "GameStats.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

int main()
{
	// Setting up window size
	int windowWidth = 786;
	int windowHeight = 1024;

	// Create and open a new window for the game
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Classic Pong | ibrahimify", sf::Style::Titlebar | sf::Style::Close);

	// Creating paddle 1 at the bottom center of the screen
	Paddle paddleOne(windowWidth / 2, windowHeight * 0.95);
	// Creating paddle 2 at the top center of the screen
	Paddle paddleTwo(windowWidth / 2, windowHeight * 0.05);

	// Creating Ball at center of screen
	Ball ball(windowWidth / 2, windowHeight / 2);
	
	//setting up the colors
	//for background
	sf::Color background_color = sf::Color(0X000000);	 // Black
	//for padlle and ball
	sf::Color neon = sf::Color(0xDF00FFFF);				 // Flourocent purple
	//Paddle outline
	sf::Color outlineColor(0xDF00FFC0);					 // Flourocent purple with lesser alpha value to glow (C0)
	
	// Assigning colors to game objects
	paddleOne.setColor(neon);
	paddleTwo.setColor(neon);
	ball.setColor(neon);

	// High Score Management
	int highScoreOne, highScoreTwo;
	try {
		GameStats::getHighScores(highScoreOne, highScoreTwo);
	}
	catch (const std::exception& e) {
		std::cerr << "Error loading high scores: " << e.what() << std::endl; // Load high scores from file
		highScoreOne = 0;
		highScoreTwo = 0;
	}

	// Adding text elements for HUD
	Text hudOne, hudTwo;						 // Heads-up display
	Text previousScoreOne, previousScoreTwo;	 // Previous scores 
	Text dashes;								 // Dashes to split the screen

	
	Font font;
	font.loadFromFile("fonts/Retro-Gaming.ttf"); // Load font file

	// Configuring text properties
	hudOne.setFont(font);
	hudTwo.setFont(font);
	previousScoreOne.setFont(font);
	previousScoreTwo.setFont(font);


	hudOne.setCharacterSize(40);
	hudOne.setFillColor(neon);
	hudOne.setPosition(windowWidth * 0.9, windowHeight * 0.6);

	previousScoreOne.setCharacterSize(20);
	previousScoreOne.setFillColor(neon);
	previousScoreOne.setPosition(windowWidth * 0.9, windowHeight * 0.6 + 45);

	hudTwo.setCharacterSize(40);
	hudTwo.setFillColor(neon);
	hudTwo.setPosition(windowWidth * 0.04, windowHeight * 0.34);

	previousScoreTwo.setCharacterSize(20);
	previousScoreTwo.setFillColor(neon);
	previousScoreTwo.setPosition(windowWidth * 0.04, windowHeight * 0.34 - 20);

	dashes.setCharacterSize(60);
	dashes.setFont(font);
	dashes.setFillColor(neon);
	dashes.setPosition(0, window.getSize().y / 2 - 30);

	// The clock is important for updating the game, it must exist before any updates
	Clock clock;

	int scoreOne = 0, scoreTwo = 0;

	// Main game loop
	while (window.isOpen())
	{
		// Event handling
		Event event;
		while (window.pollEvent(event))
		{
			// Handles the player quitting the game, either by close button from titlebar or pressing escape
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{

				try {
					GameStats::recordFinalScores(scoreOne, scoreTwo);
				}
				catch (const std::exception& e) {
					std::cerr << "Exception occurred: " << e.what() << std::endl;
				}
				// Close the window when the game is quit
				window.close();
			}

			
		}

		// Handle the pressing and releasing of the arrow keys

		// Player 1 controls
		if (Keyboard::isKeyPressed(Keyboard::Left))
			paddleOne.moveLeft();
		else
			paddleOne.stopLeft();

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			paddleOne.moveRight();
		}
		else {
			paddleOne.stopRight();
		}

		/// Player 2 controls
		if (Keyboard::isKeyPressed(Keyboard::A))
			paddleTwo.moveLeft();
		else
			paddleTwo.stopLeft();

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			paddleTwo.moveRight();
		}
		else {
			paddleTwo.stopRight();
		}		

	
		// Handle ball hitting the bottom of screen
		if (ball.getPosition().top > window.getSize().y)
		{
			ball.reboundPaddleMult(window.getSize().x, window.getSize().y);
			scoreTwo++;
		}

		// Handle ball hitting top of the screen
		if (ball.getPosition().top < 0)
		{
			ball.reboundPaddleMult(window.getSize().x, window.getSize().y);
			scoreOne++;

		}

		// Handle ball hitting sides
		if ((ball.getPosition().left < 0) || ((ball.getPosition().left + ball.getPosition().width) > window.getSize().x))
		{
			ball.reboundSides();
		}

		// Has the ball hit the Paddle?
		if (ball.getPosition().intersects(paddleOne.getPosition()) || ball.getPosition().intersects(paddleTwo.getPosition()))
		{
			ball.reboundPaddleOrTop();
		}

		// Update the delta time
		Time dt = clock.restart();
		
		// Update game objects
		paddleOne.update(dt);
		paddleTwo.update(dt);
		ball.update(dt);

		// Updating the HUD TEXT for Stats
		std::stringstream stringOne, stringTwo, strScoreOne, strScoreTwo, strDashes;


		stringOne << " " << scoreOne;
		hudOne.setString(stringOne.str());

		strScoreOne << "HS: " << GameStats::playerOneCurrentScore;
		previousScoreOne.setString(strScoreOne.str());

		stringTwo << " " << scoreTwo;
		hudTwo.setString(stringTwo.str());

		strScoreTwo << "HS: " << GameStats::playerTwoCurrentScore;
		previousScoreTwo.setString(strScoreTwo.str());

		strDashes << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
		dashes.setString(strDashes.str());


		// Updating the whole window
		// Clear old window and set its color to black
		window.clear(background_color);

		// Draw all game objects and HUD elements
		window.draw(hudOne);
		window.draw(hudTwo);
		window.draw(previousScoreOne);
		window.draw(previousScoreTwo);
		window.draw(dashes);
		window.draw(paddleOne.getShape());
		window.draw(paddleTwo.getShape());
		window.draw(ball.getShape());

		// Display updated window
		window.display();

	}
	return 0;
}