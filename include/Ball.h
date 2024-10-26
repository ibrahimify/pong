#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

// Class for representing a ball in the Pong game
class Ball
{
private:

	// Position of the ball
	Vector2f m_Position;

	// Rectangle shape representing the ball
	RectangleShape m_Shape;

	// Speed of the ball movement
	float m_Speed = 1000.0f;

	// Direction of the ball along the x and y axis respectively
	float m_DirectionX = .2f;
	float m_DirectionY = .2f;

public:

	// Constructor for Ball class
	Ball(float startX, float startY);

	void setColor(sf::Color color);

	FloatRect getPosition();
	RectangleShape getShape();

	float getXVelocity();
	void reboundSides();
	void reboundPaddleOrTop();
	void reboundBottom(int screenwidth, int screenheight);
	void reboundPaddleMult(int screenwidth, int screenheight);

	// Function to update ball movement based on time
	void update(Time dt);

};