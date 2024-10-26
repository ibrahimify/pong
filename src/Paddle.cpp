#include "Paddle.h"

// Paddle constructor
Paddle::Paddle(float startX, float startY) : Position(startX, startY)
{
	// Set size and position of the paddle shape
	Shape.setSize(sf::Vector2f(90, 7));
	Shape.setPosition(Position);
	Shape.setFillColor(sf::Color::Black);



	// Set anchor point to center of paddle shape
	Shape.setOrigin(Shape.getSize() / (float)2);


	// Set outline properties for the paddle
	thickness = 3.0f;  // Adjust thickness as desired
	outlineColor = sf::Color(0xDF00FFC0);  // Light blue neon outline (optional)
	Shape.setOutlineThickness(thickness);
	Shape.setOutlineColor(outlineColor);
}
	// Function to set the color of the paddle
	void Paddle::setColor(sf::Color color) {
	Shape.setFillColor(color);
}

// Basic functions that the paddle will need

// Function to get the position of the paddle
FloatRect Paddle::getPosition()
{
	return Shape.getGlobalBounds();
}
// Function to get the shape of the paddle
RectangleShape Paddle::getShape()
{
	return Shape;
}
// Function to set the position of the paddle
void Paddle::setPosition(int x, int y)
{
	Shape.setPosition(x, y);
}

// Functions to make move or stop the paddle to the right or left side
void Paddle::moveLeft()
{
	MovingLeft = true;
}
void Paddle::moveRight()
{
	MovingRight = true;
}
void Paddle::stopLeft()
{
	MovingLeft = false;
}
void Paddle::stopRight()
{
	MovingRight = false;
}

// Function to update paddle movement based on time
void Paddle::update(Time dt)
{
	if (MovingLeft) {
		Position.x -= Speed * dt.asSeconds();
	}
	if (MovingRight) {
		Position.x += Speed * dt.asSeconds();
	}
	// Update position of paddle shape
	Shape.setPosition(Position);
}

////for (int i = 2; i = 8; i++){
//int i = 0;
//int x = 9 * 30; 
// for the loop ther could be so many thinga that coul go wrong and there I 
// and here coukld be there could be idk what the hell I am wrtiign but thies mother fuccket
//

//