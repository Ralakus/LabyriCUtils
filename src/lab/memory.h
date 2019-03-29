#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>


/*
    Reallocates memory; 
    Returns pointer to reallocated memory;
    If ptr is NULL, it mallocs
*/
extern void* lab_mem_realloc(void* ptr, size_t size);

/*
    Appends a chunk of memory to the end of another
*/
extern void* lab_mem_append (void* dest, size_t dest_size, const void* src, size_t size);

/*
    Inserts a chunk of memory inside another at specified index
*/
extern void* lab_mem_insert (void* dest, size_t dest_size, const void* src, size_t size, size_t index);

/*
    Removes a chunk of memory from inside a chunk of memory at specifed indexes
*/
extern void* lab_mem_remove (void* ptr, size_t ptr_size, size_t begin_idx, size_t end_idx);

/*
    Shifts memory to the right by 'distance' bytes ( Positive shift );
    Does not reallocate memory, may corrupt heap if not used correctly
*/
extern void* lab_mem_shift_right(void* ptr, size_t size, size_t distance);

/*
    Shifts memory to the left by 'distance' bytes ( Negative shift );
    Does not reallocate memory, may corrupt heap if not used correctly
*/
extern void* lab_mem_shift_left (void* ptr, size_t size, size_t distance);

/*
    Copies a chunk of memory into pointer
*/
extern void* lab_mem_copy(void* dest, const void* src, size_t size);

/*
    Compares memory
*/
extern int lab_mem_cmp(const void* src0, const void* src1, size_t size);

/*
    Frees memory
*/
extern void lab_mem_free(void* ptr);

#ifdef __cplusplus
}
#endif