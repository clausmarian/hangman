#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>

/**
* Clear the console screen
**/
void clearConsole()
{
	std::cout << "\033[2J\033[1;1H";
}

/**
* Transform the chars of a string to lowercase
**/
void toLowerCase(std::string &s)
{
	for(char &c : s)
		c = tolower(c);
}

/**
* Style the string for better readability
**/
std::string guessedWordStyled(std::string s)
{
	std::string res;
	char next;
	
	for(int i = 0; i < s.length(); i++) {
		char c = s[i];
		next = (i < s.length()) ? s[i + 1] : 'a';
		
		// Only place whitespace after the underscore if the next letter is an underscore or whitespace
		if(c == '_')
			res += (next == '_' || next == ' ') ? "_ " : "_";
		else
			res += c;
	}
	
	return res;
}

/**
* Run the hangman game
**/
void game()
{
	const std::array<std::string, 20> WORDS{"book", "frame", "computer", "door", "printer", "equation", "language", "blanket", "bathroom", "toilet", "rubber band", "ceiling", "duck", "dog", "cat", "avatar", "42", "beer", "paper", "notepad"};
	std::string userIn, word;
	int maxTries;
	
	/*------------------------------------------
		Max tries input
	------------------------------------------*/
	
	// Display info to the user
	std::cout << "How many tries do you want to have? (1-5)" << std::endl;
	
	do {
		std::cin >> userIn;
		
		// Try converting the input to an integer
		if(isdigit(userIn[0]) && userIn.length() == 1)
			maxTries = std::stoi(userIn);
		else
			// The input isn't a valid number
			std::cout << "Invalid input!" << std::endl;
	// The amount of tries must be between 1 and 5
	} while(maxTries < 1 || maxTries > 5);
	
	// Success
	std::cout << "You have " << maxTries << (maxTries == 1 ? " try!" : " tries!") << std::endl;
	
	
	/*------------------------------------------
		User defined or random word
	------------------------------------------*/
	
	bool wordChosen = 0;
	
	// Tell the user to enter a word
	std::cout << "Enter a word or omit to choose a random word!" << std::endl;
	
	// Extract characters from the input and discard them
	std::cin.ignore();
	
	do {
		// Get a full line as input
		getline(std::cin, userIn);
		
		// Empty input to choose a random word
		if(userIn.length() == 0) {
			wordChosen = 1;
		}
		
		// Check if the input only contains valid characters and is not empty
		for(char c : userIn) {
			// Transform the character to lowercase
			c = tolower(c);
			
			if((c != ' ')) {
				// Only alphabetic letters and whitespace are allowed, - is allowed
				if(!isalpha(c) && c != '-') {
					wordChosen = 0;
					break;
				}
				wordChosen = 1;
			}
		}
		
		// The input contains not allowed characters or is empty
		if(!wordChosen)
			std::cout << "Invalid input!" << std::endl;
	} while(!wordChosen);

	// Random word
	if(userIn.length() == 0) {
		// RNG seed
		srand(time(NULL));
		
		// Choose a random word
		word = WORDS[rand()%WORDS.size()];
		
		std::cout << "A random word was chosen!" << std::endl;
	} else {
		// Word defined by the user
		toLowerCase(userIn);	
		word = userIn;
		
		// Clear the console so that the other user can't see it
		clearConsole();
		
		std::cout << "Word defined!" << std::endl;
	}
	
	
	/*------------------------------------------
		Main game
	------------------------------------------*/
	
	std::string guessedWord, guessedWordBefore;
	
	// Hide the word (all characters except whitespace are being changed to '_')
	for(char c : word) 
		guessedWord += (c == ' ') ? ' ' : '_';

	// Display the hidden word to the user
	std::cout << "The word is \'" + guessedWordStyled(guessedWord) + "\'" << std::endl;
	
	do {
		// Get a full line as input
		getline(std::cin, userIn);
		
		// Convert the std::string to lowercase
		toLowerCase(userIn);
		
		// The input is empty
		if(userIn.length() == 0) {
			std::cout << "Invalid input!" << std::endl;
			continue;
		}
			
		// The input is a character
		if(userIn.length() == 1) {
			char cinput = userIn[0];
			
			// Check if the character has already been guessed by the user
			if(guessedWord.find(cinput) != std::string::npos) {
				std::cout << "You've already guessed this letter right!" << std::endl;
				continue;
			}
			
			// Copy the hidden word to compare it with its copy later
			guessedWordBefore = guessedWord;
			
			// Check if the word contains the character
			for(int i = 0; i < word.length(); i++) {
				char cWord = word[i];
				
				// Word contains the character
				if(cinput == cWord) {
					// Replace the placeholders with the character
					guessedWord[i] = cWord;
				}
			}
			
			// The word doesn't contain the character, decrement maxTries
			if(guessedWord == guessedWordBefore) {
				maxTries--;
				
				// Immediately cancel the game if the tries reach 0
				if(maxTries == 0)
					break;
				
				// Display info to the user
				std::cout << "The word doesn't contain \'" << cinput << "\', you have " << maxTries << (maxTries == 1 ? " try left!" : " tries left!") << std::endl;
			} else {
				// Display the hidden work with replaced characters
				std::cout << "The word is \'" + guessedWordStyled(guessedWord) + "\'" << std::endl;
			}
		// The input is greater than 1 character so the input is a word
		} else {
			// The word typed by the user is not the word, decrement maxTries
			if(userIn != word) {
				maxTries--;
				
				// Immediately cancel the game if the tries reach 0
				if(maxTries == 0)
					break;
				
				// Display info to the user
				std::cout << "The word isn't \'" << userIn << "\', you have " << maxTries << (maxTries == 1 ? " try left!" : " tries left!") << std::endl;
			
			// The word typed by the user is the word
			} else {
				guessedWord = word;
			}
		}
	} while((guessedWord != word) && (maxTries > 0));
	
	// Win
	if(guessedWord == word)
		std::cout << "You won!" << std::endl;
	// Lose
	else
		std::cout << "You lost! The word was \'" + word + "\'!" << std::endl;
}

int main()
{
	/*
		Design
	*/
	
	// Set the console title
	std::cout << "\033]0;" << "Hangman" << "\007";
	
	// Hangman ascii-art
	std::cout << "  _   _" << std::endl;
	std::cout << " | | | |" << std::endl;                                            
	std::cout << " | |_| | __ _ _ __   __ _ _ __ ___   __ _ _ __" << std::endl;  
	std::cout << " | '_' |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\" << std::endl; 
	std::cout << " | | | | (_| | | | | (_| | | | | | | (_| | | | |" << std::endl;
	std::cout << " |_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|" << std::endl;
	std::cout << "                     __/ |" << std::endl;                      
	std::cout << "                    |___/" << std::endl;
	
	/*
		Program
	*/
	
	// Vars
	bool running = 1;
	std::string userIn;
	
	// Welcome
	std::cout << "Welcome to hangman!" << std::endl;
	
	// Start a game of hangman
	game();
	
	do {
		// Ask the user if they want to play another round
		std::cout << "Do you want to play again? (Y)" << std::endl;
		getline(std::cin, userIn);
		
		// Close the program
		if(userIn.length() == 0 || userIn.length() > 1 || tolower(userIn[0]) != 'y')
			running = 0;
		// Start a game of hangman
		else
			game();
	} while(running);
	
	return 0;
}
