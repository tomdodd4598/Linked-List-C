#include "item_impl.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

String* new_string(char* raw_str) {
	String* str = malloc(sizeof *str);
	if (str != NULL) {
		str->raw_str = raw_str;
		str->len = strlen(raw_str);
	}
	return str;
}

void delete_string(String* str) {
	free(str->raw_str);
	free(str);
}

char* get_raw_string(String* str) {
	return str->raw_str;
}

schar compare_digits(String* str, String* oth) {
	const size_t str_len = str->len, oth_len = oth->len;
	if (str_len == 0 || oth_len == 0) {
		return -1;
	}

	char* raw_str = str->raw_str;
	char* raw_oth = oth->raw_str;

	char str_char = raw_str[0], oth_char = raw_oth[0];
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
		str_char = raw_str[i];
		oth_char = raw_oth[i];
		if (str_char > oth_char) {
			return str_minus ? -1 : 1;
		}
		else if (str_char < oth_char) {
			return str_minus ? 1 : -1;
		}
	}

	return -1;
}

bool insert_before_string(String* val, String* oth) {
	const schar digit_cmp = compare_digits(val, oth);
	return digit_cmp < 0 ? true : (digit_cmp > 0 ? false : strcmp(val->raw_str, oth->raw_str) < 1);
}

bool is_value_equal_string(String* val, String* oth) {
	return strcmp(val->raw_str, oth->raw_str) == 0;
}

const ItemFunctionsString item_functions_string = { get_raw_string, delete_string, insert_before_string, is_value_equal_string };

DEFINE_LIST(String, String, string);
