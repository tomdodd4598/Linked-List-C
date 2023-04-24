#pragma once

#include "item.h"

#include <stdbool.h>

TYPEDEF_ITEM(char*, String, string);

void delete_string(char* str);

char* to_string_string(char* str);

bool insert_before_string(char** val, ItemString* item);

bool value_equals_string(ItemString* item, char** val);

DECLARE_LIST(char*, String, string);
