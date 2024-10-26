// pragma once prevents the file from being processed by the compiler more than once. 
// As our games get more complicated with perhaps dozens of classes, this will speed up compilation time.
#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

// Class for representing a paddle in the Pong game
class Paddle
{
private:

	Vector2f Position;			// Position of the paddle
	RectangleShape Shape;		// Rectangle shape representing the paddle
	float Speed = 350.0f;		// Speed of the paddle movement
	bool MovingRight = false;	// Flag indicating if paddle is moving right
	bool MovingLeft = false;	// Flag indicating if paddle is moving left

	// For outlining the paddle
	float thickness;
	sf::Color outlineColor;


public:

	// Constructor for Paddle class
	Paddle(float startX, float startY);

	//Function to get the position and shape of paddle
	FloatRect getPosition();
	RectangleShape getShape();
	void setColor(sf::Color color);

	// Functions to move, stop, and update the paddle
	void moveLeft();
	void moveRight();
	void stopLeft();
	void stopRight();
	void update(Time dt);
	void setPosition(int x, int y);

	// Outline of paddle
	void setOutlineThickness(float thickness);
	void setOutlineColor(const sf::Color& color);

};