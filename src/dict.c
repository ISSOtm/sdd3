
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include "dict.h"
#include "tree.h"
#include "growing_array.h"


TreeNode_t ** find_node(Tree_t const * const * tree, char const ** path) {
    TreeNode_t const * const * search_ptr = tree;

    while(*search_ptr != NULL && **path != '\0' && tolower((*search_ptr)->value) <= tolower(**path)) {
        /* We have a pointer to a whole horizontal level */
        /* Seek the current letter in that level */
        search_ptr = (TreeNode_t const * const *)seek_child(search_ptr, **path);
        /* `search_ptr` points to either a matching node, or a non-matching one */
        /* If the node is a match, */
        if(*search_ptr != NULL && tolower((*search_ptr)->value) == tolower(**path)) {
            /* Mark one character as matched */
            (*path)++;
            /* If we need to seek more nodes, */
            if(**path != '\0') {
                /* Start searching that node's children */
                search_ptr = (TreeNode_t const * const *)&(*search_ptr)->child;
            }
        }
    }

    return (TreeNode_t**)search_ptr;
}

int insert_word(Tree_t ** tree, char const * word) {
    int status = 0; /* Whether the function succeeds or not */
    TreeNode_t ** search_ptr; /* Pointer to the pointer to the next node */
    TreeNode_t * new_node; /* Pointer to the node we're about to create. (TODO: move this in the loop?) */
    unsigned i; /* Used only to know if we're creating the first node */
    char const * read_ptr = word;

    /*
     * The search is split in three parts:
     * 1. Look for nodes matching the string
     * 2. Add missing nodes (if any)
     * 3. Mark the last node as terminating
     */

    /* Look for matching nodes */
    search_ptr = find_node((TreeNode_t const * const *)tree, &read_ptr);
    /* `search_ptr` points to either the first non-matching node or the last matching one,
     * and `read_ptr` has been advanced to the first non-matching char
     */

    /* Add missing nodes, if any */
    if(*read_ptr != '\0') {
        for(i = 0; *read_ptr != '\0'; read_ptr++, i++) {
            new_node = create_node();
            if(i != 0) {
                /* Advance to next intended level, except on first step where it's already done */
                search_ptr = &(*search_ptr)->child;
            } else {
                /* Insert the new child in the middle of its siblings (if any) */
                new_node->sibling = *search_ptr;
            }
            /* Set current node's letter */
            new_node->value = tolower(*read_ptr);
            /* Set parent node's child pointer */
            *search_ptr = new_node;
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


/* Private function to the `list_words` function */
static void _list_words(TreeNode_t * node, unsigned depth, void * arg) {
    ListWordsArg_t * args = (ListWordsArg_t*)arg; /* Shortcut to the args being passed, for brevity */
    GrowingArray_t * string = &args->array; /* Output "std::vector" buffer */
    char const * const prefix = args->prefix; /* The prefix to all the words we're about to print */
    unsigned prefix_length = 0; /* Added to the depth to get the index into the output buffer */

    /* If the prefix is not defined, consider it empty */
    if(prefix != NULL) {
        prefix_length = strlen(prefix);
        /* This should only be ran once, ideally, but we'll avoid increasing the size of the arg struct */
        if(depth == 0) {
            /* Prepend the prefix to the output buffer */
            set_growing_array_size(string, prefix_length + 1);
            memcpy(DATA_OF(*string, char*), prefix, prefix_length * sizeof(NODE_TYPE));
        }
    }

    /* Add current letter to the output */
    set_growing_array_size(string, (prefix_length + depth + 2) * sizeof(char));
    DATA_OF(*string, char*)[    prefix_length + depth  ] = tolower(node->value);
    /* No need to terminate if we're not going to print */

    /* If the letter is terminating, print the word that was constructed */
    if(isupper(node->value)) {
        DATA_OF(*string, char*)[prefix_length + depth+1] = '\0';
        puts(DATA_OF(*string, char*));
    }
}

void list_words(Tree_t const * tree) {
    ListWordsArg_t args = { NEW_GROWING_ARRAY, NULL };
    depth_first_traversal((Tree_t*)tree, _list_words, &args);
    DESTROY_GROWING_ARRAY(args.array);
}

void list_words_prefixed(Tree_t const * root_node, NODE_TYPE const * const pattern) {
    ListWordsArg_t args = { NEW_GROWING_ARRAY, NULL };
    NODE_TYPE const * pattern_ptr = pattern;
    Tree_t const * const * pattern_end = (Tree_t const * const *)find_node(&root_node, &pattern_ptr);
    TreeNode_t const * starting_node;

    args.prefix = (NODE_TYPE*)pattern;
    
    /*
     * An empty prefix causes `find_node` to return the first tree's root,
     * which is interpreted below as part of the prefix, ultimately leading to
     * buggy results. What listing words with an empty prefix does is ambiguous,
     * therefore we've decided to special-case it so it can be handled separately.
     * (Some opinions are that an empty prefix should return all words, others think
     * it should return none instead).
     * Which of the two behaviors should be taken here was decided using a very
     * scientific method essentially consisting of applying a rotation to a coin and
     * stopping it at a certain point in time. I think that's known as a "coin flip".
     * 
     * Consider this a hack if you so desire.
     */
    if(*pattern_ptr == '\0') {
        if(*pattern == '\0') {
            /* Empty prefix means "print all words" */
            args.prefix = NULL;
            starting_node = root_node;
        } else {
            starting_node = (*pattern_end)->child;
            /* This cannot show the prefix if it itself is a word in the dictionary */
            /* To keep the code consistent, the prefix is special-cased here */
            if(isupper((*pattern_end)->value)) {
                puts(pattern);
            }
        }
		depth_first_traversal((Tree_t *)starting_node, _list_words, &args);
	}

    DESTROY_GROWING_ARRAY(args.array);
}
