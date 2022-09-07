#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void initialize_game_state(char word[], char game_state[], bool already_guessed[26]);
bool update_game_state(char guess, const char word[], char game_state[]);
void print_game_state(const char word[], char game_state[], bool already_guessed[26], int *missed);
char get_guess(void);
bool won(const char word[], char game_state[]);
bool previous_guess(char guess, bool already_guessed[26]);

int main() 
{
  const int full_length = 100;
  char word[full_length];
  char game_state[full_length];
  bool already_guessed[26];
  char guess;
  bool result;
  const char *words_list[] = {"SAUSAGE", "CHICKEN", "MILK", "SODA", "HAM", "BEEF", "PORK", "PANCAKE", "EGG", "SANDWICH"};

  printf("Running tests for function initialize_game_state.\n");
  for (size_t j = 0; j < 5; j++)
  {
    initialize_game_state(word, game_state, already_guessed);
    int word_length = strlen(word);
    int game_state_length = strlen(game_state);
    //check if word is from our list
    bool in_the_list = false;
    for (size_t i = 0; i < 10; i++)
    {
      if (!strcmp(word,words_list[i]))
      {
        in_the_list = true;
      }
    }
    assert(in_the_list);
    //check if word and game_state are the same size
    assert(word_length == game_state_length);
    //check game_state
    for (size_t i = 0; i < game_state_length; i++)
    {
      assert(game_state[i] == '_');
    }
    //check already_guessed
    for (size_t i = 0; i < 26; i++)
    {
      assert(already_guessed[i] == false);
    }
  }
  
  printf("Passed all the tests for function initialize_game_state!\n");


  printf("Running tests for function update_game_state.\n");
  
  strcpy(word, "SAUSAGE");
  //for a guess that exists in one places of the word 
  strcpy(game_state, "_______");
  guess = 'A';
  result = update_game_state(guess, word, game_state);
  char expected_state[] = "_A__A__";
  assert(result == true);
  assert(!strcmp(game_state,expected_state));
  
  //for a guess that exists in multiple places & the begining of the word 
  strcpy(game_state, "_______");
  strcpy(expected_state, "S__S___");
  guess = 'S';
  result = update_game_state(guess, word, game_state);
  assert(result == true);
  assert(!strcmp(game_state,expected_state));
  
  //for a guess that exists at the end of the word 
  strcpy(game_state, "_______");
  strcpy(expected_state, "______E");
  guess = 'E';
  result = update_game_state(guess, word, game_state);
  assert(result == true);
  assert(!strcmp(game_state,expected_state));

  //for a guess that doesn't exist in the word
  strcpy(game_state, "_______");
  strcpy(expected_state, "_______");
  guess = 'C';
  result = update_game_state(guess, word, game_state);
  assert(result == false);
  assert(!strcmp(game_state,expected_state));

  //test a guess for another word in the list (and the guess exists in multiple places & at the end of the word)
  strcpy(word, "EGG");
  //for a guess that exists in one places of the word 
  strcpy(game_state, "___");
  guess = 'G';
  result = update_game_state(guess, word, game_state);
  char expected_EGG[] = "_GG";
  assert(result == true);
  assert(!strcmp(game_state,expected_EGG));

  printf("Passed all the tests for function update_game_state!\n");

  /*
  printf("Running tests for function get_guess.\n");
  guess = get_guess();
  printf("guess: %c\n",guess);
  assert(isalpha(guess) != 0); 
  printf("Passed all the tests for function get_guess!\n");


  
  printf("Running test for function won. \n");
  strcpy(word, "SAUSAGE");
  strcpy(game_state, "SAUSAGE");
  result = won(word, game_state);
  assert(result == true);
  strcpy(game_state, "CHICKEN");
  result = won(word, game_state);
  assert(result == false);
  strcpy(game_state, "SAUSAG");
  result = won(word, game_state);
  assert(result == false);
  printf("Passed all the tests for function won!\n");

  printf("Running test for function previous_guess.\n");
  
  printf("Passed all the tests for function previous_guess!\n");
  */
  
  return(0);
}
