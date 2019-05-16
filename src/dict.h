#ifndef DICT_H
#define DICT_H


#include "tree.h"


/**
 * Given a string of letters, tries to find the last node corresponding to that string of letters
 * @return A pointer to the last node matching the given path
 */
TreeNode_t ** find_node(Tree_t ** tree, char const ** const path);

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


void list_words(Tree_t const * tree);

void list_words_prefixed(Tree_t ** root_node, NODE_TYPE const * const pattern);


#endif /* DICT_H */
