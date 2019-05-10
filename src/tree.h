#ifndef TREE_H
#define TREE_H

typedef char NODE_TYPE;
#define NODE_PRINT_SPEC "%c"

typedef struct TreeNode {
    NODE_TYPE value;
    struct TreeNode * child;
    struct TreeNode * sibling;
} TreeNode_t;

typedef TreeNode_t Tree_t;

typedef struct {
    TreeNode_t * node;
    unsigned depth;
} TreeTraversal_t;


/**
 * Allocates a new tree cell, filling its `child` and `sibling` pointers with NULL
 * @return The allocated node, or NULL on error
 */
TreeNode_t * create_node();


void depth_first_traversal(Tree_t const * tree, void (*func)(NODE_TYPE, unsigned));


/**
 * Seeks a pointer to the first child node whose value is greater than (== not strictly inferior to) the given value
 * May return a pointer to NULL, but **never** NULL
 * @param root_node The node to seek the children of
 * @param value The value to be seeked
 * @return A pointer to the seeked node
 */
TreeNode_t ** seek_child(TreeNode_t ** root_node, NODE_TYPE value);


/**
 * Prints a tree's contents in a fairly crude manner
 * @param tree The tree to print the contents of
 */
void print_tree(Tree_t const * tree);


#endif /* TREE_H */
