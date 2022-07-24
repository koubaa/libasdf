#pragma once

#include <cstdint>

void asdf_clear_error();
void asdf_get_error_details(int32_t val, const char** error);
int32_t asdf_get_error();

typedef struct asdf_file *asdf_file_handle;
asdf_file_handle asdf_read(const char* name);
