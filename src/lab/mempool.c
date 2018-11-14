#include "mempool.h"

bool lab_mempool_init(lab_mempool_t* pool, size_t bytes, size_t sub_alloc_count) {
    if(pool==NULL) {
        lab_errorln("Passed in NULL value for pool for function \"lab_mempool_free\"");
        return false;
    }
    return lab_vec_init(&pool->data, 1, bytes) && lab_vec_init(&pool->sub_allocs, sizeof(lab_mempool_suballoc_t), sub_alloc_count);
}

void lab_mempool_free(lab_mempool_t* pool) {
    if(pool==NULL) {
        lab_errorln("Passed in NULL value for pool for function \"lab_mempool_free\"");
        return;
    }
    lab_vec_free(&pool->data);
    lab_vec_free(&pool->sub_allocs);
}

lab_mempool_suballoc_t* lab_mempool_suballoc_alloc(lab_mempool_t* pool, size_t bytes) {

    if(pool==NULL) {

        lab_errorln("Passed in NULL value for pool for function \"lab_mempool_suballoc_alloc\"");
        return NULL;

    } else if(bytes==0) {

        lab_warnln("Treid to allocate a memory pool sub allocation with 0 bytes!");
        return NULL;

    }

    lab_mempool_suballoc_t* alloc = (lab_mempool_suballoc_t*)lab_vec_push_back(&pool->sub_allocs, NULL);

    if(alloc == NULL) {
        return NULL;
    }

    alloc->data  = lab_vec_push_back_arr(&pool->data, NULL, bytes);
    alloc->index = lab_vec_size(&pool->sub_allocs) - 1;
    alloc->bytes = bytes;
    return alloc;
}

/*lab_mempool_suballoc_t* lab_mempool_suballoc_realloc(lab_mempool_t* pool, lab_mempool_suballoc_t* alloc, size_t bytes) {

    if(pool==NULL && alloc==NULL) {
        lab_errorln("Passed in NULL value for pool and alloc for function \"lab_mempool_suballoc_realloc\"");
        return NULL;
    } else if(pool==NULL) {
        lab_errorln("Passed in NULL value for pool for function \"lab_mempool_suballoc_realloc\"");
        return NULL;
    } else if(alloc==NULL) {
        lab_errorln("Passed in NULL value for alloc for function \"lab_mempool_suballoc_realloc\"");
        return NULL;
    }

    if(bytes == alloc->bytes) {
        return alloc;
    }

    lab_mempool_suballoc_t* internal_alloc = (lab_mempool_suballoc_t*)lab_vec_at(&pool->sub_allocs, alloc->index);

    lab_noticeln("Alloc data ptr: %d, vec data ptr: %d", ((size_t)internal_alloc->data), ((size_t)lab_vec_at(&pool->data, 0)));
    size_t begin_index = ((size_t)internal_alloc->data) - ((size_t)pool->data.raw_data);
    lab_noticeln("Begin index: %zu", begin_index);
    size_t end_index   = begin_index + internal_alloc->bytes;
    lab_noticeln("End index: %zu", end_index);

    if(bytes < internal_alloc->bytes) {

        lab_vec_remove_arr(&pool->data, end_index - bytes - 1, internal_alloc->bytes - bytes);

    } else {

        lab_vec_insert(&pool->data, end_index - 1, NULL, bytes - internal_alloc->bytes);

    }

    internal_alloc->bytes = bytes;
    
    return internal_alloc;
}*/

bool lab_mempool_suballoc_free(lab_mempool_t* pool, lab_mempool_suballoc_t* alloc) {
    if(pool==NULL && alloc==NULL) {
        lab_errorln("Passed in NULL value for pool and alloc for function \"lab_mempool_suballoc_free\"");
        return false;
    } else if(pool==NULL) {
        lab_errorln("Passed in NULL value for pool for function \"lab_mempool_suballoc_free\"");
        return false;
    } else if(alloc==NULL) {
        lab_errorln("Passed in NULL value for alloc for function \"lab_mempool_suballoc_free\"");
        return false;
    }
    return  lab_vec_remove_arr(&pool->data, (size_t)alloc->data - (size_t)lab_vec_at(&pool->data, 0), alloc->bytes) &&
            lab_vec_remove(&pool->sub_allocs, alloc->index);
}