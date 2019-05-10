
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dict.h"
#include "tree.h"
#include "growing_array.h"


int insert_word(Tree_t ** tree, char const * word) {
    int status = 0;
    TreeNode_t * tmp;
    TreeNode_t ** search_ptr = tree; /* Pointer to the pointer to the next node */
    const char * read_ptr = word;

    /* The search is split in three parts:
     * 1. Look for nodes matching the string
     * 2. Add missing nodes (if any)
     * 3. Mark the last node as terminating
     */

    /* Look for matching nodes */
    while(*search_ptr != NULL && tolower((*search_ptr)->value) < tolower(*read_ptr) && *read_ptr != '\0' && status == 0) {
        search_ptr = seek_child(search_ptr, *read_ptr);
        (*search_ptr)->value = &(*search_ptr)->child;
        read_ptr++;
    }

    if(search_ptr == NULL || *search_ptr)

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
