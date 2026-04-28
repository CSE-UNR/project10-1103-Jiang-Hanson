//Hanson Jiang
//4-21-2026

#include <stdio.h>
#include <stdbool.h>
#define STR_CAP 100
#define WORD_LEN 5
#define NUM_GUESSES 6
#define FILE_NAME "mystery.txt"

int get_word(const char file_name[], char word[]); // 	written 	checked
void get_guess(int guess_length, int num_guesses, int turn, char guess[]); // 	written 	checked
void lower_guess(int guess_length, char guess[]); // 	written 	checked
bool check_capital_win(int guess_length, char guess[], const char word[]); // 	written 	checked
void check_arrows(int guess_length, const char guess[], const char word[], char arrows_line[]); // 	written 	checked
void display_line(int line_length, const char line[]); // 	written
void display_guess_history(int turn, int guess_length, const char guesses[][guess_length], const char arrows_lines[][guess_length]); // 	written

int main () {
	char guesses[NUM_GUESSES][WORD_LEN], arrows_lines[NUM_GUESSES][WORD_LEN];
	char word[WORD_LEN], guess[WORD_LEN], arrows_line[WORD_LEN];
	int turn = 1;
	bool won = false;
	
	if (get_word(FILE_NAME, word) == 2) {
		printf("Sorry, could not get today's word. Try again tommorrow.\n");
		return 2;
	}
	while (!won && turn <= NUM_GUESSES) {
	
		get_guess(WORD_LEN, NUM_GUESSES, turn, guess);
		lower_guess(WORD_LEN, guess);
		
		won = check_capital_win(WORD_LEN, guess, word);
		
		if (!won) {
			check_arrows(WORD_LEN, guess, word, arrows_line);
			
			for(int col = 0; col < WORD_LEN; col++) {
				guesses[turn - 1][col] = guess[col];
				arrows_lines[turn - 1][col] = arrows_line[col];
			}
			display_guess_history(turn, WORD_LEN, guesses, arrows_lines);
			turn++;
		}
	}
	if (won) {
		printf("\t\t");
		display_line(WORD_LEN, guess);
		printf("\tYou won in %d guess", turn);
		switch(turn) {
			case 1:
				printf("!\n");
				printf("\t\tGOATED!\n");
				break;
			case 2:
			case 3:
				printf("es!\n");
				printf("\t\tAmazing!\n");
				break;
			case 4:
			case 5:
				printf("es!\n");
				printf("\t\tNice!\n");
				break;
			case 6:
				printf("es!\n");
				break;
			default:
				printf("This should never be printed to the screen.\n");
		
		} 
	} else {
		printf("You lost, better luck next time!\n");
	}
	return 0;
}

int get_word(const char file_name[], char word[]) {
	FILE *f_ptr;
	int i = 0;
	f_ptr = fopen(file_name, "r");
	
	if (f_ptr == NULL) {
		return 2;
	}
	
	while(fscanf(f_ptr, "%c", &word[i]) == 1) {
		i++;
	}
	
	fclose(f_ptr);
	return 0;
}

void get_guess(int guess_length, int num_guesses, int turn, char guess[]) {
	char guess_store[STR_CAP], chr;
	bool found_non_letter, invalid_guess;
	int length;
	if (turn == num_guesses) {
		printf("FINAL GUESS: ");
	} else {
		printf("GUESS %d! Enter your guess: ", turn);
	}
	
	do{
		scanf("%s", guess_store);
		
		chr = guess_store[0];
		invalid_guess = false;
		found_non_letter = false;
	
		for (length = 0; chr != '\0'; length++, chr = guess_store[length]) {
		
			if ( !((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) ) {
				found_non_letter = true;
			}
		}
	
		if (length != guess_length) {
			printf("Your guess must be %d letters long.", guess_length);
			invalid_guess = true;
		}
		if (found_non_letter) {
			printf("Your guess must only contain letters.");
			invalid_guess = true;
		}
		
		if (invalid_guess) {
			printf("\nPlease try again: ");
		}
	
	} while(invalid_guess);
	
	for (int i = 0; i < guess_length; i++) {
		guess[i] = guess_store[i];
	}
	
	printf("================================\n");
}

void lower_guess(int guess_length, char guess[]) {
	for (int i = 0; i < guess_length; i++) {
		if (guess[i] > 'A' && guess[i] < 'Z') {
			guess[i] += ('a' - 'A');
		}
	}
}

bool check_capital_win(int guess_length, char guess[], const char word[]) {
	bool same_so_far = true;
	
	for (int i = 0; i < guess_length; i++) {
		if (guess[i] != word[i]) {
			same_so_far = false;
		} else {
			guess[i] -= ('a' - 'A');
		}
	}
	
	return same_so_far;
}

void check_arrows(int guess_length, const char guess[], const char word[], char arrows_line[]) {
	bool letter_in_word, no_arrows_line_repeat;
	for (int guess_i = 0; guess_i < guess_length; guess_i++) {
		letter_in_word = false;
		no_arrows_line_repeat = true;
		for (int arrows_i = 0; arrows_i < guess_i; arrows_i++) {
			if (arrows_line[arrows_i] == '^' && guess[guess_i] == guess[arrows_i]) {
				no_arrows_line_repeat = false;
			}
		}
		
		for (int word_i = 0; word_i < guess_length; word_i++) {
			if (guess[guess_i] == word[word_i] && (guess[word_i] >= 'a' && guess[word_i] <= 'z') && no_arrows_line_repeat) {
				letter_in_word = true;
			}
		}
		
		if (letter_in_word) {
			arrows_line[guess_i] = '^';
		} else {
			arrows_line[guess_i] = ' ';
		}
	}
}

void display_line(int line_length, const char line[]) {
	for (int i = 0; i < line_length; i++) {
		printf("%c", line[i]);
	}
	printf("\n");
}

void display_guess_history(int turn, int guess_length, const char guesses[][guess_length], const char arrows_lines[][guess_length]) {
	for (int row = 0; row < turn; row++) {
		display_line(guess_length, guesses[row]);
		display_line(guess_length, arrows_lines[row]);
	}
}
