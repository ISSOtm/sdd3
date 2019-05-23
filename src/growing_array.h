#ifndef GROWING_ARRAY_H
#define GROWING_ARRAY_H


/* Basically C++'s std::vector */
typedef struct {
    void * array;
    unsigned len;  /* Number of used items */
    unsigned size; /* Number of allocated items */
} GrowingArray_t;

/* Feed this your initialization of a GrowingArray_t */
#define NEW_GROWING_ARRAY   { NULL, 0, 0 }

/* Use this to ensure a GrowingArray gets destroyed correctly */
#define DESTROY_GROWING_ARRAY(grow_array) free((grow_array).array); (grow_array).size = 0;


/**
 * Increases the size of an array by any amount
 * If needed, `array->array` will be `realloc`'d, therefore:
 * **`array->array` is not guaranteed to be constant across this function!!**
 * @param array The array to grow the size of
 * @param size The size to grow the array by, in bytes
 * @return 0 if all went well, non-zero otherwise
 */
int set_growing_array_size(GrowingArray_t * array, unsigned size);

#define SET_GROWING_ARRAY_SIZE(array, nmemb, type)   set_growing_array_size(array, (array)->len + (nmemb) * sizeof(type))

#define DATA_OF(growing_array, type)    ((type)((growing_array).array))


#endif /* GROWING_ARRAY_H */
