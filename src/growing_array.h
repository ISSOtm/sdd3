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
 * Sets the size of a GrowingArray to any amount of bytes
 * If needed, `array->array` will be `realloc`'d, therefore:
 * **`array->array` is not guaranteed to be constant across this function!!**
 * @param array The array to set the size of
 * @param size The size to set the array's to, in bytes
 * @return 0 if all went well, non-zero otherwise
 */
int set_growing_array_size(GrowingArray_t * array, unsigned size);

/**
 * Shortcut to set a GrowingArray's size, refer to `set_growing_array_size`'s documentation for details
 * @param array The array to set the size of
 * @param nmemb The number of elements the array should now contain
 * @param type The type of the elements the array contains
 * @return See `set_growing_array_size`
 */
#define SET_GROWING_ARRAY_SIZE(array, nmemb, type)   set_growing_array_size(array, (array)->len + (nmemb) * sizeof(type))

/**
 * Shortcut to get a GrowingArray's actual array, casted to the proper type
 * @param growing_array The array to get the data of
 * @param type The type to cast the array's data to (must be a pointer or array)
 * @return As defined above.
 */
#define DATA_OF(growing_array, type)    ((type)((growing_array).array))


#endif /* GROWING_ARRAY_H */
