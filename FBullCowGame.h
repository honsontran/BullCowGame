/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
# include <string>

using namespace std;
using FString = string;
using int32 = int;

//all values initialized to 0
struct FBullCowCount {
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus {
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor
	
	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	EGuessStatus checkGuess(FString) const; // TODO make a more rich return value

	void reset();	//TODO make a more rich return
	FBullCowCount submitGuess(FString);

private:
	int32 currentTry;
	int32 maxTries;
	FString hiddenWord;
	bool bGameIsWon;

	bool isIsogram(FString) const;
	bool isLowercase(FString) const;
};