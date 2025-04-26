#include "bin_tree_func_ak.h"
const char* CALL_DUMP = "dot dump_bin.txt -T png bin.png";

struct node* get_free_node(type_elem value, bool left_or_right)
{
    struct node* new_node = (struct node*) calloc(1, sizeof(struct node));
    new_node->data = value;
    new_node->left_or_right = left_or_right;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void ctor_tree(struct tree_inf* tree_info)
{
    tree_info->input_file  = fopen("akinator_t.txt", "r");
    tree_info->dump_file = fopen("dump_bin.txt", "w");

    if (tree_info->input_file  == NULL)
    {
        fprintf(stderr, "input file is not open");
    }

    if (tree_info->dump_file  == NULL)
    {
        fprintf(stderr, "file for dump is not open");
    }
    tree_info->root = NULL;
}

void print_tree(struct node* node)
{
    if (!node) return;
    printf("(");
    printf("%s %d", node->data, node->left_or_right);
    if (node->left) print_tree(node->left);
    if (node->right) print_tree(node->right);
    printf(")");
}

void dtor_node(struct node* node)
{
    if (!node) return;
    if (node->left) dtor_node(node->left);
    if (node->right) dtor_node(node->right);
    free(node);
}

void fill_tree(int* index, char** strings, size_t size_array_ind, struct node** root, bool left_or_right)
{
    if (*index >= size_array_ind) return; //TODO sruct use onegin

    if (strcmp(strings[*index], "{") == 0)
    {
        ++(*index);
        fill_tree(index, strings, size_array_ind, root, left_or_right);
    }
    else if (strcmp(strings[*index], "}") == 0)
    {
        ++(*index);
        return;
    }
    else
    {
        if (*index >= size_array_ind) return;
        *root = get_free_node(strings[*index], left_or_right);
        ++(*index);

        if (strcmp(strings[*index], "}") == 0) //TODO func
        {
            ++(*index);
            return;
        }

        fill_tree(index, strings, size_array_ind, &(*root)->left, false);
        ++(*index);

        if (strcmp(strings[*index], "}") == 0)
        {
            ++(*index);
            return;
        }
        fill_tree(index, strings, size_array_ind, &(*root)->right, true);
    }
}

void search_value(struct node* node, char* value, struct node** way, int* index, int* flag)
{
    if (!node || *flag == 1) return;
    if (strcmp(value, node->data) == 0)
    {
        if (*index == 0)
        {
            (*index)++;
            way[(*index)] = node;
        }
        *flag = 1;
        return;
    }
    (*index)++;
    way[(*index)] = node->left;
    search_value(node->left, value, way, index, flag);
    if (*flag == 1) return; //TODO spaces
    way[(*index)] = node->right;
    search_value(node->right, value, way, index, flag);\
    if (*flag == 1) return;
    (*index)--;
}


void compare_word(struct tree_inf* tree_info)
{
    printf("write 2 word and i try compare them\n");
    char value1[64] = "";
    char value2[64] = "";
    scanf("%s %s", value1, value2);
    struct node* array_way1[MAX_HEIGHT_TREE] = {};
    struct node* array_way2[MAX_HEIGHT_TREE] = {};
    array_way1[0] = tree_info->root;
    array_way2[0] = tree_info->root;
    int index1 = 0;
    int flag1  = 0;
    search_value(tree_info->root, value1, array_way1, &index1, &flag1);
    int index2 = 0;
    int flag2  = 0;
    search_value(tree_info->root, value2, array_way2, &index2, &flag2);

    int coincidences = 0;
    printf("%s and %s are ", value1, value2);
    for (int i = 0; i < MIN(index1, index2); i++)
    {
        if (array_way1[i] == array_way2[i] && array_way1[i+1]->left_or_right == array_way2[i+1]->left_or_right)
        {
            coincidences++;
            if(array_way1[i+1]->left_or_right)
            {
                printf("%s ", array_way1[i]->data);
            } else
            {
                printf("no %s ", array_way1[i]->data);
            }
        }
    }

    if (coincidences == 0)
    {
        printf("not have coincidences\n");
    } else
    {
        if (coincidences != index1)
        {
            printf("but %s is ", value1);
            for (int i = coincidences; i < index1; i++)
            {
                if(array_way1[i+1]->left_or_right)
                {
                    printf("%s ", array_way1[i]->data);
                } else
                {
                    printf("no %s ", array_way1[i]->data);
                }
            }
            printf("\n");
        }

        if (coincidences != index2)
        {
            printf("but %s is ", value2);
            for (int i = coincidences; i < index2; i++)
            {
                if(array_way2[i+1]->left_or_right)
                {
                    printf("%s ", array_way2[i]->data);
                } else
                {
                    printf("no %s ", array_way2[i]->data);
                }
            }
            printf("\n");
        }
    }
}

void get_definition(struct tree_inf* tree_info)
{
    printf("write word and i try get definition\n");
    char value[64] = "";
    scanf("%s", value);
    struct node* array_way[MAX_HEIGHT_TREE] = {};
    array_way[0] = tree_info->root;
    int index = 0;
    int flag  = 0;
    search_value(tree_info->root, value, array_way, &index, &flag);

    if (flag == 0)
    {
        printf("%s is not find\n", value);
    } else
    {
        printf("%s is ", value);
        for (int i = 0; i < index; i++)
        {
            if(array_way[i+1]->left_or_right)
            {
                printf("%s ", array_way[i]->data);
            } else
            {
                printf("no %s ", array_way[i]->data);
            }
        }
        printf("\n");
    }

}

void work_with_akinator(struct tree_inf* tree_info, char*** strings, struct buffer_inf* buffer_info)
{
    int programm_options = -1;
    while (programm_options != END_PROG)
    {
        printf("0 - end programm\n1 - get definition\n2 - compare word\n3 - dump graph\n4 - print tree\nchoose programm options\n");
        scanf("%d", &programm_options);
        //TODO: skip buffer
        switch(programm_options)
        {
            case END_PROG:
            {
                end_of_the_programm(tree_info, strings, buffer_info);
                //system(CALL_DUMP);
                break;
            }
            case GET_DEFINITION:
            {
                get_definition(tree_info);
                break;
            }
            case COMPARE_WORD:
            {
                compare_word(tree_info);
                break;
            }
            case DUMP_GRAPH:
            {
                dump_graph(tree_info);
                break;
            }
            case PRINT_TREE:
            {
                print_tree(tree_info->root);
                printf("\n");
                break;
            }
            default:
            {
                printf("wrong options\n");
                break;
            }
        }
    }
}

void end_of_the_programm(struct tree_inf* tree_info, char*** strings, struct buffer_inf* buffer_info)
{
    if (fclose(tree_info->dump_file)) fprintf(stderr, "ERORR close dump file");
    if (fclose(tree_info->input_file)) fprintf(stderr, "ERORR close input file");
    free(*strings);
    free(buffer_info->buffer);
    dtor_node(tree_info->root);
}


