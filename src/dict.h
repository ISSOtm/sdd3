#ifndef DICT_H
#define DICT_H


#include "tree.h"


/**
 * Seeks a pointer to the first node whose value is greater than (== not strictly inferior to) the given value
 * May return a pointer to NULL, but **never** NULL
 * @param root_node The node to seek the children of
 * @param value The value to be seeked
 * @return A pointer to the seeked node
 */
TreeNode_t ** seek_node(TreeNode_t ** root_node, NODE_TYPE value);

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


#endif /* DICT_H */
