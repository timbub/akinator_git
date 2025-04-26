#include "bin_dump_ak.h"
#include "bin_tree_func_ak.h"


void dump_graph(struct tree_inf* tree_info)
{
    fprintf(tree_info->dump_file, "digraph G{\n\
    rankdir = TB;\n\
    node[color = \"#000000\", fontsize = 10];\n\
    edge[color = \"#000000\", fontsize = 5];\n");

    dump_graph_rec(tree_info->root, tree_info->dump_file);
    fprintf(tree_info->dump_file, "}\n");
}

void dump_graph_rec(struct node* root, FILE* dump_file)
{
    if (!root) return;
    if (root->left) dump_graph_rec(root->left, dump_file);
    if (root->left != NULL && root->right != NULL)
    {
        fprintf(dump_file, "\"%p\" [shape = Mrecord, style = filled, fillcolor = \"#FFFFFF\", color = \"#ff8333\", label = \"{DATA: %s | {<left> LEFT | <right> RIGHT}}\"];\n\
        \"%p\": <left> -> \"%p\" [color = \"#000000\", label = \"NO\"]\n\"%p\": <right> -> \"%p\" [color = \"#000000\", label = \"YES\"]\n", root, root->data, root, root->left, root, root->right);
    } else if (root->left != NULL)
    {
        fprintf(dump_file, "\"%p\" [shape = Mrecord, style = filled, fillcolor = \"#FFFFFF\", color = \"#ff8333\", label = \"{DATA: %s | {<left> LEFT | <right> RIGHT}}\"];\n\
        \"%p\": <left> -> \"%p\" [color = \"#000000\", label = \"NO\"]\n", root, root->data, root, root->left);
    } else if (root->right != NULL)
    {
        fprintf(dump_file, "\"%p\" [shape = Mrecord, style = filled, fillcolor = \"#FFFFFF\", color = \"#ff8333\", label = \"DATA: %s \"];\n\
        \"%p\": <right> -> \"%p\" [color = \"#000000\", label = \"YES\"]\n", root, root->data, root, root->right);
    } else
    {
        fprintf(dump_file, "\"%p\" [shape = Mrecord, style = filled, fillcolor = \"#FFFFFF\", color = \"#ff8333\", label = \"{DATA: %s | {<left> LEFT | <right> RIGHT}}\"];\n", root, root->data);
    }
    if (root->right) dump_graph_rec(root->right, dump_file);
}
