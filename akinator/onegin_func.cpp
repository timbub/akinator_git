#include "onegin_func.h"
#include "bin_tree_func_ak.h"

size_t get_size(FILE* input_file)
{
    fseek(input_file, 0L, SEEK_END);
    size_t size_file = ftell(input_file);
    fseek(input_file, 0L, SEEK_SET);

    return size_file;
}

void input_buf(struct buffer_inf* buffer_info, FILE* input_file)
{
    size_t k = fread(buffer_info->buffer, sizeof(char), (buffer_info->size_buffer)/sizeof(char), input_file);
    if (k != buffer_info->size_buffer)
    {
        printf("Wrong input to buffer %ld\n", k);
    }

}

size_t proccess_buffer(struct buffer_inf* buffer_info)
{
    int num_string = 0;
    int check_ = 0;
    for (size_t i = 0; i < buffer_info->size_buffer; i++)
    {
        if (buffer_info->buffer[i] == '"')
        {
            buffer_info->buffer[i] = '\0';
            check_ = abs(check_ - 1);
        }
        if (buffer_info->buffer[i] == '\n')
        {
            num_string++;
            buffer_info->buffer[i] = '\0';
        } else if (buffer_info->buffer[i] == '\r')
        {
            buffer_info->buffer[i] = '\0';
        } else if (buffer_info->buffer[i] == ' ' && check_ == 0)
        {
            buffer_info->buffer[i] = '\0';
        }
    }
    return num_string;
}

size_t input_indicator(struct buffer_inf* buffer_info, char** indicator)
{
    indicator[0] = &buffer_info->buffer[0];
    //printf("strings - %d\n", buffer_info->num_string);
    size_t num_ind = 1;
    for (size_t i = 1; i < buffer_info->size_buffer - 1; i++)
    {
        //printf("i = %d\n", i);
        if (buffer_info->buffer[i] == '\0' && buffer_info->buffer[i + 1] != '\0')
        {
            indicator[num_ind] = &buffer_info->buffer[i + 1];
            //printf("%d %s\n", num_ind, indicator[num_ind]);
            num_ind++;
        }
        if (num_ind == buffer_info->num_string)
        {
            return num_ind;
            break;
        }
    }
    return num_ind;
}

void onegin_func(char*** strings, struct buffer_inf* buffer_info, struct tree_inf* tree_info)
{
    buffer_info->size_buffer = get_size(tree_info->input_file);
    //printf("size %d\n",  buffer_info->size_buffer);  //TODO func
    buffer_info->buffer = NULL;

    buffer_info->buffer = (char*) calloc(buffer_info->size_buffer, sizeof(char));

    input_buf(buffer_info, tree_info->input_file);
    buffer_info->num_string = proccess_buffer(buffer_info);

    *strings = (char**) calloc(buffer_info->num_string, sizeof(char*));

    buffer_info->num_string = input_indicator(buffer_info, *strings);
}
