#ifndef STACK_H
#define STACK_H


/* For the FILE type */
#include <stdio.h>
/* For the Treenode_t * type */
#include "tree.h"


/* Tuned for the `thing` function */
#define STACK_CAPACITY 3

/*
 * These are used to simulate genericity (C++ templates FTW!)
 * WARNING: Make sure to keep in sync!
 */
/*
 * Intentionally does not adhere to the style guide, as this is not a complex type, just an alias.
 * TODO: have style guide clarify this?
*/
typedef TreeTraversal_t STACK_DATA_TYPE;
#define STACK_PRINTF_TYPE "%p"

typedef struct {
    unsigned nb_elems;
    STACK_DATA_TYPE data[STACK_CAPACITY];
} Stack_t;


/**
 * Inits a stack
 * @param stack The stack to init
 */
void init_stack(Stack_t * stack);

/**
 * Creates and inits a stack
 * Make sure to destroy it using `destroy_stack`
 * @return A pointer to the stack, or NULL if an error occurred
 */
Stack_t * create_stack();

/**
 * Destroys a stack created with `create_stack`
 * @param stack The stack to be destroyed
 */
void destroy_stack(Stack_t * stack);


/**
 * Push data onto a stack
 * @param stack The stack to save the data onto
 * @param data The data to be saved to the stack
 * @return 0 if everything went well, -1 otherwise (in which case the stack will be left untouched)
 */
int push(Stack_t * stack, STACK_DATA_TYPE data);

/**
 * Pop data from a stack
 * @param stack The stack to retrieve data from
 * @param status A pointer to a status int, set to 0 if all went well, or to -1 otherwise.
 * @return The data retrieved from the stack. If an error occurred, this is undefined
 */
STACK_DATA_TYPE pop(Stack_t * stack, int * status);

/**
 * Get the first element from a stack, but don't remove it
 * Parameters and returning are identical to `pop`
 */
STACK_DATA_TYPE peek_stack(Stack_t const * stack, int * status);


/**
 * Print a stack to a stream
 * @param stream The stream to print the stack to
 * @param stack The stack to be printed
 */
void fprintf_stack(FILE * stream, Stack_t const * stack);


/**
 * Check if a stack is empty
 * @param stack The stack to check
 * @return Non-zero if the stack is empty, 0 otherwise
 */
int is_stack_empty(Stack_t const * stack);

/**
 * Check if a stack is full
 * @param stack The stack to check
 * @return Non-zero if the stack is full, 0 otherwise
 */
int is_stack_full(Stack_t const * stack);


#endif /* STACK_H */
