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
  
  //for a guess that exists in multiple places & the beginning of the word 
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

  printf("Running tests for function get_guess.\n");
  printf("(TIPs!!! Suggested input for test cases:\n\tvalid cases: single letter (for both lower and upper cases)\n\tinvalid cases: digit(s), space and/or other special character(s) mixed with letter(s), empty input is also invalid)\n");
  printf("Please input your guess: ");
  guess = get_guess();
  printf("guess: %c\n",guess);
  assert(isalpha(guess) != 0); 
  printf("Passed all the tests for function get_guess!\n");


  printf("Running test for function won. \n");
  //when won
  strcpy(word, "SAUSAGE");
  strcpy(game_state, "SAUSAGE");
  result = won(word, game_state);
  assert(result == true);
  //when not winning with no letter guessed right
  strcpy(game_state, "_______");
  result = won(word, game_state);
  assert(result == false);
  //when not winning with only last letter missed
  strcpy(game_state, "SAUSAG_");
  result = won(word, game_state);
  assert(result == false);
  //when not winning with only first letter missed
  strcpy(game_state, "_AUSAGE");
  result = won(word, game_state);
  assert(result == false);
  //when not winning with only one letter in the middle missed
  strcpy(game_state, "SA_SAGE");
  result = won(word, game_state);
  assert(result == false);
  printf("Passed all the tests for function won!\n");
  
  printf("Running test for function previous_guess.\n");
  //case 1: letter A has not been guessed
  guess = 'A';
  result = previous_guess(guess, already_guessed);
  assert(result == false);

  //case 2: letter A has been guessed
  already_guessed[0] = true; //letter A has been guessed
  result = previous_guess(guess, already_guessed);
  assert(result == true);

  //case 3: different un-guessed letter
  guess = 'H';
  result = previous_guess(guess, already_guessed);
  assert(result == false);

  //case 4: different un-guessed letter
  guess = 'Z';
  result = previous_guess(guess, already_guessed);
  assert(result == false);

  //case 5: different guessed letter
  int index = guess - 'A';
  already_guessed[index] = true;
  result = previous_guess(guess, already_guessed);
  assert(result == true);
  printf("Passed all the tests for function previous_guess!\n");
  
  printf("Running test for function print_game_state.\n ");
  int missed = 0;
  strcpy(word, "EGG");
  strcpy(game_state, "___");
  for (size_t i = 0; i < 26; i++)
  {
      already_guessed[i] = false;
  }
  int n_guessed;
  int n_last_guessed = 0;
  int last_missed = 0;
  printf("____________This is a test run, the word is EGG.______________\n ");
  while(!won(word, game_state) && (missed < 7)){
        n_guessed = 0;
        print_game_state(word, game_state, already_guessed, &missed);
        for (size_t i = 0; i < 26; i++)
        {
          if (already_guessed[i] == true)
          {
            n_guessed ++;
          }
        }
        assert(n_guessed == (n_last_guessed+1));
        n_last_guessed ++;
        assert( (missed == (last_missed+1))  || (missed == last_missed) );
        last_missed++;
  }
  if (won(word, game_state)){
        printf("Yes it's %s!\nYou WON and made the stick person happy!:)\n",word);
  }
  printf("Passed all the tests for function print_game_state!\n");
  
  
  
  return(0);
}
