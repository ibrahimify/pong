#include <fstream>
#include <iostream>
#include "GameStats.h"

// Static variables must be initialized only once outside the class before usage 
int GameStats::playerOneCurrentScore;
int GameStats::playerTwoCurrentScore;

// Function to record final scores at the end of the game
void GameStats::recordFinalScores(int playerOneScore, int playerTwoScore) {

	// Open file for writing
	std::ofstream* file = new std::ofstream;
	file->open("GameStats.txt");

	// Check if file is opened successfully
	if (file->is_open()) {
		// Write player one's score to file
		if (playerOneScore > playerOneCurrentScore) {
			*file << playerOneScore << std::endl;
		}
		else {
			*file << playerOneCurrentScore << std::endl;
		}

		// Write player two's score to file
		if (playerTwoScore > playerTwoCurrentScore) {
			*file << playerTwoScore << std::endl;
		}
		else {
			*file << playerTwoCurrentScore << std::endl;
		}
		// Close file after writing 
		file->close();
	}
	else {
		// Throw exception if file cannot be opened
		throw std::runtime_error("Whoops! The Hall of Fame seems to be down for maintenance. Your amazing score won't be recorded this time.");
	}

	// Deallocate file pointer
	delete file;

}

// Function to retrieve high scores from file
void GameStats::getHighScores(int& playerOneScore, int& playerTwoScore) {

	// Open file for reading
	std::ifstream* file = new std::ifstream;
	file->open("GameStats.txt");

	// Check if file is opened successfully
	if (file->is_open()) {

		// Read player one and player two scores from file
		*file >> playerOneCurrentScore;
		*file >> playerTwoCurrentScore;

		// Close file after reading
		file->close();
	}
	else {
		// Throw exception if file cannot be opened
		throw std::runtime_error("Couldn't retrieve past champions' scores. Starting the match with a clean slate.");
	}

	// Deallocate file pointer
	delete file;

	playerOneScore = playerOneCurrentScore;
	playerTwoScore = playerTwoCurrentScore;


}
