/* This is the console executable, that makes use of the BullCow class
   This acts as the view in a MVC pattern, and is responsible for all
   user interaction. For game logic, see the FBullCowGame class.
*/

#pragma once

# include <iostream>
# include <string>
# include "FBullCowGame.h"

// to make syntax Unreal engine friendly
using namespace std;
using FText = string;
using int32 = int;

// function prototypes as outside a class
void printIntro();
FText getValidGuess();
void playGame();
bool playAgain();
void printGameSummary();

//create instance of the game
FBullCowGame BCGame;

int main(){
	
	do {
		printIntro();
		playGame();
	} while (playAgain());

	
	return 0;
}

// Plays the game once. Use this in a loop to repeat the game.
void playGame()
{
	BCGame.reset();
	
	int32 maxTries = BCGame.getMaxTries();
	int32 currentTry = BCGame.getCurrentTry();

	//loop through the amount of turns for guessing
	//TODO change from FOR to WHILE once we error check guesses
	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTries) {
		FText guess = getValidGuess(); //TODO check for valid guess

		//Submit valid guess to game and receive counts
		FBullCowCount BullCowCount = BCGame.submitGuess(guess);

		//Print # of bulls and cows
		cout << "Bulls = " << BullCowCount.bulls;
		cout << ". Cows = " << BullCowCount.cows;
		
		cout << endl;
	}

	//TODO summarize game
	return;
}

bool playAgain() {

	FText response = "";

	// ask user
	cout << "Do you want to play again?" << endl;
	getline(cin, response);
	
	//Return either true or false
	return (response[0] == 'y');
}

void printGameSummary() {
	if (BCGame.isGameWon()) {
		cout << "WELL DONE - YOU WIN!" << endl;
	}

	else {
		cout << "Sorry, better luck next time!" << endl;
	}
}

FText getValidGuess() {	//TODO change to getValidGuess
	EGuessStatus status = EGuessStatus::OK;
	FText guess = "";

	do {
		int32 currentTry = BCGame.getCurrentTry();

		//get the guess
		cout << "-----------------------------------------------------" << endl;
		cout << "Try " << currentTry << " of " << BCGame.getMaxTries();
		cout << ". What is your guess ? " << endl;
		getline(cin, guess);
		
		//Check the validity of the guess
		status = BCGame.checkGuess(guess);
		switch (status) {
			case EGuessStatus::Wrong_Length:
				cout << "Please enter a " << BCGame.getHiddenWordLength()
					<< " letter word." << endl;
				break;
			case EGuessStatus::Not_Isogram:
				cout << "Please enter a word without repeating letters" << endl;
				break;
			case EGuessStatus::Not_Lowercase:
				cout << "Please type in a response with all lowercase letters." << endl;
				break;
			default: break;
		}
	} while (status != EGuessStatus::OK);

	return guess;
}

// Introduce the game
void printIntro()
{
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << endl;
	cout << "          }   {         ___ " << endl;
	cout << "          (o o)        (o o) " << endl;
	cout << "   /-------\\ /          \\ /-------\\ " << endl;
	cout << "  / | BULL |O            O| COW  | \\ " << endl;
	cout << " *  |-,--- |              |------|  * " << endl;
	cout << "    ^      ^              ^      ^ " << endl;
	cout << "Can you guess the " << BCGame.getHiddenWordLength();
	cout << " letter isogram I'm thinking of?\n";
	cout << endl;
	return;
}