#ifndef __DUMP_BIN__
#define __DUMP_BIN__

#include <stdio.h>
#include <stdlib.h>
//#include "bin_tree_func_ak.h"
void dump_graph_rec(struct node* root, FILE* dump_file);
void dump_graph(struct tree_inf* tree_info);

#endif
