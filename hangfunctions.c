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
This function initializes the game by firstly, randomly select a word from a pre-determined list (consisting of only foods). It then initializes 
game_state to be exactly the same length as the chosen word but all letter are replaced with '_'. Finally, it initializes the already_guessed[26] 
array to contain all false values since this array is used to keep track of all the characters that the player guesses (the input of the user). Each 
element in the already_guessed[26] corresponds to a character in the English alphabet in the same order.
*/
void initialize_game_state(char word[], char game_state[], bool already_guessed[26]) {
    time_t t;
    srand((unsigned) time(&t));
    const int length_of_list = 10;
    const char *words_list[] = {"SAUSAGE", "CHICKEN", "MILK", "SODA", "HAM", "BEEF", "PORK", "PANCAKE", "EGG", "SANDWICH"};
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
}

/*
This function checks the word for the guessed letter. if the guessed letter appears in the word, the function updates game_state with the guess at any 
locations it appears. The function also returns whether the guessed letter appears in the word.
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
    return if_contained;
}
      
/*
This function asks for and reads the user input, i.e. which letter the user want to guess. 
Only when a letter from the English alphabet is input along with no other characters, 
the input is considered to be valid. In cases that the user enters invalid inputs (empty input, 
digits, words, sentences, special characters, etc.), the function will ask the user for another 
input till it gets a valid input.
*/
char get_guess() {
    char guess[2];
    char read_till_end[2];
    while (fgets(guess, 2, stdin) != NULL){
    	//if user hits return without any input: 
    	if (guess[0] == '\n')
    	{
    		printf("Please input a character: ");
    	}else{
            fgets(read_till_end, 2, stdin);
    		if ( (!isalpha(guess[0])) || (read_till_end[0] != '\n') )
    		{
            	while(read_till_end[0] != '\n')
            	{
            		fgets(read_till_end, 2, stdin);
           		}
            	printf("Please input a character: ");
        	}else{
            	return toupper(guess[0]);
        	}	
    	}
    }
    return toupper(guess[0]);  
}

/*
This function checks if all the letters in the word has been checked in the game_state. The function returns true if all the letters are guessed, meaning
the player has won the game. The function returns false if the player has not won yet. 
*/
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
This function checks if the character was already guessed. The function returns true if the letter is already guessed by the player; otherwise, the function
returns false.
*/
int previous_guess(char guess, bool already_guessed[26]) {
    int index = guess - 'A';
    return already_guessed[index];
}
 
/*
This function provides a user interface for the player. Specifically, it prints out the current game state and the letters already guessed in the following
format:
|||========|||
|||
|||
|||
|||
|||
|||
================
___
Already guessed: 
What is your guess? 
Bad/Good guess!
Missed:  
*/
void print_game_state(const char word[], char game_state[], bool already_guessed[26],int *missed) {
    int word_length = strlen(word);
    int miss_limit = 7;
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
    printf("Missed: %d\n", *missed);
    if ( *missed >= miss_limit){
        printf("%s",options[miss_limit]);
        printf("You lost and made stick-person sad...\nThe word was ");
        for (size_t i = 0; i < word_length; i++)
        {
            printf("%c",word[i]);
        }
        printf(".\n");
    }
}

