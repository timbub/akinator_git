#ifndef __ONEGIN__
#define __ONEGIN__
#include <stdio.h>
#include <stdlib.h>

struct buffer_inf
{
    char* buffer;
    size_t size_buffer;
    size_t num_string;
};

size_t get_size(FILE* input_file);
void input_buf(struct buffer_inf* buffer_info, FILE* input_file);
size_t proccess_buffer(struct buffer_inf* buffer_info);
size_t input_indicator(struct buffer_inf* buffer_info, char** indicator);
void onegin_func(char*** strings, struct buffer_inf* buffer_info, struct tree_inf* tree_info);

#endif
