#include "bin_tree_func_ak.h"
#include <stdio.h>
#include <stdlib.h>
#include "bin_dump_ak.h"

int main()
{
    struct tree_inf tree_info = {};
    ctor_tree(&tree_info);

    struct buffer_inf buffer_info = {};
    char** strings = NULL;

    onegin_func(&strings, &buffer_info, &tree_info); //TODO rename

    int index = 0;
    fill_tree(&index, strings, buffer_info.num_string, &tree_info.root, true);

    work_with_akinator(&tree_info, &strings, &buffer_info);

    return 0;
}
