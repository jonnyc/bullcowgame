#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount						// all values initialized to 0
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame();						// Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;	

	void Reset();						//TODO make a more rich return value
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;					// See Constructor for initialization
	int32 MyMaxTries;					// See Constructor for initialization
	FString MyHiddenWord;				// See Constructor for initialization
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};