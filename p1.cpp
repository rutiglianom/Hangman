// Matthew Rutigliano
// P1: Hangman
// Purpose: Implements the "hangman" class to run a game of hangman.
// Inputs: Filepath of a list of words, guessed letters
// Process: Filepath is used to select the mystery word. Once it has been inputted,
//          a random word is selected, the hangman and available letters are printed onto
//          the screen, and the user is asked to guess letters. Each right guess reveals letters
//          in the word, with each wrong guess bringing another section of the hangman's
//          body. The game goes until the word is revealed or the hangman is complete, when
//          the game's statistics are shown and the user is asked if they'd like to play again
//          with another word.
// Outputs: Hangman graphics, available letters, number of games won and lost, number of words
//          inputted and played

#include <iostream>
#include <string>
#include <cctype>

#include "hangman.h"

using namespace std;

int main()
{
  Hangman game; // Creation of Hangman object
  char letter;
  bool gameOver = false;
  bool gameWon = false;
  string filename;

  char ans;
  bool repeat = true;
  
  // Displaying Welcome Message, asking user to play and inputting filepath
  cout << "Welcome to Hangman!\nHangman is a game about guessing the letters of a word.\nEach wrong guess puts another body part in the onscreen gallows.\n";
  cout << "The game ends when the body is complete, or all the letters have been guessed.\nThink Wheel of fortune, but more morbid.\n\n";
  cout << "Would you like to play Hangman? Y/N ";
  cin >> ans;
  ans = toupper(ans);
  if (ans == 'Y')
    {
      repeat = true;
      cin.ignore();
      cout << "Please enter a filepath for words to be read from:" << endl;
      getline(cin,filename);

      // Loading file
      if(!game.initializeFile(filename))
        {
          cout << "file problem...exiting" << endl;
          return 0;
        }
      else
        {
          cout << "file loaded OK" << endl << endl;
        }
    }
  else
    {
      repeat = false;
    }
  
  // Main game loop
  while (repeat == true)
    {
      // display game statistics
      game.displayStatistics();  
      
      // randomly chooses new word from list of words
      game.newWord();

      // displays the hangman body
      game.displayGame();

      // resets gameOver and gameWon
      gameOver = false;
      gameWon = false;

      // keep guessing letters until gaveOver or gameWon
      while (!gameOver)
        {
          cout << "What letter? ";
	      cin >> letter;

          // processes the user's guess
          game.guess(toupper(letter), gameOver, gameWon);

          // displays the updated hangman body
          game.displayGame();
        }

      // displays the word
      game.revealWord();

      // displays whether game was won
      if (gameWon)
        {
          cout << "You won!" << endl;
        }

      // asks user if they want to continue playing
      cout << "Would you like to keep playing? Y/N ";
      cin >> ans;
      ans = toupper(ans);
      if (ans == 'Y')
        {
          repeat = true;
        }
      else
        {
          repeat = false;
        }
    }

   // display final game statistics 
  game.displayStatistics();

  cout << "Thank you for playing!" << endl;

  return 0;
}
