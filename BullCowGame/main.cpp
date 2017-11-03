/* This is the console executable that makes use of the BullCow class
This acts as teh view in MVC pattern and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using int32 = int;
using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;					//Instantiate a new game

int main()
{
	PrintIntro();
	do
	{
		PlayGame();
	} while (AskToPlayAgain());
	return 0;							//Exit Application
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is not won and while there are still tries remaining.
		while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries )
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess); // Submit valid guess to the game and receive counts

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
		PrintGameSummary();
		return;
}

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "         }   {            ___ " << std::endl;
	std::cout << "         (o o)           (o o) " << std::endl;
	std::cout << "  /-------\\ /             \\ /-------\\ " << std::endl;
	std::cout << " / | BULL |O               O| COW  | \\ " << std::endl;
	std::cout << "*  |-,--- |                 |------|  * " << std::endl;
	std::cout << "   ^      ^                 ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

FText GetValidGuess() //get a guess from the player
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		std::cout << "Try " << BCGame.GetCurrentTry() << ". of " << BCGame.GetMaxTries() << " Enter Your Guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Invalid_Status:
			std::cout << "Enter a Guess.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an Isogram (each letter may appear only once).\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " Letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word that is all lower case.\n";
			break;
		default:
			break;
		} std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get "OK" status
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	getline(std::cin, Response);
	
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You won the game!\n\n";
	}
	else
	{
		std::cout << "Better luck next time.\n\n";
	}
}
