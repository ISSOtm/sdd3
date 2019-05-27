#ifndef DICT_H
#define DICT_H


#include "tree.h"
#include "growing_array.h"


typedef struct {
    GrowingArray_t array;
    NODE_TYPE * prefix;
} ListWordsArg_t;


/**
 * Given a string of letters, tries to find the last node corresponding to that string of letters
 * @param tree The tree to find the path in
 * @param path The string to seek a path for
 * @return A pointer to the last node matching the given path
 */
TreeNode_t ** find_node(Tree_t const * const * tree, char const * * path);

/**
 * Inserts a word in a dictionary tree. If the word is already present, this function does nothing.
 * @param tree A pointer to the dictionary to insert the word into
 * @param word The word to insert
 * @return Zero if all went well, an error code otherwise
 */
int insert_word(Tree_t ** tree, char const * word);

/**
 * Inserts an array of words in a dictionary tree. Stops on the first failing word, if any.
 * @param tree A pointer to the dictionary to insert the word into
 * @param words An array of words to insert
 * @return Zero if all went well, an error code otherwise
 */
int insert_words(Tree_t ** tree, char const * const * const words, unsigned nb_words);


/**
 * Lists all the words stored in a dictionary tree to stdout
 * @param tree The tree to list the words of
 */
void list_words(Tree_t const * tree);

/**
 * Lists all the words beginning with a certain prefix in a dictionary tree to stdout
 * @param root_node A pointer to the tree to list the words of
 * @param pattern The prefix that all words must begin with. An empty prefix causes the function to behave as `list_words`.
 */
void list_words_prefixed(Tree_t const * root_node, NODE_TYPE const * const pattern);


#endif /* DICT_H */
