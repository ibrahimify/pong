#pragma once

// Class for managing game statistics such as high scores
class GameStats {

public:

	// Function to record final scores at the end of the game
	static void recordFinalScores(int playerOneScore, int playerTwoScore);
	// Function to retrieve high scores from file
	static void getHighScores(int& playerOneScore, int& playerTwoScore);

	// Static variables to store current scores
	static int playerOneCurrentScore;
	static int playerTwoCurrentScore;

};