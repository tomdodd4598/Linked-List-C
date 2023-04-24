#include "item_impl.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void delete_string(char* str) {
	free(str);
}

char* to_string_string(char* str) {
	return str;
}

int compare_digits(char* str, char* oth) {
	const size_t str_len = strlen(str), oth_len = strlen(oth);
	if (str_len == 0 || oth_len == 0) {
		return -1;
	}

	char str_char = str[0], oth_char = oth[0];
	const bool str_minus = str_char == '-', other_minus = oth_char == '-';
	if (str_minus ^ other_minus) {
		return str_minus ? -1 : 1;
	}
	else if (!str_minus && (!isdigit(str_char) || !isdigit(oth_char))) {
		return 0;
	}
	else if (str_len > oth_len) {
		return str_minus ? -1 : 1;
	}
	else if (str_len < oth_len) {
		return str_minus ? 1 : -1;
	}

	for (size_t i = str_minus ? 1 : 0; i < str_len; ++i) {
		str_char = str[i];
		oth_char = oth[i];
		if (str_char > oth_char) {
			return str_minus ? -1 : 1;
		}
		else if (str_char < oth_char) {
			return str_minus ? 1 : -1;
		}
	}

	return -1;
}

bool insert_before_string(char** val, ItemString* item) {
	const int digit_cmp = compare_digits(*val, item->value);
	return digit_cmp < 0 ? true : (digit_cmp > 0 ? false : strcmp(*val, item->value) < 1);
}

bool value_equals_string(ItemString* item, char** val) {
	return strcmp(item->value, *val) == 0;
}

DEFINE_LIST(char*, String, string);
