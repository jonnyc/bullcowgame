#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	bGameIsWon = false;
	return;
}


FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) // recieves a VALID guess, increments turn and returns count
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length(); //setup hidden word length variable
	int32 GuessLength = Guess.length(); // assuming same length as guess
	
	// loop through all letters in the guess
	for (int32 i = 0; i < GuessLength; i++)
	{
		// compare letters agains the hidden word
		for (int32 j = 0; j < WordLength; j++)
		{
			// if they match then
			if ((i == j) && (Guess[i] == MyHiddenWord[j])) // if they're in the same place, increment bulls
			{
				BullCowCount.Bulls++;
			}
			else if (Guess[i] == MyHiddenWord[j])
			{
				BullCowCount.Cows++;
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // set up the map
	for (auto Letter : Word) // for all letters of the word 
	{
		Letter = tolower(Letter); // lowercase the letter
		if (LetterSeen[Letter]) 
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return true;
		}
	}
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; //TODO write function
	}
	else if (IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; //TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}
