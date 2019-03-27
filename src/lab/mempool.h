#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "vector.h"

typedef struct lab_mempool_suballoc_t {
    
    void* data;
    size_t index;
    size_t bytes;

} lab_mempool_suballoc_t;

typedef struct lab_mempool_t {
    
    lab_vec_t data;
    lab_vec_t sub_allocs;

} lab_mempool_t;

/*
    Mempool must be initilized before use and must be freed after use
*/
extern bool lab_mempool_init(lab_mempool_t* pool, size_t bytes, size_t sub_alloc_count);
extern void lab_mempool_free(lab_mempool_t* pool);

/*
    Each suballocation does not need to be freed but only to reduce memory consumption
*/
extern lab_mempool_suballoc_t* lab_mempool_suballoc_alloc(lab_mempool_t* pool, size_t bytes);
//extern lab_mempool_suballoc_t* lab_mempool_suballoc_realloc(lab_mempool_t* pool, lab_mempool_suballoc_t* alloc, size_t bytes);
extern bool                    lab_mempool_suballoc_free(lab_mempool_t* pool, lab_mempool_suballoc_t* alloc);

#ifdef __cplusplus
}
#endif