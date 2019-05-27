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
 * WARNING: the "value" field is NOT initialized!!
 * @return The allocated node, or NULL on error
 */
TreeNode_t * create_node();

/**
 * Destroys a tree, freeing all its nodes
 * @param tree The tree to be destroyed
 */
void destroy_tree(Tree_t * tree);


/**
 * Traverses a tree depth-first, executing a function each time a node is encountered
 * Prefix traversal is applied, meaning the function is called as soon as each node is found
 * @param tree The tree to run through
 * @param func The function to call for each cell. Params are as follows:
 *             1: The current node. Modifying the node is allowed, though modifying its `child` or `sibling` parameter
 *                won't have any effect on the depth. This is required eg. for freeing nodes.
 *             2: The depth at which the node is, 0 being the tree's root.
 *             3: `arg` described below
 * @param arg This argument will be passed unmodified to all calls to `func` as described above. Use this for storage
 *            that should persist across calls to `func`.
 */
void depth_first_traversal(Tree_t * tree, void (*func)(TreeNode_t *, unsigned, void *), void * const arg);


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
