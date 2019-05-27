
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

/* `free` wrapper for depth_first_traversal */
static void _destroy_node(TreeNode_t * node, unsigned depth, void * arg) {
    (void)depth;
    (void)arg;
    free(node);
}

void destroy_tree(Tree_t * tree) {
    depth_first_traversal(tree, _destroy_node, NULL);
}


void depth_first_traversal(Tree_t * tree, void (*func)(TreeNode_t *, unsigned, void *), void * const arg) {
    TreeNode_t * read_ptr = tree;
    TreeNode_t * child, * sibling; /* The current node's "family" is cached in order to avoid use-after-free when destroying the tree */
    Stack_t * const stack = create_stack(); /* We'll implement recursion ourselves because pushing might be unnecessary at times. (Compilers do perform tail call optimizations though) */
    unsigned depth = 0; /* Depth is a very useful parameter to call the function with */
    TreeTraversal_t traversal_struct = { NULL, 0 }; /* Struct used to store siblings & depth in a single stack */

    if(stack != NULL) {
        push(stack, traversal_struct); /* This will be popped at the end of reading the tree, meaning it's been read all over */

        /* We thoroughly check to prevent read_ptr from being set to NULL, except when popping the stack
         * Therefore, it's also impossible to push a NULL pointer; and thus, the only time read_ptr will be NULL is
         * when popping the NULL initially pushed to the stack */
        while(read_ptr != NULL) {
            /* The function might modify the node, but we mustn't be affected by it
             * This is especially important for freeing */
            child = read_ptr->child, sibling = read_ptr->sibling;
            func(read_ptr, depth, arg);

            if(child != NULL) {
                /* If there are children, we'll need to iterate over them */
                if(sibling != NULL) {
                    /* If there also are siblings, we'll need to iterate over them as well after we're done */
                    traversal_struct.node = sibling;
                    traversal_struct.depth = depth;
                    push(stack, traversal_struct);
                }
                read_ptr = child;
                depth++;

            } else if(sibling != NULL) {
                /* If there is only a sibling, then go to them */
                read_ptr = sibling;

            } else {
                /* If this was a leaf, go back to previous intersection */
                traversal_struct = pop(stack, NULL);
                read_ptr = traversal_struct.node;
                /* If we always pushed when going down a level, we could avoid pushing depth to the stack;
                 * but, due to the optimizations, it's impossible to infer how many levels a pop goes back up,
                 * unless we store that info within the "traversal struct" */
                depth = traversal_struct.depth;
            }
        }
        destroy_stack(stack);
    }
}


TreeNode_t ** seek_child(TreeNode_t const * const * root_node, NODE_TYPE value) {
    TreeNode_t const * const * search_ptr = root_node;
    while(*search_ptr != NULL && tolower((*search_ptr)->value) < tolower(value)) {
        search_ptr = (TreeNode_t const * const *)&(*search_ptr)->sibling;
    }

    return (TreeNode_t **)search_ptr;
}


/* "Private" function, basically a lambda */
static void _print_tree(TreeNode_t * node, unsigned depth, void * arg) {
    unsigned i;
    (void)arg;

    for(i = 0; i < depth; i++) putchar(' ');
    printf(NODE_PRINT_SPEC "\n", node->value);
}

/* Used both as an example of depth-first traversal, and as a quick&dirty way to check a tree's contents */
void print_tree(Tree_t const * tree) {
    depth_first_traversal((Tree_t*)tree, _print_tree, NULL);
}
