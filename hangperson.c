/*
Homework 1
Brian Nguyen and XD
CS 372: Operating Systems
8/31/2022 
*/

#include <stdio.h>
#include <stdbool.h>

void initialize_game_state(char word[], char game_state[], bool already_guessed[26]);
bool update_game_state(char guess, const char word[], char game_state[]);
void print_game_state(const char word[], char game_state[], bool already_guessed[26]);
char get_guess(void);
bool won(const char word[], char game_state[]);
bool previous_guess(char guess, bool already_guessed[26]);


int main(int argc, char **argv) {
    const int word_length = 100;
    char word[word_length];
    char game_state[word_length];
    bool already_guessed[26];
    initialize_game_state(word, game_state, already_guessed);
}