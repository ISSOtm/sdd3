
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


void init_stack(Stack_t * stack) {
    stack->nb_elems = 0;
}

Stack_t * create_stack() {
    Stack_t * stack = malloc(sizeof(Stack_t));
    if(stack != NULL) {
        init_stack(stack);
    }
    return stack;
}

void destroy_stack(Stack_t * stack) {
    free(stack);
}


int push(Stack_t * stack, STACK_DATA_TYPE data) {
    int status = -1;
    if(!is_stack_full(stack)) {
        stack->data[stack->nb_elems++] = data;
        status = 0;
    }
    return status;
}

STACK_DATA_TYPE pop(Stack_t * stack, int * status) {
    /* FIXME: Generic typing doesn't provide a way to init this -- errors will return an uninitialized value, Valgrind will complain but there's nothing that can be done about it */
    STACK_DATA_TYPE retval;

    if(is_stack_empty(stack)) {
        if(status != NULL) {
            *status = -1;
        }
    } else {
        retval = stack->data[--stack->nb_elems];
        if(status != NULL) {
            *status = 0;
        }
    }
    return retval;
}

STACK_DATA_TYPE peek_stack(Stack_t const * stack, int * status) {
    STACK_DATA_TYPE retval;

    if(is_stack_empty(stack)) {
        *status = -1;
    } else {
        retval = stack->data[stack->nb_elems - 1];
        *status = 0;
    }
    return retval;
}


void fprintf_stack(FILE * stream, Stack_t const * stack) {
    unsigned read_index = 0;
    fprintf(stream, "Queue print, %u elems (from bottom)\n", stack->nb_elems);

    while(read_index < stack->nb_elems) {
        fprintf(stream, "%d " STACK_PRINTF_TYPE "\n", read_index, stack->data[read_index].node, stack->data[read_index].depth);
        read_index++;
    }
}


int is_stack_empty(Stack_t const * stack) {
    return stack->nb_elems == 0;
}

int is_stack_full(Stack_t const * stack) {
    return stack->nb_elems >= STACK_CAPACITY;
}

