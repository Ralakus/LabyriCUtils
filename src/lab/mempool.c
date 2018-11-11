#include "mempool.h"

bool lab_mempool_init(lab_mempool_t* pool, size_t bytes, size_t sub_alloc_count) {
    return lab_vec_init(&pool->data, 1, bytes) && lab_vec_init(&pool->sub_allocs, sizeof(lab_mempool_suballoc_t), sub_alloc_count);
}

void lab_mempool_free(lab_mempool_t* pool) {
    lab_vec_free(&pool->data);
    lab_vec_free(&pool->sub_allocs);
}

lab_mempool_suballoc_t* lab_mempool_suballoc_alloc(lab_mempool_t* pool, size_t bytes) {
    lab_mempool_suballoc_t* alloc = (lab_mempool_suballoc_t*)lab_vec_push_back(&pool->sub_allocs, NULL);
    if(alloc == NULL) {
        return NULL;
    }
    alloc->data  = lab_vec_push_back_arr(&pool->data, NULL, bytes);
    alloc->index = lab_vec_size(&pool->sub_allocs) - 1;
    alloc->bytes = bytes;
    return alloc;
}

bool lab_mempool_suballoc_free(lab_mempool_t* pool, lab_mempool_suballoc_t* alloc) {
    return  lab_vec_remove_arr(&pool->data, (size_t)alloc->data - (size_t)lab_vec_at(&pool->data, 0), alloc->bytes) &&
            lab_vec_remove(&pool->sub_allocs, alloc->index);
}