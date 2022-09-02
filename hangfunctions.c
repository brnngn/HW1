#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

// char *options[8] = { "|||========|||\n", 
//                     "|||     \n", 
//                     "|||     \n", 
//                     "|||     \n", 
//                     "|||     \n", 
//                     "|||     \n", 
//                     "|||     \n", 
//                     "=============="};
/*
This function 
*/
void initialize_game_state(char word[], char game_state[], bool already_guessed[26]) {
    srand(time(0));
    const int length_of_list = 10;
    const char *words_list[length_of_list] = {"SAUSAGE", "CHICKEN", "MILK", "SODA", "HAM", "BEEF", "PORK", "PANCAKE", "EGG", "SANDWICH"};
    const int random_index = (rand() % length_of_list);
    strcpy(word, words_list[random_index]);
    strcpy(game_state, word);
    int length_of_game_state = strlen(game_state);
    for (size_t i = 0; i < length_of_game_state; i++)
    {
        game_state[i] = '_';
    }
    for (size_t i = 0; i < 26; i++)
    {
        already_guessed[i] = false;
    }
    //printf("%s",word);
    //printf("%s",game_state);
}

/*
This function 
*/
bool update_game_state(char guess, const char word[], char game_state[]) {
    int word_length = strlen(word);
    bool if_contained = false;
    for (size_t i = 0; i < word_length; i++)
    {
        if (guess == word[i]){
            game_state[i] = guess;
            if_contained = true;
        }
    }
    //printf("%s",word);
    //printf("%s",game_state);
    return if_contained;
}


/*
This function 
*/
char get_guess() {
    char guess;
    char readtillend[60];
    int count;
    while (fgets(&guess, 2, stdin)!= NULL){
        fgets(readtillend, 60, stdin);
        if ( (!isalpha(guess)) || (readtillend[0] != '\n') ){
            
            printf("Please input a character: ");
        }
        else{
            return toupper(guess);
        }
    }
    return toupper(guess);  
}

// /*
// This function 
// */
bool won(const char word[], char game_state[]) {
    int word_length = strlen(word);
    for (size_t i = 0; i < word_length; i++)
    {
        if (game_state[i] != word[i]){
            return false;
        }
    }
    return true;
}

/*
This function checks if the character was already guessed.
*/
int previous_guess(char guess, bool already_guessed[26]) {
    int index = guess - 'A';
    return already_guessed[index];
}
 
// /*
// This function 
// */
void print_game_state(const char word[], char game_state[], bool already_guessed[26]) {

}


int main() {
    // char guess;
    // printf("User input: ");
    // guess = get_guess();
    // printf("User input is %c", guess);
    const int full_length = 100;
    char word[full_length];
    char game_state[full_length];
    bool already_guessed[26];
    char guess;
    initialize_game_state(word, game_state, already_guessed);
    while(!won(word, game_state)){
        printf("User input: ");
        guess = get_guess();
        if (! previous_guess(guess,already_guessed)){
            int index = guess - 'A';
            already_guessed[index] = true;
        }else{
            printf("You already guessed this one! Try again:");
            guess = get_guess();
        }
        update_game_state(guess, word, game_state);
        printf("%s",word);
        printf("%s",game_state);
    }
    //printf("User input: ");
    //char guess = get_guess();
    //update_game_state(guess, word, game_state);
    //bool sth[26];
    //char guess;
    //printf("%d", previous_guess(guess, sth));
    return 0;
}