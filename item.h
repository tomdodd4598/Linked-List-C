#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define TYPEDEF_ITEM(TYPE, CAPITAL, LOWERCASE)\
\
typedef struct Item##CAPITAL Item##CAPITAL;\
struct Item##CAPITAL {\
	TYPE value;\
	Item##CAPITAL* next;\
};\

#define DECLARE_LIST(TYPE, CAPITAL, LOWERCASE)\
\
Item##CAPITAL* new_item_##LOWERCASE(TYPE val, Item##CAPITAL* next);\
\
void delete_item_##LOWERCASE(Item##CAPITAL* item);\
\
Item##CAPITAL* print_get_next_##LOWERCASE(Item##CAPITAL* item);\
\
typedef struct ItemIterator##CAPITAL ItemIterator##CAPITAL;\
struct ItemIterator##CAPITAL {\
	Item##CAPITAL* item;\
};\
\
bool has_next_##LOWERCASE(ItemIterator##CAPITAL* iter);\
\
void increment_##LOWERCASE(ItemIterator##CAPITAL* iter);\
\
void insert_item_##LOWERCASE(Item##CAPITAL** start, TYPE val);\
\
void remove_item_##LOWERCASE(Item##CAPITAL** start, TYPE val);\
\
void remove_all_##LOWERCASE(Item##CAPITAL** start);\
\
char* fold_##LOWERCASE(char* (*f_some)(Item##CAPITAL*, Item##CAPITAL*, char*), char* (*f_last)(Item##CAPITAL*, char*), char* (*f_empty)(char*), char* accumulator, Item##CAPITAL* item);\
\
typedef struct ItemFoldbackClosure##CAPITAL ItemFoldbackClosure##CAPITAL;\
struct ItemFoldbackClosure##CAPITAL {\
	ItemFoldbackClosure##CAPITAL* previous;\
	char* (*f_some)(Item##CAPITAL*, Item##CAPITAL*, char*);\
	Item##CAPITAL* item;\
	Item##CAPITAL* next;\
};\
\
ItemFoldbackClosure##CAPITAL* new_item_foldback_closure_##LOWERCASE(ItemFoldbackClosure##CAPITAL* previous, char* (*f_some)(Item##CAPITAL*, Item##CAPITAL*, char*), Item##CAPITAL* item, Item##CAPITAL* next);\
\
char* foldback_generator_##LOWERCASE(ItemFoldbackClosure##CAPITAL* closure, char* inner_val);\
\
char* foldback_##LOWERCASE(char* (*f_some)(Item##CAPITAL*, Item##CAPITAL*, char*), char* (*f_last)(Item##CAPITAL*), char* (*f_empty)(), ItemFoldbackClosure##CAPITAL* closure, Item##CAPITAL* item);\
\
void print_loop_##LOWERCASE(Item##CAPITAL* start);\
\
void print_iterator_##LOWERCASE(Item##CAPITAL* start);\
\
void print_recursive_##LOWERCASE(Item##CAPITAL* start);\
\
char* print_fold_f_some_##LOWERCASE(Item##CAPITAL* current, Item##CAPITAL* next, char* accumulator);\
\
char* print_fold_f_last_##LOWERCASE(Item##CAPITAL* current, char* accumulator);\
\
char* print_fold_f_empty_##LOWERCASE(char* accumulator);\
\
void print_fold_##LOWERCASE(Item##CAPITAL* start);\
\
char* print_foldback_f_some_##LOWERCASE(Item##CAPITAL* current, Item##CAPITAL* next, char* inner_val);\
\
char* print_foldback_f_last_##LOWERCASE(Item##CAPITAL* current);\
\
char* print_foldback_f_empty_##LOWERCASE();\
\
void print_foldback_##LOWERCASE(Item##CAPITAL* start);\

#define DEFINE_LIST(TYPE, CAPITAL, LOWERCASE)\
\
Item##CAPITAL* new_item_##LOWERCASE(TYPE val, Item##CAPITAL* next) {\
	printf("Creating item: %s\n", to_string_##LOWERCASE(val));\
	Item##CAPITAL* item = malloc(sizeof *item);\
	if (item != NULL) {\
		item->value = val;\
		item->next = next;\
	}\
	return item;\
}\
\
void delete_item_##LOWERCASE(Item##CAPITAL* item) {\
	printf("Deleting item: %s\n", to_string_##LOWERCASE(item->value));\
	delete_##LOWERCASE(item->value);\
	if (item->next != NULL) {\
		delete_item_##LOWERCASE(item->next);\
	}\
	free(item);\
}\
\
Item##CAPITAL* print_get_next_##LOWERCASE(Item##CAPITAL* item) {\
	Item##CAPITAL* next = item->next;\
	printf("%s%s", to_string_##LOWERCASE(item->value), next == NULL ? "\n" : ", ");\
	return next;\
}\
\
bool has_next_##LOWERCASE(ItemIterator##CAPITAL* iter) {\
	return iter->item != NULL;\
}\
\
void increment_##LOWERCASE(ItemIterator##CAPITAL* iter) {\
	iter->item = iter->item->next;\
}\
\
void insert_item_##LOWERCASE(Item##CAPITAL** start, TYPE val) {\
	while (*start != NULL && !insert_before_##LOWERCASE(&val, *start)) {\
		start = &(*start)->next;\
	}\
	*start = new_item_##LOWERCASE(val, *start);\
}\
\
void remove_item_##LOWERCASE(Item##CAPITAL** start, TYPE val) {\
	while (*start != NULL && !value_equals_##LOWERCASE(*start, &val)) {\
		start = &(*start)->next;\
	}\
	\
	if (*start == NULL) {\
		printf("Item %s does not exist!\n", to_string_##LOWERCASE(val));\
	}\
	else {\
		Item##CAPITAL* removed = *start;\
		*start = removed->next;\
		removed->next = NULL;\
		delete_item_##LOWERCASE(removed);\
	}\
	delete_##LOWERCASE(val);\
}\
\
void remove_all_##LOWERCASE(Item##CAPITAL** start) {\
	if (*start != NULL) {\
		delete_item_##LOWERCASE(*start);\
	}\
	*start = NULL;\
}\
\
char* fold_##LOWERCASE(char* (*f_some)(Item##CAPITAL*, Item##CAPITAL*, char*), char* (*f_last)(Item##CAPITAL*, char*), char* (*f_empty)(char*), char* accumulator, Item##CAPITAL* item) {\
	if (item != NULL) {\
		Item##CAPITAL* next = item->next;\
		if (next != NULL) {\
			return fold_##LOWERCASE(f_some, f_last, f_empty, f_some(item, next, accumulator), next);\
		}\
		else {\
			return f_last(item, accumulator);\
		}\
	}\
	else {\
		return f_empty(accumulator);\
	}\
}\
\
ItemFoldbackClosure##CAPITAL* new_item_foldback_closure_##LOWERCASE(ItemFoldbackClosure##CAPITAL* previous, char* (*f_some)(Item##CAPITAL*, Item##CAPITAL*, char*), Item##CAPITAL* item, Item##CAPITAL* next) {\
	ItemFoldbackClosure##CAPITAL* closure = malloc(sizeof *closure);\
	if (closure != NULL) {\
		closure->previous = previous;\
		closure->f_some = f_some;\
		closure->item = item;\
		closure->next = next;\
	}\
	return closure;\
}\
\
char* foldback_generator_##LOWERCASE(ItemFoldbackClosure##CAPITAL* closure, char* inner_val) {\
	ItemFoldbackClosure##CAPITAL* previous = closure->previous;\
	if (previous != NULL) {\
		char* (*f_some)(Item##CAPITAL*, Item##CAPITAL*, char*) = closure->f_some;\
		Item##CAPITAL* item = closure->item, *next = closure->next;\
		free(closure);\
		return foldback_generator_##LOWERCASE(previous, f_some(item, next, inner_val));\
	}\
	else {\
		free(closure);\
		return inner_val;\
	}\
}\
\
char* foldback_##LOWERCASE(char* (*f_some)(Item##CAPITAL*, Item##CAPITAL*, char*), char* (*f_last)(Item##CAPITAL*), char* (*f_empty)(), ItemFoldbackClosure##CAPITAL* closure, Item##CAPITAL* item) {\
	if (item != NULL) {\
		Item##CAPITAL* next = item->next;\
		if (next != NULL) {\
			return foldback_##LOWERCASE(f_some, f_last, f_empty, new_item_foldback_closure_##LOWERCASE(closure, f_some, item, next), next);\
		}\
		else {\
			return foldback_generator_##LOWERCASE(closure, f_last(item));\
		}\
	}\
	else {\
		return foldback_generator_##LOWERCASE(closure, f_empty());\
	}\
}\
\
void print_loop_##LOWERCASE(Item##CAPITAL* start) {\
	while (start != NULL) {\
		start = print_get_next_##LOWERCASE(start);\
	}\
}\
\
void print_iterator_##LOWERCASE(Item##CAPITAL* start) {\
	if (start != NULL) {\
		for (ItemIterator##CAPITAL iter = { start }; has_next_##LOWERCASE(&iter); increment_##LOWERCASE(&iter)) {\
			print_get_next_##LOWERCASE(iter.item);\
		}\
	}\
}\
\
void print_recursive_##LOWERCASE(Item##CAPITAL* start) {\
	if (start != NULL) {\
		print_recursive_##LOWERCASE(print_get_next_##LOWERCASE(start));\
	}\
}\
\
char* print_fold_f_some_##LOWERCASE(Item##CAPITAL* current, Item##CAPITAL* next, char* accumulator) {\
	char* current_str = to_string_##LOWERCASE(current->value);\
	const size_t accumulator_len = strlen(accumulator), current_str_len = strlen(current_str);\
	char* str = realloc(accumulator, accumulator_len + current_str_len + 3);\
	if (str != NULL) {\
		strcpy_s(&str[accumulator_len], current_str_len + 1, current_str);\
		strcpy_s(&str[accumulator_len + current_str_len], 3, ", ");\
		str[accumulator_len + current_str_len + 2] = '\0';\
	}\
	return str;\
}\
\
char* print_fold_f_last_##LOWERCASE(Item##CAPITAL* current, char* accumulator) {\
	char* current_str = to_string_##LOWERCASE(current->value);\
	const size_t accumulator_len = strlen(accumulator), current_str_len = strlen(current_str);\
	char* str = realloc(accumulator, accumulator_len + current_str_len + 2);\
	if (str != NULL) {\
		strcpy_s(&str[accumulator_len], current_str_len + 1, current_str);\
		str[accumulator_len + current_str_len] = '\n';\
		str[accumulator_len + current_str_len + 1] = '\0';\
	}\
	return str;\
}\
\
char* print_fold_f_empty_##LOWERCASE(char* accumulator) {\
	return accumulator;\
}\
\
void print_fold_##LOWERCASE(Item##CAPITAL* start) {\
	char* str = fold_##LOWERCASE(print_fold_f_some_##LOWERCASE, print_fold_f_last_##LOWERCASE, print_fold_f_empty_##LOWERCASE, calloc(1, sizeof(char)), start);\
	printf(str);\
	free(str);\
}\
\
char* print_foldback_f_some_##LOWERCASE(Item##CAPITAL* current, Item##CAPITAL* next, char* inner_val) {\
	char* current_str = to_string_##LOWERCASE(current->value);\
	const size_t current_str_len = strlen(current_str), inner_val_len = strlen(inner_val);\
	char* inner_copy = malloc(inner_val_len + 1), *str = NULL;\
	if (inner_copy != NULL) {\
		strcpy_s(inner_copy, inner_val_len + 1, inner_val);\
		str = realloc(inner_val, current_str_len + inner_val_len + 3);\
		if (str != NULL && inner_val != NULL) {\
			strcpy_s(str, current_str_len + 1, current_str);\
			strcpy_s(&str[current_str_len], 3, ", ");\
			strcpy_s(&str[current_str_len + 2], inner_val_len + 1, inner_copy);\
			str[current_str_len + inner_val_len + 2] = '\0';\
		}\
		free(inner_copy);\
	}\
	return str;\
}\
\
char* print_foldback_f_last_##LOWERCASE(Item##CAPITAL* current) {\
	char* current_str = to_string_##LOWERCASE(current->value);\
	const size_t current_str_len = strlen(current_str);\
	char* str = malloc(current_str_len + 2);\
	if (str != NULL) {\
		strcpy_s(str, current_str_len + 1, current_str);\
		str[current_str_len] = '\n';\
		str[current_str_len + 1] = '\0';\
	}\
	return str;\
}\
\
char* print_foldback_f_empty_##LOWERCASE() {\
	return calloc(1, sizeof(char));\
}\
\
void print_foldback_##LOWERCASE(Item##CAPITAL* start) {\
	char* str = foldback_##LOWERCASE(print_foldback_f_some_##LOWERCASE, print_foldback_f_last_##LOWERCASE, print_foldback_f_empty_##LOWERCASE, new_item_foldback_closure_##LOWERCASE(NULL, NULL, NULL, NULL), start);\
	printf(str);\
	free(str);\
}\
