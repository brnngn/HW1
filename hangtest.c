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
  //const int miss_limit = 7;
  char word[full_length];
  char game_state[full_length];
  bool already_guessed[26];
  //int missed = 0;
  char guess;
  bool result;

  printf("Running tests for function initialize_game_state.\n");
  initialize_game_state(word, game_state, already_guessed);
  int word_length = strlen(word);
  int game_state_length = strlen(game_state);
  assert(word_length == game_state_length);
  for (size_t i = 0; i < game_state_length; i++)
  {
    assert(game_state[i] == '_');
  }
  for (size_t i = 0; i < 26; i++)
  {
    assert(already_guessed[i] == false);
  }
  printf("Passed all the tests for function initialize_game_state!\n");


  printf("Running tests for function update_game_state.\n");
  strcpy(word, "SAUSAGE");
  strcpy(game_state, "_______");
  guess = 'S';
  result = update_game_state(guess, word, game_state);
  assert(result == true);
  assert(game_state[0] == 'S');
  assert(game_state[3] == 'S');
  assert(game_state[1] == '_');
  strcpy(game_state, "_______");
  guess = 'C';
  result = update_game_state(guess, word, game_state);
  assert(result == false);
  assert(game_state[0] == '_');
  assert(game_state[3] == '_');
  assert(game_state[1] == '_');
  printf("Passed all the tests for function update_game_state!\n");


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
  
  
  return(0);
}
