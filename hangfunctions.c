#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

char *options[8] = { "|||========|||\n|||     \n|||     \n|||     \n|||     \n|||     \n|||     \n==============\n",
"|||========|||\n|||   | \n|||     \n|||     \n|||     \n|||     \n|||     \n==============\n",
"|||========|||\n|||   | \n|||   O \n|||     \n|||     \n|||     \n|||     \n==============\n",
"|||========|||\n|||   | \n|||   O \n|||  /  \n|||     \n|||     \n|||     \n==============\n",
"|||========|||\n|||   | \n|||   O \n|||  /| \n|||     \n|||     \n|||     \n==============\n",
"|||========|||\n|||   | \n|||   O \n|||  /|\\\n|||     \n|||     \n|||     \n==============\n",
"|||========|||\n|||   | \n|||   O \n|||  /|\\\n|||  /  \n|||     \n|||     \n==============\n",
"|||========|||\n|||   | \n|||   O \n|||  /|\\\n|||  / \\\n|||     \n|||     \n==============\n"};

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
    char readtillend[60]; // TODO: INT_MAX?
    int count;
    while (fgets(&guess, 2, stdin)!= NULL){
        // TODO: NT_MAX?
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
void print_game_state(const char word[], char game_state[], bool already_guessed[26],int *missed) {
    int word_length = strlen(word);
    printf("%s",options[*missed]);
    for (size_t i = 0; i < word_length; i++)
    {
        printf("%c",game_state[i]);
    }
    printf("%s","\nAlready guessed: ");
    for (size_t i = 0; i < 26; i++)
    {
        if (already_guessed[i]){
            char guessed = 'A';
            guessed = guessed + i;
            printf("%c ",guessed);
        }
    }
    printf("%s","\nWhat is your guess? ");
    char guess = get_guess();
    if (! previous_guess(guess,already_guessed)){
        int index = guess - 'A';
        already_guessed[index] = true;
    }else{
        printf("You already guessed this one! Try again:");
        guess = get_guess();
    }
    if (update_game_state(guess, word, game_state)){
        printf("Good guess!\n");
    }else{
        printf("Bad guess!\n");
        *missed = *missed +1;
    }
    printf("Missed: %d", *missed);
    if ( *missed >= 7){
        printf("%s",options[7]);
        printf("You lost and made stick-person sad...\nThe word was ");
        for (size_t i = 0; i < word_length; i++)
        {
            printf("%c",word[i]);
        }
        printf(".\n");
    }
/*
_ _ _
Already guessed:
What is your guess? e
Good guess.
Missed: 0
*/
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
    int missed = 0;
    initialize_game_state(word, game_state, already_guessed);
    while(!won(word, game_state) && (missed < 7)){
        print_game_state(word, game_state, already_guessed, &missed);
    }
    if (won(word, game_state)){
        printf("You WON and made the stick person happy!:)");
    }

    //printf("User input: ");
    //char guess = get_guess();
    //update_game_state(guess, word, game_state);
    //bool sth[26];
    //char guess;
    //printf("%d", previous_guess(guess, sth));
    // options[1] = "|||   | \n";
    // options[2] = "|||   O \n";
    // options[3] = "|||  /  \n";
    // options[3] = "|||  /| \n";
    // options[3] = "|||  /|\\\n";
    // options[4] = "|||  /  \n";
    // options[4] = "|||  / \\\n";
    // for (size_t i = 0; i < 8; i++){
    //     printf("%s", options[i]);
    // }
    // char guessed = 'A';
    // guessed = guessed + 5;
    // printf("%c", guessed);
    return 0;
}