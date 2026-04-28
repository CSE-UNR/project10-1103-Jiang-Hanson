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
bool check_win(int guess_length, const char guess[], const char word[]); // 	written 	checked
void check_capital(int guess_length, char guess[], const char word[]); // 	written 	checked
void check_arrows(int guess_length, const char guess[], const char word[], char arrows_line[]); // 	written 	checked
void display_line(int line_length, const char line[]); // 	written
void display_guess_history(int turn, int guess_length, const char guesses[][guess_length], const char arrows_lines[][guess_length]); // 	written

int main () {
	char word[WORD_LEN], guess[WORD_LEN], arrows[WORD_LEN];
	bool won;
	
	if (get_word(FILE_NAME, word) == 2) {
		printf("Sorry, could not get today's word. Try again tommorrow.\n");
		return 2;
	}
	get_guess(WORD_LEN, NUM_GUESSES, 4, guess);
	
	lower_guess(WORD_LEN, guess);
	
	won = check_win(WORD_LEN, guess, word);
	
	check_capital(WORD_LEN, guess, word);
	check_arrows(WORD_LEN, guess, word, arrows);
	
	for (int i = 0; i < 5; i++) {
		printf("%c", guess[i]);
	}
	printf("\n");
	for (int i = 0; i < 5; i++) {
		printf("%c", arrows[i]);
	}
	printf("\n");
	
	printf("%d\n", won);
	

	/*
	if get mystery word gives 2:
		printf("Sorry, could not get today's word. Try again tommorrow.\n");
		return 2;
	loop: while the user didn't win and the turn is less than or equal to NUM_GUESSES:
		get guess
		make guess lowercase
		check if user won
		if not:
			check capital letters
			check arrows
			add guess to end of guess list
			add arrows line to end of arrows lines list
			display guess history
	
	if the user won:
		print you won message
	else:
		print you lost message
	*/
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
}

void lower_guess(int guess_length, char guess[]) {
	for (int i = 0; i < guess_length; i++) {
		if (guess[i] > 'A' && guess[i] < 'Z') {
			guess[i] += ('a' - 'A');
		}
	}
}

bool check_win(int guess_length, const char guess[], const char word[]) {
	bool same_so_far = true;
	
	for (int i = 0; i < guess_length && same_so_far; i++) {
		if (guess[i] != word[i]) {
			same_so_far = false;
		}
	}
	
	return same_so_far;
}

void check_capital(int guess_length, char guess[], const char word[]) {
	for (int i = 0; i < guess_length; i++) {
		if (guess[i] == word[i]) {
			guess[i] -= ('a' - 'A');
		}
	}
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
