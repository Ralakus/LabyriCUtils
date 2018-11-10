#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "logger.h"

#include <stdbool.h>
#include <stddef.h>

/*
    
    Vector struct
    Do not modify raw data unless you know what you're doing

*/
typedef struct lab_vec_t {
    
    size_t type_size;
    size_t alloc_size;
    size_t used_size;
    void* raw_data;

} lab_vec_t;

/*
    Initializes vector with values specified
    Program will crash if vector is not initialized before use

    type_size is the size of the type you're planning to use like `sizeof(int)`
    init_size can be left at 0 since the vector will auto resize when not large enough
*/
extern bool lab_vec_init(lab_vec_t* vec, size_t type_size, size_t init_size); 

/*
    Vectors must be freed at the end of lifetime due the use of dynamic memory mangagement
*/
extern void lab_vec_free(lab_vec_t* vec);

/*
    Self explainitory
*/
extern size_t lab_vec_size      (lab_vec_t* vec);
extern size_t lab_vec_alloc_size(lab_vec_t* vec);
extern size_t lab_vec_type_size (lab_vec_t* vec);

/*
    Returns the pointer to index in vector
    Indices are determined by type_size
*/
extern void* lab_vec_at          (lab_vec_t* vec, size_t index);
/*
    Returns pointer to index in vector's allocated space
    Can be outside user's data
*/
extern void* lab_vec_at_raw_alloc(lab_vec_t* vec, size_t index);

/*
    Returns false if resize failed
*/
extern bool lab_vec_resize(lab_vec_t* vec, size_t new_size);

/*
    Appends data to end of vector
    Returns pointer to data appended
    If NULL is passed as raw_data, no data will be copied into vector
*/
extern void* lab_vec_push_back_arr(lab_vec_t* vec, void* raw_data, size_t count);
extern void* lab_vec_push_back    (lab_vec_t* vec, void* raw_data);

/*
    Removes data from end of vector
    Returns if removal was successful
*/
extern bool lab_vec_pop_back_arr(lab_vec_t* vec, size_t count);
extern bool lab_vec_pop_back    (lab_vec_t* vec);

/*
    Inserts data at specified index
    Returns pointer to new data
    If NULL is passed as raw_data, no data will be copied into vector
*/
extern void* lab_vec_insert(lab_vec_t* vec, size_t index, void* raw_data, size_t count);


/*
    Removes data from the vector
    Does not shrink vector
*/
extern bool lab_vec_remove_arr(lab_vec_t* vec, size_t start_index, size_t count);
extern bool lab_vec_remove    (lab_vec_t* vec, size_t index);



#ifdef __cplusplus
}
#endif