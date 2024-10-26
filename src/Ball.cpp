#include "Ball.h"

// Ball constructor
Ball::Ball(float startx, float starty) {

	// Initialize position of the ball
	m_Position.x = startx;
	m_Position.y = starty;

	// Set size and position of the ball shape
	m_Shape.setSize(sf::Vector2f(10, 10));
	m_Shape.setPosition(m_Position);

}

void Ball::setColor(sf::Color color) {
	m_Shape.setFillColor(color);
}

FloatRect Ball::getPosition()
{
	return m_Shape.getGlobalBounds(); //collission detection
}
RectangleShape Ball::getShape()
{
	return m_Shape;
}
float Ball::getXVelocity()
{
	return m_DirectionX;
}

// Function to rebound the ball off the either sides of the window
void Ball::reboundSides()
{
	m_DirectionX = -m_DirectionX;
}
void Ball::reboundPaddleOrTop()
{
	m_DirectionY = -m_DirectionY;
	if (m_Speed < 2200.0f) {
		m_Speed = m_Speed * 1.1f;
	}
}

//Function to reset the ball position and rebound it off the bottom of the window
void Ball::reboundBottom(int screenwidth, int screenheight)
{
	m_Position.y = screenwidth * 0.1;
	m_Position.x = screenheight / 2;
	m_DirectionY = -m_DirectionY;
}

// Function to reset the ball position and rebound it off the paddle with a multiplier effect
void Ball::reboundPaddleMult(int screenwidth, int screenheight)
{
	m_Position.y = screenwidth / 2;
	m_Position.x = screenheight / 2;
	m_DirectionY = -m_DirectionY;
}

// Function to update ball movement based on time
void Ball::update(Time dt)
{
	// Update position of the ball
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

	// Move the ball
	m_Shape.setPosition(m_Position);
}