
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "tree.h"
#include "stack.h"


TreeNode_t * create_node() {
    TreeNode_t * node = malloc(sizeof(TreeNode_t));

    if(node != NULL) {
        node->child = NULL;
        node->sibling = NULL;
    }

    return node;
}


void depth_first_traversal(Tree_t const * tree, void (*func)(NODE_TYPE, unsigned, void *), void * const arg) {
    TreeNode_t const * read_ptr = tree;
    Stack_t * const stack = create_stack();
    unsigned depth = 0; /* Depth is a very useful parameter to call the function with */
    TreeTraversal_t traversal_struct = { .node = NULL, .depth = 0 };

    if(stack != NULL) {
        push(stack, traversal_struct); /* This will be popped at the end of reading the tree, meaning it's been read all over */

        while(read_ptr != NULL) {
            func(read_ptr->value, depth, arg);

            if(read_ptr->child != NULL) {
                /* If there are children, we'll need to iterate over them */
                if(read_ptr->sibling != NULL) {
                    /* If there also are siblings, we'll need to iterate over them as well */
                    traversal_struct.node = read_ptr->sibling;
                    traversal_struct.depth = depth;
                    push(stack, traversal_struct);
                }
                read_ptr = read_ptr->child;
                depth++;

            } else if(read_ptr->sibling != NULL) {
                /* If there is only a sibling, then go to them */
                read_ptr = read_ptr->sibling;

            } else {
                /* If this was a leaf, go back to previous intersection */
                traversal_struct = pop(stack, NULL);
                read_ptr = traversal_struct.node;
                depth = traversal_struct.depth;
            }
        }
        destroy_stack(stack);
    }
}


TreeNode_t ** seek_child(TreeNode_t ** root_node, NODE_TYPE value) {
    TreeNode_t ** search_ptr = root_node;
    while(*search_ptr != NULL && tolower((*search_ptr)->value) < tolower(value)) {
        search_ptr = &(*search_ptr)->sibling;
    }

    return search_ptr;
}


/* "Private" function, basically a lambda */
void _print_tree(NODE_TYPE value, unsigned depth) {
    unsigned i;
    for(i = 0; i < depth; i++) putchar(' ');
    printf(NODE_PRINT_SPEC "\n", value);
}

/* Used both as an example of depth-first traversal, and as a quick&dirty way to check a tree's contents */
void print_tree(Tree_t const * tree) {
    depth_first_traversal(tree, _print_tree, NULL);
}
