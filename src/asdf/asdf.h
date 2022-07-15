#pragma once

#include <cstdint>

void asdf_clear_error();
void asdf_get_error_details(int32_t val, const char** error);
int32_t asdf_get_error();

typedef struct asdf_file *asdf_file_handle;
asdf_file_handle asdf_read(const char* name);
void lib_divide(int64_t numerator, int64_t denominator, int64_t* remainder, int64_t* result);
