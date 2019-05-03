#ifndef TREE_H
#define TREE_H

typedef char NODE_TYPE;

typedef struct TreeNode {
    NODE_TYPE value;
    struct TreeNode * child;
    struct TreeNode * sibling;
} TreeNode_t;

#endif /* TREE_H */
