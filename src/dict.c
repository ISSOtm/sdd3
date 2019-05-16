
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dict.h"
#include "tree.h"
#include "growing_array.h"


TreeNode_t ** find_node(Tree_t ** tree, char const ** const path) {
    TreeNode_t ** search_ptr = tree;

    while(*search_ptr != NULL && **path != '\0' && tolower((*search_ptr)->value) <= tolower(**path)) {
        /* We have a pointer to a whole horizontal level */
        /* Seek the current letter in that level */
        search_ptr = seek_child(search_ptr, **path);
        /* `search_ptr` points to either a matching node, or a non-matching one */
        /* If the node is a match, */
        if(*search_ptr != NULL && tolower((*search_ptr)->value) == tolower(**path)) {
            /* Mark one character as matched */
            (*path)++;
            /* If we need to seek more nodes, */
            if(**path != '\0') {
                /* Start searching that node's children */
                search_ptr = &(*search_ptr)->child;
            }
        }
    }

    return search_ptr;
}

int insert_word(Tree_t ** tree, char const * word) {
    int status = 0;
    TreeNode_t ** search_ptr; /* Pointer to the pointer to the next node */
    TreeNode_t * new_nodes;
    unsigned i;
    char const * read_ptr = word;

    /*
     * The search is split in three parts:
     * 1. Look for nodes matching the string
     * 2. Add missing nodes (if any)
     * 3. Mark the last node as terminating
     */

    /* Look for matching nodes */
    search_ptr = find_node(tree, &read_ptr);
    /* `search_ptr` points to either the first non-matching node or the last matching one,
     * and `read_ptr` has been advanced to the first non-matching char
     */

    /* Add missing nodes, if any */
    if(*read_ptr != '\0') {
        new_nodes = calloc(strlen(read_ptr), sizeof(TreeNode_t));
        if(new_nodes != NULL) {
            /* Insert the new child in the middle of its siblings (if any) */
            new_nodes[0].sibling = *search_ptr;
            /* The `calloc` causes all pointers to be set to NULL by default */
            for(i = 0; *read_ptr != '\0'; read_ptr++, i++) {
                /* Advance to next intended level, except on first step where it's already done */
                if(i != 0) {
                    search_ptr = &(*search_ptr)->child;
                }
                /* Set current node's letter */
                new_nodes[i].value = tolower(*read_ptr);
                /* Set parent node's child pointer */
                *search_ptr = &new_nodes[i];
            }
        } else {
            status = -1;
        }
    }

    /* Finally, make last node terminal */
    (*search_ptr)->value = toupper((*search_ptr)->value);

    return status;
}

int insert_words(Tree_t ** tree, char const * const * const words, unsigned nb_words) {
    int status = 0;
    unsigned i;
    for(i = 0; i < nb_words && status == 0; i++) {
        status = insert_word(tree, words[i]);
    }

    return status;
}


void _list_words(NODE_TYPE value, unsigned depth) {
    static GrowingArray_t string = NEW_GROWING_ARRAY;

    set_growing_array_size(&string, (depth + 2) * sizeof(char));
    DATA_OF(string, char*)[depth  ] = tolower(value);

    if(isupper(value)) {
        DATA_OF(string, char*)[depth+1] = '\0';
        puts(DATA_OF(string, char*));
    }
}

void list_words(Tree_t const * tree) {
    depth_first_traversal(tree, _list_words);
}
