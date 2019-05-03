
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dict.h"
#include "tree.h"
#include "growing_array.h"


TreeNode_t ** seek_node(TreeNode_t ** root_node, NODE_TYPE value) {
    TreeNode_t ** search_ptr = root_node;
    while(*search_ptr != NULL && tolower((*search_ptr)->value) < tolower(value)) {
        search_ptr = &(*search_ptr)->sibling;
    }

    return search_ptr;
}

int insert_word(Tree_t ** tree, char const * word) {
    int status = 0;
    TreeNode_t * tmp;
    TreeNode_t ** search_ptr = tree; /* Pointer to the pointer to the next node */
    const char * read_ptr = word;

    /* While we're not at the end of the string... */
    while(*read_ptr != '\0' && status == 0) {
        search_ptr = seek_node(search_ptr, *read_ptr);

        if(*search_ptr == NULL || tolower((*search_ptr)->value) != tolower(*read_ptr)) {
            /* We need to insert the node */
            tmp = create_node();
            if(tmp == NULL) {
                status = -1;
            } else {
                tmp->value = tolower(*read_ptr);
                tmp->sibling = *search_ptr;
                *search_ptr = tmp;
            }
        }

        /* If we're at the last node in the word, mark it as terminating */
        if(*++read_ptr == '\0') {
            (*search_ptr)->value = toupper((*search_ptr)->value);
        }

        search_ptr = &(*search_ptr)->child;
    }

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
    DATA_OF(string, char*)[depth+1] = '\0';

    if(isupper(value)) {
        puts(DATA_OF(string, char*));
    }
}

void list_words(Tree_t const * tree) {
    depth_first_traversal(tree, _list_words);
}
