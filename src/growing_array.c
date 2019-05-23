
#include <stdlib.h>
#include "growing_array.h"


int set_growing_array_size(GrowingArray_t * array, unsigned size) {
    array->len = size;
    /* If the underlying array needs to grow, */
    if(array->len > array->size) {
        /* double its size, */
        array->size *= 2;
        /* unless it it not enough. */
        if(array->size < array->len) {
            array->size = array->len;
        }
        array->array = realloc(array->array, array->size);
    }

    return array->array == NULL;
}
