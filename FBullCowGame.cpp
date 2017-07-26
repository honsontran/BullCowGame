#pragma once

#include "FBullCowGame.h"
# include <map>
#include <ctype.h>


//Unreal syntax
# define TMap std::map
using int32 = int;

int FBullCowGame::getCurrentTry() const { return currentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return hiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameIsWon; }

int FBullCowGame::getMaxTries() const {
	TMap<int32, int32> lengthToTries{ {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
	return lengthToTries[hiddenWord.length()];
}

//constructor
FBullCowGame::FBullCowGame() { reset(); }

void FBullCowGame::reset() {
	currentTry = 1;

	constexpr int32 MAX_TRIES = 8;
	maxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	hiddenWord = HIDDEN_WORD;

	bGameIsWon = false;
}

EGuessStatus FBullCowGame::checkGuess(FString guess) const {
	//if guess isn't an isogram
	if (!isIsogram(guess)) {
		return EGuessStatus::Not_Isogram;
	}

	//if guess isn't all lowercase
	else if (!isIsogram(guess)) {
		return EGuessStatus::Not_Isogram;
	}

	//if not correct length
	else if (guess.length() != getHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}

	//else, return true
	return EGuessStatus::OK;

}

//receives a VALID guess, increments turn + returns count
FBullCowCount FBullCowGame::submitGuess(FString guess) {
	//increment the turn number
	currentTry++;

	//setup a return variableopp	
	FBullCowCount BullCowCount;

	int32 wordLength = hiddenWord.length();

	//loop through all letter in the guess
	for (int32 i = 0; i < wordLength; i++) {		
		//compare letters against the hidden word
		for (int32 j = 0; j < wordLength; j++) {
			
			//check if there is a matching char in the string
			if (guess[i] == hiddenWord[j]) {				
				if (i == j) {	//if they are the same index
					BullCowCount.bulls++;
				}
				else {
					BullCowCount.cows++;
				}
			}

		}
	}
	if (BullCowCount.bulls == wordLength) {
		bGameIsWon = true;
	}

	else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::isLowercase(FString word) const {
	
	if (word.length() <= 1) { return true; }

	for (auto letter : word) {
		if (islower(letter)) {
			return true;
		}
	}

	return false;
}

bool FBullCowGame::isIsogram(FString word) const {
	//a single letter or empty string is an isogram
	if (word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;	//setup our map

	for (auto letter : word) {
		letter = tolower(letter);	//store and retreat only lowercase cases

		if (LetterSeen[letter]) {
			return false;
		}
		else {
			LetterSeen[letter] = true; //add letter to the map
		}
	}

	return true;
}
