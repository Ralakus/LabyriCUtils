
#ifdef __cplusplus
extern "C" {
#endif

#include "string.h"
#include <string.h>

bool lab_str_init(lab_str_t* str, size_t size) {

    return lab_vec_init(str, 1, size);

}

bool lab_str_make      (lab_str_t* str, const char* cstr) {
    if(!lab_str_init(str, strlen(cstr) + 1)) return false;
    return lab_vec_push_back_arr(str, cstr, str->alloc_size) != NULL;
}

bool lab_str_make_sized(lab_str_t* str, const char* cstr, size_t size) {
    if(!lab_str_init(str, size + 1)) return false;
    if(lab_vec_push_back_arr(str, cstr, size) == NULL) {
        return false;
    } else {
        LAB_VEC_TYPE_AT_RAW_ALLOC(str, size, char) = '\0';
        ++str->used_size;
        return true;
    }
}

void lab_str_free(lab_str_t* str) {
    lab_vec_free(str);
}

size_t lab_str_len(lab_str_t* str) {
    return lab_vec_size(str) - 1;
}

const char* lab_str_cstr(lab_str_t* str) {
    return (const char*)str->raw_data;
}


const char* lab_str_insert     (lab_str_t* dest, lab_str_t*  src, size_t index) {
    return lab_vec_insert(dest, index, src->raw_data, src->used_size - 1);
}

const char* lab_str_insert_cstr(lab_str_t* dest, const char* src, size_t index) {
    return lab_vec_insert(dest, index, src, strlen(src));
}


bool lab_str_append(lab_str_t* dest, lab_str_t* src) {
    return lab_vec_insert(dest, dest->used_size - 1, src->raw_data, src->used_size - 1);
}

bool lab_str_append_cstr(lab_str_t* dest, const char* src) {
    return lab_vec_insert(dest, dest->used_size - 1, src, strlen(src));
}

extern bool lab_str_substr(const lab_str_t* src, lab_str_t* dest, size_t i1, size_t i2) {
    lab_str_free(dest);

    if(i2 >= i1) {
        lab_errorln("\'lab_str_substr\' begin index is greater or equal to the end index!");
        return false;
    }

    return lab_str_make_sized(dest, src->raw_data + i1, i2 - i1);
}

void lab_str_to_upper(lab_str_t* str) {
    char* c = (char*)str->raw_data;
    while(*c) {
        if(*c >= 'a' || *c <= 'z') *c -= 32;
    }
}

void lab_str_to_lower(lab_str_t* str) {
    char* c = (char*)str->raw_data;
    while(*c) {
        if(*c >= 'A' || *c <= 'Z') *c += 32;
    }
}

#ifdef __cplusplus
}
#endif
