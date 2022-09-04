#pragma once

#include "item.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef signed char schar;

typedef struct String {
	char* raw_str;
	size_t len;
} String;

String* new_string(char* raw_str);

void delete_string(String* str);

typedef struct ItemFunctionsString {
	char* (*value_to_string)(String*);
	void (*delete_value)(String*);
	bool (*insert_before)(String*, String*);
	bool (*is_value_equal)(String*, String*);
} ItemFunctionsString;

char* get_raw_string(String* str);

bool insert_before_string(String* val, String* oth);

bool is_value_equal_string(String* val, String* oth);

DECLARE_LIST(String, String, string);
