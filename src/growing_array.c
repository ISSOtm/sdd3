
#include <stdlib.h>
#include "growing_array.h"


int set_growing_array_size(GrowingArray_t * array, unsigned size) {
    array->len = size;
    if(array->len > array->size) {
        array->size *= 2;
        if(array->size < array->len) {
            array->size = array->len;
        }
        array->array = realloc(array->array, array->size);
    }

    return array->array == NULL;
}
