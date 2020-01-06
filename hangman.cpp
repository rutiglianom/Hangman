// Matthew Rutigliano
// Lab 6: More Hangman
// Purpose: Implement Hangman constructor, initialize file, display statistics and reveal word

#include "hangman.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#ifndef HANGMAN_H
#define HANGMAN_H

Hangman::Hangman()
{
  // Initializes word array
  
  for(int i = 0; i < WORD_LIST_SIZE; i++)
    {
      words[i].word  = "";
      words[i].isAvailable = true;
    }
  
  const int ASCIIA = 65;     // 65 is the ASCII value of A. Since ASCII letters are alphabetized
  char asciiVal = 0;   // starting at A, I populate the ith number of the alphabet array by
                       // setting it equal to 65 + i.
  for(int i = 0; i < ALPHA_SIZE; i++)
    {
      asciiVal = ASCIIA + i;
      alphabet[i].letter = asciiVal;
      alphabet[i].isAvailable = true;
    }

  // Initializes words and statistics
  
  currentWord = "";
  displayWord = "";
  gamesWon = 0;
  gamesLost = 0;
  numWordsRead = 0;
  numWordsAvailable = 0;

  // initialize hangman body array
  
  body[0].firstLine = "    ----\n";                                              
  body[1].firstLine = "    |  |\n";                                              
  body[2].firstLine = "       |\n";                                              
  body[2].secondLine = "    O  |\n";                                             
  body[3].firstLine = "       |\n";                                              
  body[3].secondLine = "    |  |\n";                                             
  body[4].firstLine = "       |\n";                                              
  body[4].secondLine = "   -|  |\n";                                             
  body[4].thirdLine = "   -|- |\n";                                              
  body[5].firstLine = "       |\n";                                              
  body[5].secondLine = "    |  |\n";                                             
  body[6].firstLine = "       |\n";                                              
  body[6].secondLine = "   /   |\n";                                             
  body[6].thirdLine = "   / \\ |\n";                                              
  body[7].firstLine = "       |\n";                                              
  body[8].firstLine = "_______|___\n";                                           

  // initially set displaySecond and displayThird to false 
  // for all body parts
  
  for (int i = 0; i < BODY_SIZE; i++)
    {
      body[i].displaySecond = false;                                               
      body[i].displayThird = false;                                                
  	}
}

bool Hangman::initializeFile(string filename)
{
  // Reads inputted word file into word array
  
  string data;
  ifstream infile;
  infile.open(filename);

  if (infile)
    {
      while (infile >> data)
        {
          words[numWordsRead].word = data;
          numWordsRead++;
        }
    }
  else
    {
      cout << "Error\n";
      return false;
    }
  infile.close();
  
  numWordsAvailable = numWordsRead;

	return true;
}

void Hangman::displayStatistics()
{
  // Outputs statistics at the end of each game
  
  cout << "Games won: " << gamesWon << endl;
  cout << "Games lost: " << gamesLost << endl;
  cout << "There have been " << numWordsRead << " words read from file" << endl;
  cout << "There are " << numWordsAvailable << " available for play" << endl;  
}

bool Hangman::newWord()
{
  // Generates random integer within bounds of word array, checks to see if word
  // at that place is available then sets it as current word if so. If not, another
  // word is generated.

  bool search;
  int LENGTH;
  const int ASCIIA = 65;
  char asciiVal = 0;
  int wordChoice = 0;
  
  if (numWordsAvailable)
    {
      unsigned seed = time(0);
      srand(seed);

      search = true;
      
      while (search == true)
        {
          wordChoice =  rand() % numWordsRead;
          if (words[wordChoice].isAvailable == true)
            {
              currentWord = words[wordChoice].word;
              words[wordChoice].isAvailable = false;
              --numWordsAvailable;
              search = false;
            }
        }

      // Sets displayed word as all underscores
      
      LENGTH = currentWord.length();
      for(int i = 0; i < LENGTH; i++)
        displayWord[i] ='_';

      // Resets alphabet and body array for each new game
      
      for(int i = 0; i < ALPHA_SIZE; i++)
        {
          asciiVal = ASCIIA + i;
          alphabet[i].letter = asciiVal;
          alphabet[i].isAvailable = true;
        }

      for (int i = 0; i < BODY_SIZE; i++)
        {
          body[i].displaySecond = false;
          body[i].displayThird = false;
        }
      
      return true;
    }
  else
    {
      return false;
    }
}

void Hangman::displayGame()
{
  int LENGTH = currentWord.length();
  
  // Prints last line set to true in body array
  
  for(int i = 0; i < BODY_SIZE; i++)
    {
      if (body[i].displayThird == true)
        {
          cout << body[i].thirdLine;
        }
      else if (body[i].displaySecond == true)
        {
          cout << body[i].secondLine;
        }
      else
        {
          cout << body[i].firstLine;
        }
    }
  
   cout << endl << endl;

   // Prints guessed letters
 
   for(int i = 0; i < LENGTH; i++)
     {
       cout << displayWord[i] << " ";
     }

   cout << endl << endl;

  // Prints letters of the alphabet array if they haven't been guessed

   for(int i = 0; i < ALPHA_SIZE; i++)
     {
       if (alphabet[i].isAvailable == true)
         cout << alphabet[i].letter << " ";
       else
         cout << "_ ";
     }
   cout << endl << endl;
}

bool Hangman::guess(char letter, bool& done, bool& won)
{
  
  int LENGTH = currentWord.length();
  int letterCount;
  bool update = true;  // In my cutthroat hangman, letters are wrong unless proven right

  // Checks to see if letter has been guessed already
  
  for(int i = 0; i < ALPHA_SIZE; i++)
    {
      if (letter == alphabet[i].letter)
        {
          if (alphabet[i].isAvailable == true)
            {
              alphabet[i].isAvailable = false;
            }
          else
            {
              cout << "Letter has already been guessed" << endl;
              return true;
            }
        }
    }

  // Checks to see if guessed letter is in the word, setting the update boolean to false if
  // it is while updating the displayed string to contain it

  for(int i = 0; i < LENGTH; i++)
    {
      if (currentWord[i] == letter)
        {
          update = false;
          displayWord[i] = letter;
        }
    }

  // Updating body array: If update wasn't set to false by a correct guess, the update loop is
  // executed, in which a for loop goes through the body array checking if (a) a second or third
  // line exists and (b) if it's set to false. If it is, this is changed to true and the loop is broken,
  // setting the next stage of the body to display.

  while (update == true)
    {
      for (int i = 0; i < BODY_SIZE; i++)
        {
          if (body[i].secondLine != "")
            {
              if (body[i].displaySecond == false)
                {
                  body[i].displaySecond = true;
                  update = false;
                  break;
                }
              else if (body[i].thirdLine != "")
                {
                  if (body[i].displayThird == false)
                    {
                      body[i].displayThird = true;
                      update = false;
                      break;
                    }
                }
            }
        }
    }

  // Checking if game was lost: If the last third of the body (line 6) is set to display,
  // the game is set to done.

  if (body[6].displayThird == true)
    {
      gamesLost++;
      done = true;
      return true;
    }

  // Checking if game was won: letterCount is incremented for every unguessed letter in
  // the displayed word. If letterCount is zero afterwards, the game is set to won and done.
  
  for (int i = 0; i < LENGTH; i++)
    {
      if (displayWord[i] == '_')
        {
          letterCount++;
        }
    }
  if (letterCount == 0)
    {
      gamesWon++;
      won = true;
      done = true;
      return true;
    }

  return true;
}

void Hangman::revealWord()
{
  // Outputs currentWord at the end of each game
  
  cout << "The word was " << currentWord << endl;
}

#endif
