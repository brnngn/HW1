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
void print_game_state(const char word[], char game_state[], bool already_guessed[26], int *missed);
char get_guess(void);
bool won(const char word[], char game_state[]);
bool previous_guess(char guess, bool already_guessed[26]);


int main(int argc, char **argv) {
    const int full_length = 100;
    const int miss_limit = 7;
    char word[full_length];
    char game_state[full_length];
    bool already_guessed[26];
    int missed = 0;
    initialize_game_state(word, game_state, already_guessed);
    while(!won(word, game_state) && (missed < miss_limit)){
        print_game_state(word, game_state, already_guessed, &missed);
    }
    if (won(word, game_state)){
        printf("Yes it's %s!\nYou WON and made the stick person happy!:)\n",word);
    }
    return 0;
}
