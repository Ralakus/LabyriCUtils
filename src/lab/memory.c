
#ifdef __cplusplus
extern "C" {
#endif

#include "memory.h"

#include <stdlib.h>
#include <string.h>

void* lab_mem_realloc(void* ptr, size_t size) {
    if(size == 0) {
        free(ptr);
        return NULL;
    }

    return realloc(ptr, size);
}

void* lab_mem_append (void* dest, size_t dest_size, const void* src, size_t size) {

    if(dest == NULL || src == NULL) {
        return NULL;
    }

    if(size == 0) {
        return dest;
    }

    dest = lab_mem_realloc(dest, dest_size + size);
    if(dest == NULL) return NULL;

    if(memcpy(dest + dest_size, src, size) == NULL) return NULL;

    return dest;

}

void* lab_mem_insert (void* dest, size_t dest_size, const void* src, size_t size, size_t index) {

    if(dest == NULL || src == NULL) {
        return NULL;
    }

    if(size == 0) {
        return dest;
    }

    dest = lab_mem_realloc(dest, dest_size + size);
    if(dest == NULL) return NULL;

    if(lab_mem_shift_right(dest + index, dest_size - index, size) == NULL) return NULL;
    if(memcpy(dest + index, src, size) == NULL) return NULL;

    return dest;

}

void* lab_mem_remove (void* ptr, size_t ptr_size,  size_t begin_idx, size_t end_idx) {
    if(lab_mem_shift_left(ptr + end_idx, ptr_size - end_idx, end_idx - begin_idx) == NULL) return NULL;
    return lab_mem_realloc(ptr, ptr_size - (end_idx - begin_idx));
}

void* lab_mem_shift_right(void* ptr, size_t size, size_t distance) {
    return memmove(ptr + distance, ptr, size);
}

void* lab_mem_shift_left (void* ptr, size_t size, size_t distance) {
    return memmove(ptr - distance, ptr, size);
}

void* lab_mem_copy(void* dest, const void* src, size_t size) {
    return memcpy(dest, src, size);
}

int lab_mem_cmp(const void* src0, const void* src1, size_t size) {
    return memcmp(src0, src1, size);
}

void lab_mem_free(void* ptr) {
    free(ptr);
}

#ifdef __cplusplus
}
#endif