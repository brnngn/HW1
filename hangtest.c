#include <assert.h>
#include <stdbool.h>
#include <stdio.h>


void initialize_game_state(char word[], char game_state[], bool already_guessed[26]);
bool update_game_state(char guess, const char word[], char game_state[]);
void print_game_state(const char word[], char game_state[], bool already_guessed[26], int *missed);
char get_guess(void);
bool won(const char word[], char game_state[]);
bool previous_guess(char guess, bool already_guessed[26]);

int main() 
{
  printf("This is a test...\n");

  return(0);
}