#ifndef __BIN_FUNC__
#define __BIN_FUNC__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bin_dump_ak.h"
#include "onegin_func.h"

typedef char* type_elem;

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

const int MAX_HEIGHT_TREE = 20;

struct node* get_free_node(type_elem value, bool left_or_right);
void fill_tree(int* index, char** strings, size_t size_array_ind, struct node** root, bool left_or_right);
void dtor_node(struct node* node);
void print_tree(struct node* root);
void search_value(struct node* node, char* value, struct node** way, int* index);
void ctor_tree(struct tree_inf* tree_info);
void get_definition(struct tree_inf* tree_info);
void compare_word(struct tree_inf* tree_info);
void work_with_akinator(struct tree_inf* tree_info, char*** strings, struct buffer_inf* buffer_info);
void end_of_the_programm(struct tree_inf* tree_info, char*** strings, struct buffer_inf* buffer_info);

enum func_code
{
    END_PROG,
    GET_DEFINITION,
    COMPARE_WORD,
    DUMP_GRAPH,
    PRINT_TREE
};



struct tree_inf //TODO
{
    FILE*  input_file;
    FILE*  dump_file;
    struct node* root;
};

struct node
{
    type_elem    data;
    bool        left_or_right;
    struct node* left;
    struct node* right;
};

#endif
