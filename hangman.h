// Matthew Rutigliano
// Hangman class header file
// Purpose: The hangman object has all the attributes necessary to run
//          a game of hangman. A file of words is inputted with one being randomly selected,
//          a hangman graphic is drawn onto the screen along with the list of letters
//          available to guess, the guess is processed with another element of either
//          the word or body revealed depending on its accuracy, and at the end the player's
//          statistics are stored and displayed.

#include <string>
using namespace std;

class Hangman
{
 public:
  Hangman();
  // Default constructor
  // Precondition: None
  // Postcondition: All private attributes have been initialized

  bool initializeFile(string filename);
  // Input a file of words to populate the word array
  // Precondition: Filepath must exist
  // Postcondition: Words array is now populated

  void displayStatistics();
  // Display the player's statistics
  // Precondition: gamesWon and gamesLost must be initialized, words must
  //               be inputted
  // Postcondition: None
  
  bool newWord();
  // Use a random integer to select a word from the words array, reset all
  // guessing arrays for each new game
  // Precondition: Words array must be populated
  // Postcondition: currentWord and displayWord are now assigned, alphabet and
  //                body array are reset
  
  void displayGame();
  // Output the body graphic and letters available to guess
  // Precondition: Body array and alphabet array have been initialized
  // Postcondition: None
  
  bool guess(char letter, bool& done, bool& won);
  // Process the user's guess, rewarding or penalizing them depending on the accuracy
  // Precondition: User has inputted an unguessed letter
  // Postcondition: Guessed letter becomes unavailable, body array or displayed word are
  //                updated depending on the guess
  
  void revealWord();
  // Reveal the displayed word at the end of the game
  // Precondition: currentWord has been assigned
  // Postcondition: None

 private:

  // Constant sizes of arrays
  static const int BODY_SIZE = 9;
  static const int WORD_LIST_SIZE = 100;
  static const int ALPHA_SIZE = 26;

  // Structure holding first second and third lines of body graphic, and booleans for
  // displaying the second or third line
  struct BodyPart{
    string firstLine;
	string secondLine;
	string thirdLine;
    bool displaySecond;
	bool displayThird;
  };

  // Structure holding words and whether or not they've been played
  struct WordInfo
  {
    string word;
	bool isAvailable;
  };

  // Structure holding letters and whether or not they've been guessed
  struct AlphaInfo
  {
    char letter;
	bool isAvailable;
  };

  // Arrays for body graphics, words and alphabet
  BodyPart body[BODY_SIZE];
  WordInfo words[WORD_LIST_SIZE]; 	
  AlphaInfo alphabet[ALPHA_SIZE];

  // Strings holding the current word, displayed word and game statistics
  string currentWord;
  string displayWord;
  int gamesWon;
  int gamesLost;
  int numWordsRead;
  int numWordsAvailable;

};
