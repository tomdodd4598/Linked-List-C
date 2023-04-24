#include "item_impl.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 16

char* read_line() {
	char* input = NULL;
	char temp[BLOCK_SIZE];
	size_t input_len = 0, temp_len = 0;

	do {
		fgets(temp, BLOCK_SIZE, stdin);
		temp[strcspn(temp, "\r\n")] = 0;
		temp_len = strlen(temp);
		char* realloc_ptr = realloc(input, input_len + temp_len + 1);
		if (realloc_ptr == NULL) {
			return NULL;
		}
		else {
			input = realloc_ptr;
			strcpy_s(input + input_len, temp_len + 1, temp);
		}
		input_len += temp_len;
	}
	while (temp_len == BLOCK_SIZE - 1 && temp[BLOCK_SIZE - 2] != '\n');

	return input;
}

bool is_valid_string(char* str, const size_t len) {
	const char first = str[0];

	if (len == 1 && first == '0') {
		return true;
	}

	size_t i = 1;

	if (isalpha(first)) {
		for (; i < len; ++i) {
			const char c = str[i];
			if (!isalpha(c) && !isdigit(c) && c != '_') {
				return false;
			}
		}
		return true;
	}

	if (first == '-') {
		if (len == 1) {
			return false;
		}

		const char second = str[1];
		if (second < '1' || second > '9') {
			return false;
		}

		++i;
	}
	else if (first < '1' || first > '9') {
		return false;
	}

	for (; i < len; ++i) {
		if (!isdigit(str[i])) {
			return false;
		}
	}

	return true;
}

int main() {
	ItemString* start = NULL;

	bool begin = true;

	while (true) {
		if (!begin) {
			putchar('\n');
		}
		else {
			begin = false;
		}

		puts("Awaiting input...");
		char* const input = read_line();

		if (input != NULL) {
			const size_t len = strlen(input);
			if (len == 0) {
				puts("\nProgram terminated!");
				remove_all_string(&start);
				return 0;
			}
			else if (input[0] == '~') {
				if (len == 1) {
					puts("\nDeleting list...");
					remove_all_string(&start);
				}
				else {
					char* const substr = malloc(len);
					if (substr != NULL) {
						strcpy_s(substr, len, input + 1);
						if (is_valid_string(substr, len - 1)) {
							puts("\nRemoving item...");
							remove_item_string(&start, substr);
						}
						else {
							puts("\nCould not parse input!");
							free(substr);
						}
					}
				}
			}
			else if (strcmp(input, "l") == 0) {
				puts("\nLoop print...");
				print_loop_string(start);
			}
			else if (strcmp(input, "i") == 0) {
				puts("\nIterator print...");
				print_iterator_string(start);
			}
			else if (strcmp(input, "a") == 0) {
				puts("\nArray print not implemented!");
			}
			else if (strcmp(input, "r") == 0) {
				puts("\nRecursive print...");
				print_recursive_string(start);
			}
			else if (strcmp(input, "f") == 0) {
				puts("\nFold print...");
				print_fold_string(start);
			}
			else if (strcmp(input, "b") == 0) {
				puts("\nFoldback print...");
				print_foldback_string(start);
			}
			else if (is_valid_string(input, len)) {
				puts("\nInserting item...");
				insert_item_string(&start, input);
				continue;
			}
			else {
				puts("\nCould not parse input!");
			}
			free(input);
		}
	}
}
