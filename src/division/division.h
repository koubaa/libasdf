#pragma once

void lib_clear_error();
void lib_get_error_details(int val, const char** error);
int32_t lib_get_error();
void lib_divide(int64_t numerator, int64_t denominator, int64_t* remainder, int64_t* result);
