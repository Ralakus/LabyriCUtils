#ifdef __cplusplus
extern "C" {
#endif

#include "vector.h"

#include <stdlib.h>
#include <string.h>

bool lab_vec_init(lab_vec_t* vec, size_t type_size, size_t init_size) {
    vec->type_size  = type_size;
    vec->used_size  = 0;
    vec->alloc_size = init_size;
    if(init_size == 0) {

        vec->raw_data = NULL;

        return true;

    } else {

        vec->raw_data   = malloc(type_size * vec->alloc_size);
        if(vec->raw_data == NULL) {
            lab_errorln("Failed to allocate vector array with size of %d and type size of %d", vec->alloc_size, vec->type_size);
            return false;
        } else {
            return true;
        }

    }
}

void lab_vec_free(lab_vec_t* vec) {
    vec->type_size  = 0;
    vec->used_size  = 0;
    vec->alloc_size = 0;
    free(vec->raw_data);
}

size_t lab_vec_size(lab_vec_t* vec) {
    return vec->used_size;
}

size_t lab_vec_alloc_size(lab_vec_t* vec) {
    return vec->alloc_size;
}

size_t lab_vec_type_size(lab_vec_t* vec) {
    return vec->type_size;
}

void* lab_vec_at(lab_vec_t* vec, size_t index) {
    if(index >= vec->used_size) {
        lab_errorln("Tried to access data outside of vector of size %d but access index of %d", vec->used_size, index);
        return NULL;
    } else {
        return vec->raw_data + (vec->type_size * index);
    }
}

void* lab_vec_at_raw_alloc(lab_vec_t* vec, size_t index) {
    if(index >= vec->alloc_size) {
        lab_errorln("Tried to access data outside of vector of alloc size %d but access index of %d", vec->alloc_size, index);
        return NULL;
    } else {
        return vec->raw_data + (vec->type_size * index);
    }
}

bool lab_vec_resize(lab_vec_t* vec, size_t new_size) {
    vec->alloc_size = new_size;
    vec->raw_data = realloc(vec->raw_data, vec->alloc_size * vec->type_size);
    if(vec->raw_data == NULL) {
        lab_errorln("Failed to reallocate vector from size %d to %d with type size of %d", vec->alloc_size, vec->type_size * new_size, vec->type_size);
        return false;
    } else {
        if(vec->used_size > vec->alloc_size) {
            vec->used_size = vec->alloc_size;
        }
        return true;
    }
}

void* lab_vec_push_back_arr(lab_vec_t* vec, void* raw_data, size_t count) {
    vec->used_size += count;
    if(vec->used_size > vec->alloc_size) {
        if(!lab_vec_resize(vec, vec->alloc_size + (vec->used_size - vec->alloc_size))) {
            lab_errorln("Failed to push back vector!");
            return NULL;
        }
    }
    if(memcpy(lab_vec_at_raw_alloc(vec, vec->used_size - count), raw_data, vec->type_size * count)==NULL) {
        lab_errorln("Failed to copy data into vector!");
        return NULL;
    } else {
        return lab_vec_at(vec, vec->used_size - count);
    }
}

void* lab_vec_push_back(lab_vec_t* vec, void* raw_data) {
    return lab_vec_push_back_arr(vec, raw_data, 1);
}

bool lab_vec_pop_back_arr(lab_vec_t* vec, size_t count) {
    return lab_vec_resize(vec, vec->used_size - count);
}
bool lab_vec_pop_back    (lab_vec_t* vec) {
    return lab_vec_pop_back_arr(vec, 1);
}

bool lab_vec_insert(lab_vec_t* vec, size_t index, void* raw_data, size_t count) {
    vec->used_size += count;
    if(vec->used_size > vec->alloc_size) {
        if(!lab_vec_resize(vec, vec->used_size + count)) {
            return false;
        }
    }
    memmove(lab_vec_at(vec, index + count), lab_vec_at(vec, index), vec->used_size - index);
    memcpy(vec->raw_data + index, raw_data, vec->type_size * count);
    return true;
}

#ifdef __cplusplus
}
#endif