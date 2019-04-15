#include "vector.h"

#include "memory.h"

#define USED_BYTES (vec->used_len * vec->type_size)
#define ALLOC_BYTES (vec->alloc_len * vec->type_size)
#define LEN_TO_BYTES(len) (len * vec->type_size) 

size_t lab_vec_grow_fn_double(size_t old_size) {
    return old_size == 0 ? 8 : old_size * 2;
}
size_t lab_vec_grow_fn_1p5   (size_t old_size) {
    return old_size == 0 ? 8 : old_size + (1 + ((old_size - 1) / 2));
}


bool lab_vec_init(lab_vec_t* vec, size_t type_size, size_t init_len) {

    vec->type_size = type_size;
    vec->used_len  = 0;
    vec->alloc_len = init_len;
    vec->grow_fn = lab_vec_grow_fn_1p5;
    vec->data  = lab_mem_realloc(NULL, ALLOC_BYTES);
    return init_len > 0 ? vec->data != NULL : true;

}

void lab_vec_free(lab_vec_t* vec) {
    vec->type_size = 0;
    vec->used_len  = 0;
    vec->alloc_len = 0;
    lab_mem_free(vec->data);
}

size_t lab_vec_len       (lab_vec_t* vec) {
    return vec->used_len;
}

size_t lab_vec_alloc_len (lab_vec_t* vec) {
    return vec->alloc_len;
}

size_t lab_vec_type_size (lab_vec_t* vec) {
    return vec->type_size;
}

void* lab_vec_at          (lab_vec_t* vec, size_t index) {
    if(index >= vec->used_len) return NULL;
    else return vec->data + LEN_TO_BYTES(index);
}

void* lab_vec_at_alloc(lab_vec_t* vec, size_t index) {
    if(index >= vec->alloc_len) return NULL;
    else return vec->data + LEN_TO_BYTES(index);
}

bool lab_vec_grow(lab_vec_t* vec) {
    return lab_vec_resize(vec, vec->grow_fn(vec->alloc_len));
}

void lab_vec_set_grow_fn(lab_vec_t* vec, lab_vec_grow_fn_t fn) {
    vec->grow_fn = fn;
}

bool lab_vec_resize(lab_vec_t* vec, size_t new_len) {
    vec->alloc_len = new_len;
    vec->data = lab_mem_realloc(vec->data, ALLOC_BYTES);
    if(vec->data == NULL && vec->alloc_len != 0) {
        return false;
    } else {
        if(vec->used_len > vec->alloc_len) {
            vec->used_len = vec->alloc_len;
        }
        return true;
    }
}

bool lab_vec_shrink_to_size(lab_vec_t* vec) {
    return lab_vec_resize(vec, vec->used_len);
}

void* lab_vec_push_back_arr(lab_vec_t* vec, const void* data, size_t count) {
    if(count > 0) {
        vec->used_len += count;
        if(vec->alloc_len < vec->used_len) {
            if(vec->used_len < vec->grow_fn(vec->alloc_len)) {
                if(!lab_vec_grow(vec)) return NULL;
            } else {
                if(!lab_vec_resize(vec, vec->used_len)) return NULL;
            }
        }

        if(lab_mem_copy(vec->data + USED_BYTES - LEN_TO_BYTES(count), data, LEN_TO_BYTES(count)) == NULL) return NULL;
        else return vec->data + vec->used_len - count;
    } else return vec->data;
}

void* lab_vec_push_back    (lab_vec_t* vec, const void* data) {
    return lab_vec_push_back_arr(vec, data, 1);
}

void lab_vec_pop_back_arr(lab_vec_t* vec, size_t count) {
    vec->used_len -= count;
}
void lab_vec_pop_back    (lab_vec_t* vec) {
    --vec->used_len;
}

void* lab_vec_insert    (lab_vec_t* vec,  size_t index, const void* data, size_t count) {
    if(count > 0) {
        vec->used_len += count;
        if(vec->alloc_len < vec->used_len) {
            if(vec->used_len < vec->grow_fn(vec->alloc_len)) {
                if(!lab_vec_grow(vec)) return NULL;
            } else {
                if(!lab_vec_resize(vec, vec->used_len)) return NULL;
            }
        }
        if(lab_mem_shift_right(vec->data + LEN_TO_BYTES(index), USED_BYTES - LEN_TO_BYTES(index) - 1, LEN_TO_BYTES(count)) == NULL) return NULL;
        if(lab_mem_copy(vec->data + LEN_TO_BYTES(index), data, LEN_TO_BYTES(count))) return NULL;
        else return vec->data + index;
    } else return vec->data;
}

void* lab_vec_insert_vec(lab_vec_t* dest, size_t index, const lab_vec_t* src) {
    return lab_vec_insert(dest, index, src->data, src->used_len);
}

void* lab_vec_insert_vec_len(lab_vec_t* dest, size_t index, const lab_vec_t* src, size_t len) {
    return lab_vec_insert(dest, index, src->data, len <= src->used_len ? len : src->used_len);
}

bool lab_vec_remove_arr(lab_vec_t* vec, size_t start_index, size_t count) {
    vec->used_len -= count;
    if(lab_mem_shift_left(vec->data + LEN_TO_BYTES(start_index) + LEN_TO_BYTES(count), USED_BYTES - LEN_TO_BYTES(start_index), LEN_TO_BYTES(count)) == NULL) return false;
    else return true;
}

bool lab_vec_remove    (lab_vec_t* vec, size_t index) {
    return lab_vec_remove_arr(vec, index, 1);
}

bool lab_vec_copy(lab_vec_t* dest, lab_vec_t* src) {
    lab_vec_free(dest);
    return lab_vec_init(dest, src->type_size, src->alloc_len) &&
           lab_vec_push_back_arr(dest, src->data, src->used_len);
}

bool lab_vec_equal(lab_vec_t* vec0, lab_vec_t* vec1) {
    if(vec0->type_size != vec1->type_size) return false;
    if(vec0->used_len != vec1->used_len) return false;
    if(lab_mem_cmp(vec0->data, vec1->data, vec0->type_size * vec0->used_len) == 0) {
        return true;
    } else {
        return false;
    }
}